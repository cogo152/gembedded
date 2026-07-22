#pragma once

struct JNIEnv_;
typedef JNIEnv_ JNIEnv;

void createJVM(void);

void getJNIEnv(JNIEnv **);

void destroyJVM(void);
