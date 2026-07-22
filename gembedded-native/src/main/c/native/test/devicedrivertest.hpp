#pragma once

#include <gctest/core/core.hpp>

#include "devicedriver.h"

#include "jvm.hpp"
#include "jniutil.h"
#include "mapper.h"

#include <unistd.h>
#include <stdexcept>

#include "i2cmasterdriver.h"

#define SOC_RANGE_FILE ("/proc/device-tree/soc/ranges")
#define PERIPHERAL_BASE_OFFSET (8)

#define PAGE_LENGTH (8)
#define PAGE_SHIFT (12)

static JNIEnv *jniEnv = NULL;

int initDeviceDriverSuite(void)
{

    getJNIEnv(&jniEnv);

    Java_com_comert_gembedded_device_nativeinterface_JNIUtil_setupJNIUtil(jniEnv, NULL);
    if (jniEnv->ExceptionCheck())
    {
        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();
        return 1;
    }

    return 0;
}

int cleanupDeviceDriverSuite(void)
{

    Java_com_comert_gembedded_device_nativeinterface_JNIUtil_shutdownJNIUtil(jniEnv, NULL);

    if (jniEnv->ExceptionCheck())
    {
        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();
        return 1;
    }

    jniEnv = NULL;

    return 0;
}

Gctest_Case(testInitDriverSuite)
{
    Gctest_Case_Ctor(testInitDriverSuite);

    Gctest_Case_Assert()
    {
        gctest_case_assert_equal(initDeviceDriverSuite(), 0);
    }
};

Gctest_Case(testSetupDeviceDriver)
{
    Gctest_Case_Ctor(testSetupDeviceDriver);

    Gctest_Case_Assert()
    {
        off_t peripheralBase;

        FILE *const fp = fopen(SOC_RANGE_FILE, "rb");
        if (fp == NULL)
        {
            fclose(fp);
            throw std::runtime_error("Exception");
        }

        int const seekStatus = fseek(fp, PERIPHERAL_BASE_OFFSET, SEEK_SET);
        if (seekStatus != 0)
        {
            fclose(fp);
            throw std::runtime_error("Exception");
        }

        uint8_t buf[4];
        uint32_t const readStatus = fread(buf, 1, sizeof buf, fp);
        if (readStatus != sizeof buf)
        {
            fclose(fp);
            throw std::runtime_error("Exception");
        }

        fclose(fp);

        peripheralBase = buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3] << 0;
        gctest_case_assert_equal(static_cast<unsigned int>(peripheralBase), PERIPHERAL_BASE_ADDRESS);

        Java_com_comert_gembedded_device_nativeinterface_DeviceDriver_setupDeviceDriver(jniEnv, NULL);

        gctest_case_assert_true(jniEnv->ExceptionCheck() == JNI_FALSE);

        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionDescribe();
            jniEnv->ExceptionClear();
            throw std::runtime_error("Exception");
        }
    }
};

Gctest_Case(testGetDeviceName)
{
    Gctest_Case_Ctor(testGetDeviceName);

    Gctest_Case_Assert()
    {
        char deviceName[sizeof DEVICE_NAME];

        jstring deviceNameString = Java_com_comert_gembedded_device_nativeinterface_DeviceDriver_getDeviceName(jniEnv,
                                                                                                               NULL);
        // assert_true(deviceNameString);

        jsize stringSize = jniEnv->GetStringUTFLength(deviceNameString);
        jniEnv->GetStringUTFRegion(deviceNameString, 0, stringSize, deviceName);
        gctest_case_assert_equal(reinterpret_cast<const char *>(deviceName), DEVICE_NAME);
    }
};

Gctest_Case(testRequestGPIOOBase)
{
    Gctest_Case_Ctor(testRequestGPIOOBase);

    Gctest_Case_Assert()
    {
        void *ptr = requestGPIOOBase();
        gctest_case_assert_true(ptr != NULL); // change with pointer check
    }
};

Gctest_Case(testRequestClockBase)
{
    Gctest_Case_Ctor(testRequestClockBase);

    Gctest_Case_Assert()
    {
        void *ptr = requestClockBase();
        gctest_case_assert_true(ptr != NULL); // change with pointer check
    }
};

Gctest_Case(testRequestPWMBase)
{
    Gctest_Case_Ctor(testRequestPWMBase);

    Gctest_Case_Assert()
    {
        void *ptr = requestPWMBase();
        gctest_case_assert_true(ptr != NULL); // change with pointer check
    }
};

Gctest_Case(testRequestI2CMasterBase)
{
    Gctest_Case_Ctor(testRequestI2CMasterBase);

    Gctest_Case_Assert()
    {
        void *ptr = requestI2CMasterBase();
        gctest_case_assert_true(ptr != NULL); // change with pointer check
    }
};

Gctest_Case(testShutdownDeviceDriver)
{
    Gctest_Case_Ctor(testShutdownDeviceDriver);

    Gctest_Case_Assert()
    {
        Java_com_comert_gembedded_device_nativeinterface_DeviceDriver_shutdownDeviceDriver(jniEnv, NULL);

        gctest_case_assert_true(jniEnv->ExceptionCheck() == JNI_FALSE);

        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionDescribe();
            jniEnv->ExceptionClear();
            throw std::runtime_error("Exception");
        }
    }
};

Gctest_Case(testCleanupDeviceDriverSuite)
{
    Gctest_Case_Ctor(testCleanupDeviceDriverSuite);

    Gctest_Case_Assert()
    {
        gctest_case_assert_equal(cleanupDeviceDriverSuite(), 0);
    }
};