#include "com_comert_gembedded_device_nativeinterface_JNIUtil.h"
#include "jniutil.h"

#include "commontest.hpp"
#include "jvm_test.h"

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

        return GCTEST_FALSE;
    }
    else
    {
        jfieldID pinFieldId = jniEnv->GetStaticFieldID(pinClass, PIN_NAME, PIN_SIGNATURE);
        if ((pinFieldId == NULL) || (jniEnv->ExceptionCheck()))
        {
            jniEnv->ExceptionDescribe();
            jniEnv->ExceptionClear();
            return GCTEST_FALSE;
        }
        else
        {
            pin = jniEnv->GetStaticObjectField(pinClass, pinFieldId);
            if ((pin == NULL) || (jniEnv->ExceptionCheck()))
            {
                jniEnv->ExceptionDescribe();
                jniEnv->ExceptionClear();
                return GCTEST_FALSE;
            }
        }
    }

    jclass const notInstanceClass = jniEnv->FindClass(NOT_INSTANCE_ENUM_CLASS);
    if ((notInstanceClass == NULL) || (jniEnv->ExceptionCheck()))
    {
        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();
        return GCTEST_FALSE;
    }
    else
    {
        jfieldID notInstanceFieldId = jniEnv->GetStaticFieldID(notInstanceClass, NOT_INSTANCE_ENUM_NAME,
                                                               NOT_INSTANCE_ENUM_SIGNATURE);
        if ((notInstanceFieldId == NULL) || (jniEnv->ExceptionCheck()))
        {
            jniEnv->ExceptionDescribe();
            jniEnv->ExceptionClear();
            return GCTEST_FALSE;
        }
        else
        {
            notInstance = jniEnv->GetStaticObjectField(notInstanceClass, notInstanceFieldId);
            if ((notInstance == NULL) || (jniEnv->ExceptionCheck()))
            {
                jniEnv->ExceptionDescribe();
                jniEnv->ExceptionClear();
                return GCTEST_FALSE;
            }
        }
    }

    return GCTEST_TRUE;
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

    return GCTEST_TRUE;
}

GCTEST_CASE(testInitJniUtilSuite)
{
    gctest_case_config_default(testInitJniUtilSuite);

    gctest_case_now
    {
        assert_equal(initJniUtilSuite(), GCTEST_TRUE);
    }
};

GCTEST_CASE(testSetupJNIUtil)
{
    gctest_case_config_default(testSetupJNIUtil);

    gctest_case_now
    {
        Java_com_comert_gembedded_device_nativeinterface_JNIUtil_setupJNIUtil(jniEnv, NULL);

        assert_false(jniEnv->ExceptionCheck());
    }
};

GCTEST_CASE(testThrowANewRuntimeException)
{
    gctest_case_config_default(testThrowANewRuntimeException);

    gctest_case_now
    {
        // ERROR EXIT_FAILURE: if the env is NULL.
        // throwANewRuntimeException(NULL, "Hello World"); // exits process

        // ERROR EXIT_FAILURE: if the message is NULL.
        // throwANewRuntimeException(jniEnv,NULL); // exits process

        throwANewRuntimeException(jniEnv, "***TestRuntimeException***");
        assert_true(jniEnv->ExceptionCheck());

        jthrowable exceptionClass = jniEnv->ExceptionOccurred();
        jboolean isInstance = jniEnv->IsInstanceOf(exceptionClass, jniEnv->FindClass(RUNTIMEEXCEPTION_CLASS));

        assert_true(isInstance);

        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();

        assert_false(jniEnv->ExceptionCheck());
    }
};

GCTEST_CASE(testThrowANewDeviceConfigurationException)
{
    gctest_case_config_default(testThrowANewDeviceConfigurationException);

    gctest_case_now
    {
        // ERROR EXIT_FAILURE: if the env is NULL.
        // throwANewDeviceConfigurationException(NULL, "Hello World"); // exits process

        // ERROR EXIT_FAILURE: if the message is NULL.
        // throwANewDeviceConfigurationException(jniEnv,NULL); // exits process

        throwANewDeviceConfigurationException(jniEnv, "***TestDeviceConfigurationException***");

        assert_true(jniEnv->ExceptionCheck());

        jthrowable exceptionClass = jniEnv->ExceptionOccurred();
        jboolean isInstance = jniEnv->IsInstanceOf(exceptionClass,
                                                   jniEnv->FindClass(DEVICECONFIGURATIONEXCEPTION_CLASS));

        assert_true(isInstance);

        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();

        assert_false(jniEnv->ExceptionCheck());
    }
};

GCTEST_CASE(testThrowANewDeviceIOException)
{
    gctest_case_config_default(testThrowANewDeviceIOException);

    gctest_case_now
    {
        // ERROR EXIT_FAILURE: if the env is NULL.
        // throwANewDeviceIOException(NULL, "Hello World"); // exits process

        // ERROR EXIT_FAILURE: if the message is NULL.
        // throwANewDeviceIOException(jniEnv,NULL); // exits process

        throwANewDeviceIOException(jniEnv, "***TestDeviceIOException***");

        assert_true(jniEnv->ExceptionCheck());

        jthrowable exceptionClass = jniEnv->ExceptionOccurred();
        jboolean isInstance = jniEnv->IsInstanceOf(exceptionClass,
                                                   jniEnv->FindClass(DEVICEIOEXCEPTION_CLASS));

        assert_true(isInstance);

        jniEnv->ExceptionDescribe();
        jniEnv->ExceptionClear();

        assert_false(jniEnv->ExceptionCheck());
    }
};

GCTEST_CASE(testGetEnumDigit)
{
    gctest_case_config_default(testGetEnumDigit);

    gctest_case_now
    {
        jbyte digitValue = -1;
        JNI_STATUS status;

        // JNI_ERROR : if the env is NULL.
        status = getEnumDigit(NULL, pin, NULL);

        assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enumObject is NULL.
        status = getEnumDigit(jniEnv, NULL, NULL);
        assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enum does not implement DeviceConstant interface.
        status = getEnumDigit(jniEnv, notInstance, &digitValue);
        assert_equal(status, JNI_ERROR);

        status = getEnumDigit(jniEnv, pin, &digitValue);
        assert_equal(status, JNI_SUCCESS);
        assert_equal(digitValue, static_cast<jbyte>(PIN_DIGIT));
    }
};

GCTEST_CASE(testGetEnumText)
{
    gctest_case_config_default(testGetEnumText);

    gctest_case_now
    {
        char text[sizeof PIN_TEXT];
        JNI_STATUS status;

        // JNI_ERROR : if the env is NULL.
        status = getEnumText(NULL, pin, text, sizeof(text));
        assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enumObject is NULL.
        status = getEnumText(jniEnv, NULL, text, sizeof(text));
        assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the textToReturn is a NULL char array.
        status = getEnumText(jniEnv, pin, NULL, sizeof(text));
        assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enum does not implement DeviceConstant interface.
        status = getEnumText(jniEnv, notInstance, text, sizeof(text));
        assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the textToReturnSize is less than string size.
        status = getEnumText(jniEnv, pin, text, sizeof(text) - 2); // nil character
        assert_equal(status, JNI_ERROR);

        status = getEnumText(jniEnv, pin, text, sizeof(text));
        assert_equal(status, JNI_SUCCESS);
        assert_equal(reinterpret_cast<const char *>(text), PIN_TEXT);
    }
};

GCTEST_CASE(testGetEnum)
{
    gctest_case_config_default(testGetEnum);

    gctest_case_now
    {
        jobject pinToGet;
        JNI_STATUS status;

        // JNI_ERROR : if the env is NULL.
        status = getEnum(NULL, PIN_CLASS, PIN_NAME, PIN_SIGNATURE, &pinToGet);
        assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the fullyQualifiedEnumClassName is NULL.
        status = getEnum(jniEnv, NULL, PIN_NAME, PIN_SIGNATURE, &pinToGet);
        assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enumName is NULL.
        status = getEnum(jniEnv, PIN_CLASS, NULL, PIN_SIGNATURE, &pinToGet);
        assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enumSignature is NULL.
        status = getEnum(jniEnv, PIN_CLASS, PIN_NAME, NULL, &pinToGet);
        assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the enumToReturn is NULL.
        status = getEnum(jniEnv, PIN_CLASS, PIN_NAME, PIN_SIGNATURE, NULL);
        assert_equal(status, JNI_ERROR);

        // JNI_ERROR : if the fullyQualifiedEnumClassName is invalid.
        status = getEnum(jniEnv, INVALID_PIN_CLASS, PIN_NAME, PIN_SIGNATURE, NULL);
        assert_equal(status, JNI_ERROR);
        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionClear();
        }

        // JNI_ERROR : if the enum does not implement DeviceConstant interface.
        status = getEnum(jniEnv, NOT_INSTANCE_ENUM_CLASS, NOT_INSTANCE_ENUM_NAME, NOT_INSTANCE_ENUM_SIGNATURE, &pinToGet);
        assert_equal(status, JNI_ERROR);
        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionClear();
        }

        // JNI_ERROR : if the enumName is invalid.
        status = getEnum(jniEnv, PIN_CLASS, INVALID_PIN_NAME, PIN_SIGNATURE, &pinToGet);
        assert_equal(status, JNI_ERROR);
        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionClear();
        }

        // JNI_ERROR : if the enumSignature is invalid.
        status = getEnum(jniEnv, PIN_CLASS, PIN_NAME, INVALID_PIN_SIGNATURE, &pinToGet);
        assert_equal(status, JNI_ERROR);
        if (jniEnv->ExceptionCheck())
        {
            jniEnv->ExceptionClear();
        }

        status = getEnum(jniEnv, PIN_CLASS, PIN_NAME, PIN_SIGNATURE, &pinToGet);
        assert_equal(status, JNI_SUCCESS);
        jboolean isSameObject = jniEnv->IsSameObject(pin, pinToGet);
        assert_true(isSameObject);
    }
};

GCTEST_CASE(testShutdownJNIUtil)
{
    gctest_case_config_default(testShutdownJNIUtil);

    gctest_case_now
    {
        Java_com_comert_gembedded_device_nativeinterface_JNIUtil_shutdownJNIUtil(jniEnv, NULL);

        assert_false(jniEnv->ExceptionCheck());
    }
};

GCTEST_CASE(testCleanupJniUtilSuite)
{
    gctest_case_config_default(testCleanupJniUtilSuite);

    gctest_case_now
    {
        assert_equal(cleanupJniUtilSuite(), GCTEST_TRUE);
    }
};
