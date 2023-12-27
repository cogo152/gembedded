#include "devicedriver.h"
#include "jniutil.h"
#include "mapper.h"

#include <unistd.h>
#include <stdexcept>

#include "commontest.hpp"
#include "jvm_test.h"

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
        return GCTEST_FALSE;
    }

    return GCTEST_TRUE;
}

int cleanupDeviceDriverSuite(void)
{

    Java_com_comert_gembedded_device_nativeinterface_JNIUtil_shutdownJNIUtil(jniEnv, NULL);

    if (jniEnv->ExceptionCheck())
    {
        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();
        return GCTEST_FALSE;
    }

    jniEnv = NULL;

    return GCTEST_TRUE;
}

GCTEST_CASE(testInitDriverSuite)
{
    gctest_case_config_default(testInitDriverSuite);

    gctest_case_now
    {
        assert_equal(initDeviceDriverSuite(), GCTEST_TRUE);
    }
};

GCTEST_CASE(testSetupDeviceDriver)
{
    gctest_case_config_default(testSetupDeviceDriver);

    gctest_case_now
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
        assert_equal(static_cast<unsigned int>(peripheralBase), PERIPHERAL_BASE_ADDRESS);

        Java_com_comert_gembedded_device_nativeinterface_DeviceDriver_setupDeviceDriver(jniEnv, NULL);

        assert_false(jniEnv->ExceptionCheck());

        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionDescribe();
            jniEnv->ExceptionClear();
            throw std::runtime_error("Exception");
        }


    }
};

GCTEST_CASE(testGetDeviceName)
{
    gctest_case_config_default(testGetDeviceName);

    gctest_case_now
    {
        char deviceName[sizeof DEVICE_NAME];

        jstring deviceNameString = Java_com_comert_gembedded_device_nativeinterface_DeviceDriver_getDeviceName(jniEnv,
                                                                                                               NULL);
        // assert_true(deviceNameString);

        jsize stringSize = jniEnv->GetStringUTFLength(deviceNameString);
        jniEnv->GetStringUTFRegion(deviceNameString, 0, stringSize, deviceName);
        assert_equal(reinterpret_cast<const char *>(deviceName), DEVICE_NAME);
    }
};

GCTEST_CASE(testRequestGPIOOBase)
{
    gctest_case_config_default(testRequestGPIOOBase);

    gctest_case_now
    {
        void *ptr = requestGPIOOBase();
        assert_true(ptr != NULL); // change with pointer check
    }
};

GCTEST_CASE(testRequestClockBase)
{
    gctest_case_config_default(testRequestClockBase);

    gctest_case_now
    {
        void *ptr = requestClockBase();
        assert_true(ptr != NULL); // change with pointer check
    }
};

GCTEST_CASE(testRequestPWMBase)
{
    gctest_case_config_default(testRequestPWMBase);

    gctest_case_now
    {
        void *ptr = requestPWMBase();
        assert_true(ptr != NULL); // change with pointer check
    }
};

GCTEST_CASE(testRequestI2CMasterBase)
{
    gctest_case_config_default(testRequestI2CMasterBase);

    gctest_case_now
    {
        void *ptr = requestI2CMasterBase();
        assert_true(ptr != NULL); // change with pointer check
    }
};

GCTEST_CASE(testShutdownDeviceDriver)
{
    gctest_case_config_default(testShutdownDeviceDriver);

    gctest_case_now
    {
        Java_com_comert_gembedded_device_nativeinterface_DeviceDriver_shutdownDeviceDriver(jniEnv, NULL);

        assert_false(jniEnv->ExceptionCheck());

        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionDescribe();
            jniEnv->ExceptionClear();
            throw std::runtime_error("Exception");
        }
    }
};

GCTEST_CASE(testCleanupDeviceDriverSuite)
{
    gctest_case_config_default(testCleanupDeviceDriverSuite);

    gctest_case_now
    {
        assert_equal(cleanupDeviceDriverSuite(), GCTEST_TRUE);
    }
};