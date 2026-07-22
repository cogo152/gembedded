#include "jvm.hpp"

#include <jni.h>
#include <iostream>
#include <cstdlib>

static JavaVM *javaVm;
static JNIEnv *jniEnv;

void createJVM(void)
{
    JavaVMInitArgs javaVmInitArgs;
    JavaVMOption javaVmOption[1];

    constexpr jint JNI_VERSION = JNI_VERSION_21;
    constexpr const char *GEMBEDDED_API_JAR_CLASSPATH = "-Djava.class.path=./../resource/gembedded-api-1.0.0-SNAPSHOT.jar";
    constexpr const char *GEMBEDDED_API_JAR_VALIDATION_EXAMPLE_CLASS = "com/comert/gembedded/api/device/DeviceContext";

    javaVmOption[0].optionString = const_cast<char *>(GEMBEDDED_API_JAR_CLASSPATH);

    javaVmInitArgs.version = JNI_VERSION;
    javaVmInitArgs.options = javaVmOption;
    javaVmInitArgs.nOptions = 1;
    javaVmInitArgs.ignoreUnrecognized = JNI_FALSE;

    const auto jvmCreated = JNI_CreateJavaVM(&javaVm, (void **)&jniEnv, &javaVmInitArgs);
    if (jvmCreated != JNI_OK)
    {
        std::cout << "FATAL ERROR file::jvm_test.c, function::createJVM(), message::JVM creation failed, error code:: " << jvmCreated << "\n";
        std::exit(EXIT_FAILURE);
    }

    if (!jniEnv)
    {
        std::cout << "FATAL ERROR file::jvm_test.c, function::createJVM(), message::NULL jniEnv\n";
        std::exit(EXIT_FAILURE);
    }
    else
    {
        const auto jniVersion = jniEnv->GetVersion();
        if (jniVersion != JNI_VERSION)
        {
            std::cout << "FATAL ERROR file::jvm_test.c, function::createJVM(), message::invalid jniEnv\n";
            std::exit(EXIT_FAILURE);
        }
    }

    const auto DeviceContextClass = jniEnv->FindClass(GEMBEDDED_API_JAR_VALIDATION_EXAMPLE_CLASS);
    if (!DeviceContextClass || jniEnv->ExceptionCheck() == JNI_TRUE)
    {
        if (jniEnv->ExceptionCheck() == JNI_TRUE)
        {
            jniEnv->ExceptionDescribe();
            jniEnv->ExceptionClear();
        }
        std::cout << "FATAL ERROR file::jvm_test.c, function::createJVM(), message::invalid gembedded-api-XXX.jar or validation example class\n";
        std::exit(EXIT_FAILURE);
    }

    std::cout << "JVM is successfully created\n";
}

void getJNIEnv(JNIEnv **pJniEnv)
{

    if (!pJniEnv)
    {
        std::cout << "FATAL ERROR file::jvm_test.c, function::getJNIEnv(JNIEnv **pJniEnv), message::NULL pJniEnv\n";
        std::exit(EXIT_FAILURE);
    }

    *pJniEnv = jniEnv;
}

void destroyJVM()
{

    if (!javaVm)
    {
        std::cout << "FATAL ERROR file::jvm_test.c, function::destroyJVM(), message::NULL javaVm\n";
        std::exit(EXIT_FAILURE);
    }
    else
    {
        const auto jvmDestroyed = javaVm->DestroyJavaVM();
        if (jvmDestroyed != JNI_OK)
        {
            std::cout << "FATAL ERROR file::jvm_test.c, function::destroyJVM(), message::JVM removal failed, error code:: " << jvmDestroyed << "\n";
            std::exit(EXIT_FAILURE);
        }
    }

    std::cout << "JVM is successfully destroyed\n";
}