#pragma once

#include <gctest/core/core.hpp>

#include "com_comert_gembedded_device_nativeinterface_JNIUtil.h"
#include "jniutil.h"

#include "jvm.hpp"

#include <stdexcept>

#define PIN_CLASS ("com/comert/gembedded/api/device/Pin")
#define PIN_NAME ("PIN_27")
#define PIN_SIGNATURE ("Lcom/comert/gembedded/api/device/Pin;")
#define PIN_DIGIT (27)
#define PIN_TEXT ("Twenty seven")

#define INVALID_PIN_CLASS ("com/comert/gembedded/api/device/InvalidPin")
#define INVALID_PIN_NAME ("PIN_INVALID")
#define INVALID_PIN_SIGNATURE ("Lcom/comert/gembedded/api/device/InvalidPin;")

#define NOT_INSTANCE_ENUM_CLASS ("java/lang/Thread$State")
#define NOT_INSTANCE_ENUM_NAME ("NEW")
#define NOT_INSTANCE_ENUM_SIGNATURE ("Ljava/lang/Thread$State;")

static JNIEnv *jniEnv = NULL;
static jobject pin = NULL;
static jobject notInstance = NULL;

int initJniUtilSuite(void)
{

    getJNIEnv(&jniEnv);

    jclass const pinClass = jniEnv->FindClass(PIN_CLASS);
    jniEnv->ExceptionDescribe();

    if ((pinClass == NULL) || (jniEnv->ExceptionCheck()))
    {
        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();

        return 1;
    }
    else
    {
        jfieldID pinFieldId = jniEnv->GetStaticFieldID(pinClass, PIN_NAME, PIN_SIGNATURE);
        if ((pinFieldId == NULL) || (jniEnv->ExceptionCheck()))
        {
            jniEnv->ExceptionDescribe();
            jniEnv->ExceptionClear();
            return 2;
        }
        else
        {
            pin = jniEnv->GetStaticObjectField(pinClass, pinFieldId);
            if ((pin == NULL) || (jniEnv->ExceptionCheck()))
            {
                jniEnv->ExceptionDescribe();
                jniEnv->ExceptionClear();
                return 3;
            }
        }
    }

    jclass const notInstanceClass = jniEnv->FindClass(NOT_INSTANCE_ENUM_CLASS);
    if ((notInstanceClass == NULL) || (jniEnv->ExceptionCheck()))
    {
        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();
        return 4;
    }
    else
    {
        jfieldID notInstanceFieldId = jniEnv->GetStaticFieldID(notInstanceClass, NOT_INSTANCE_ENUM_NAME,
                                                               NOT_INSTANCE_ENUM_SIGNATURE);
        if ((notInstanceFieldId == NULL) || (jniEnv->ExceptionCheck()))
        {
            jniEnv->ExceptionDescribe();
            jniEnv->ExceptionClear();
            return 5;
        }
        else
        {
            notInstance = jniEnv->GetStaticObjectField(notInstanceClass, notInstanceFieldId);
            if ((notInstance == NULL) || (jniEnv->ExceptionCheck()))
            {
                jniEnv->ExceptionDescribe();
                jniEnv->ExceptionClear();
                return 6;
            }
        }
    }

    return 0;
}

int cleanupJniUtilSuite(void)
{

    if (jniEnv->ExceptionCheck())
    {
        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();
    }

    jniEnv = NULL;
    pin = NULL;
    notInstance = NULL;

    return 0;
}

Gctest_Case(testInitJniUtilSuite)
{
    Gctest_Case_Ctor(testInitJniUtilSuite);

    Gctest_Case_Assert()
    {
        gctest_case_assert_equal(initJniUtilSuite(), 0);
    }
};

Gctest_Case(testSetupJNIUtil)
{
    Gctest_Case_Ctor(testSetupJNIUtil);

    Gctest_Case_Assert()
    {
        Java_com_comert_gembedded_device_nativeinterface_JNIUtil_setupJNIUtil(jniEnv, NULL);

        gctest_case_assert_false(jniEnv->ExceptionCheck() == JNI_TRUE);
    }
};

Gctest_Case(testThrowANewRuntimeException)
{
    Gctest_Case_Ctor(testThrowANewRuntimeException);

    Gctest_Case_Assert()
    {
        // ERROR EXIT_FAILURE: if the env is NULL.
        // throwANewRuntimeException(NULL, "Hello World"); // exits process

        // ERROR EXIT_FAILURE: if the message is NULL.
        // throwANewRuntimeException(jniEnv,NULL); // exits process

        throwANewRuntimeException(jniEnv, "***TestRuntimeException***");
        gctest_case_assert_true(jniEnv->ExceptionCheck() == JNI_TRUE);

        jthrowable exceptionClass = jniEnv->ExceptionOccurred();
        jboolean isInstance = jniEnv->IsInstanceOf(exceptionClass, jniEnv->FindClass(RUNTIMEEXCEPTION_CLASS));

        gctest_case_assert_true(isInstance == JNI_TRUE);

        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();

        gctest_case_assert_false(jniEnv->ExceptionCheck() == JNI_TRUE);
    }
};

Gctest_Case(testThrowANewDeviceConfigurationException)
{
    Gctest_Case_Ctor(testThrowANewDeviceConfigurationException);

    Gctest_Case_Assert()
    {
        // ERROR EXIT_FAILURE: if the env is NULL.
        // throwANewDeviceConfigurationException(NULL, "Hello World"); // exits process

        // ERROR EXIT_FAILURE: if the message is NULL.
        // throwANewDeviceConfigurationException(jniEnv,NULL); // exits process

        throwANewDeviceConfigurationException(jniEnv, "***TestDeviceConfigurationException***");

        gctest_case_assert_true(jniEnv->ExceptionCheck() == JNI_TRUE);

        jthrowable exceptionClass = jniEnv->ExceptionOccurred();
        jboolean isInstance = jniEnv->IsInstanceOf(exceptionClass,
                                                   jniEnv->FindClass(DEVICECONFIGURATIONEXCEPTION_CLASS));

        gctest_case_assert_true(isInstance == JNI_TRUE);

        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();

        gctest_case_assert_false(jniEnv->ExceptionCheck() == JNI_TRUE);
    }
};

Gctest_Case(testThrowANewDeviceIOException)
{
    Gctest_Case_Ctor(testThrowANewDeviceIOException);

    Gctest_Case_Assert()
    {
        // ERROR EXIT_FAILURE: if the env is NULL.
        // throwANewDeviceIOException(NULL, "Hello World"); // exits process

        // ERROR EXIT_FAILURE: if the message is NULL.
        // throwANewDeviceIOException(jniEnv,NULL); // exits process

        throwANewDeviceIOException(jniEnv, "***TestDeviceIOException***");

        gctest_case_assert_true(jniEnv->ExceptionCheck() == JNI_TRUE);

        jthrowable exceptionClass = jniEnv->ExceptionOccurred();
        jboolean isInstance = jniEnv->IsInstanceOf(exceptionClass,
                                                   jniEnv->FindClass(DEVICEIOEXCEPTION_CLASS));

        gctest_case_assert_true(isInstance == JNI_TRUE);

        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();

        gctest_case_assert_false(jniEnv->ExceptionCheck() == JNI_TRUE);
    }
};

Gctest_Case(testGetEnumDigit)
{
    Gctest_Case_Ctor(testGetEnumDigit);

    Gctest_Case_Assert()
    {
        jbyte digitValue = -1;
        JNI_STATUS status;

        // JNI_ERROR : if the env is NULL.
        status = getEnumDigit(NULL, pin, NULL);

        gctest_case_assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enumObject is NULL.
        status = getEnumDigit(jniEnv, NULL, NULL);
        gctest_case_assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enum does not implement DeviceConstant interface.
        status = getEnumDigit(jniEnv, notInstance, &digitValue);
        gctest_case_assert_equal(status, JNI_ERROR);

        status = getEnumDigit(jniEnv, pin, &digitValue);
        gctest_case_assert_equal(status, JNI_SUCCESS);
        gctest_case_assert_equal(digitValue, static_cast<jbyte>(PIN_DIGIT));
    }
};

Gctest_Case(testGetEnumText)
{
    Gctest_Case_Ctor(testGetEnumText);

    Gctest_Case_Assert()
    {
        char text[sizeof PIN_TEXT];
        JNI_STATUS status;

        // JNI_ERROR : if the env is NULL.
        status = getEnumText(NULL, pin, text, sizeof(text));
        gctest_case_assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enumObject is NULL.
        status = getEnumText(jniEnv, NULL, text, sizeof(text));
        gctest_case_assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the textToReturn is a NULL char array.
        status = getEnumText(jniEnv, pin, NULL, sizeof(text));
        gctest_case_assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enum does not implement DeviceConstant interface.
        status = getEnumText(jniEnv, notInstance, text, sizeof(text));
        gctest_case_assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the textToReturnSize is less than string size.
        status = getEnumText(jniEnv, pin, text, sizeof(text) - 2); // nil character
        gctest_case_assert_equal(status, JNI_ERROR);

        status = getEnumText(jniEnv, pin, text, sizeof(text));
        gctest_case_assert_equal(status, JNI_SUCCESS);
        gctest_case_assert_equal(reinterpret_cast<const char *>(text), PIN_TEXT);
    }
};

Gctest_Case(testGetEnum)
{
    Gctest_Case_Ctor(testGetEnum);

    Gctest_Case_Assert()
    {
        jobject pinToGet;
        JNI_STATUS status;

        // JNI_ERROR : if the env is NULL.
        status = getEnum(NULL, PIN_CLASS, PIN_NAME, PIN_SIGNATURE, &pinToGet);
        gctest_case_assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the fullyQualifiedEnumClassName is NULL.
        status = getEnum(jniEnv, NULL, PIN_NAME, PIN_SIGNATURE, &pinToGet);
        gctest_case_assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enumName is NULL.
        status = getEnum(jniEnv, PIN_CLASS, NULL, PIN_SIGNATURE, &pinToGet);
        gctest_case_assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enumSignature is NULL.
        status = getEnum(jniEnv, PIN_CLASS, PIN_NAME, NULL, &pinToGet);
        gctest_case_assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enumToReturn is NULL.
        status = getEnum(jniEnv, PIN_CLASS, PIN_NAME, PIN_SIGNATURE, NULL);
        gctest_case_assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the fullyQualifiedEnumClassName is invalid.
        status = getEnum(jniEnv, INVALID_PIN_CLASS, PIN_NAME, PIN_SIGNATURE, NULL);
        gctest_case_assert_equal(status, JNI_ERROR);
        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionClear();
        }

        // JNI_ERROR : if the enum does not implement DeviceConstant interface.
        status = getEnum(jniEnv, NOT_INSTANCE_ENUM_CLASS, NOT_INSTANCE_ENUM_NAME, NOT_INSTANCE_ENUM_SIGNATURE, &pinToGet);
        gctest_case_assert_equal(status, JNI_ERROR);
        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionClear();
        }

        // JNI_ERROR : if the enumName is invalid.
        status = getEnum(jniEnv, PIN_CLASS, INVALID_PIN_NAME, PIN_SIGNATURE, &pinToGet);
        gctest_case_assert_equal(status, JNI_ERROR);
        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionClear();
        }

        // JNI_ERROR : if the enumSignature is invalid.
        status = getEnum(jniEnv, PIN_CLASS, PIN_NAME, INVALID_PIN_SIGNATURE, &pinToGet);
        gctest_case_assert_equal(status, JNI_ERROR);
        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionClear();
        }

        status = getEnum(jniEnv, PIN_CLASS, PIN_NAME, PIN_SIGNATURE, &pinToGet);
        gctest_case_assert_equal(status, JNI_SUCCESS);
        jboolean isSameObject = jniEnv->IsSameObject(pin, pinToGet);
        gctest_case_assert_true(isSameObject == JNI_TRUE);
    }
};

Gctest_Case(testShutdownJNIUtil)
{
    Gctest_Case_Ctor(testShutdownJNIUtil);

    Gctest_Case_Assert()
    {
        Java_com_comert_gembedded_device_nativeinterface_JNIUtil_shutdownJNIUtil(jniEnv, NULL);

        gctest_case_assert_false(jniEnv->ExceptionCheck() == JNI_TRUE);
    }
};

Gctest_Case(testCleanupJniUtilSuite)
{
    Gctest_Case_Ctor(testCleanupJniUtilSuite);

    Gctest_Case_Assert()
    {
        gctest_case_assert_equal(cleanupJniUtilSuite(), 0);
    }
};
