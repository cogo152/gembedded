#ifndef JVM_TEST_H
#define JVM_TEST_H

#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define JNI_VERSION (JNI_VERSION_21)
#define GEMBEDDED_API_JAR_CLASSPATH ("-Djava.class.path=./../resource/gembedded-api-1.0.0-SNAPSHOT.jar")
#define GEMBEDDED_API_JAR_VALIDATION_EXAMPLE_CLASS ("com/comert/gembedded/api/device/DeviceContext")

#ifdef __cplusplus
extern "C"
{
#endif

    void createJVM(void);

    void getJNIEnv(JNIEnv **);

    void destroyJVM(void);

#ifdef __cplusplus
}
#endif

#endif
