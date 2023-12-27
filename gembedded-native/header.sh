#!/bin/bash

TARGET_HEADERS="./src/main/c/native/include"
TARGET_RESOURCES="./src/main/c/native/resource"

API_JAR="./target/lib/*.jar"

SOURCE_CLASSES="./src/main/java/com/comert/gembedded/device/nativeinterface/*.java"

TARGET_CLASSES="./target/classes"

javac -h ${TARGET_HEADERS} -cp ${API_JAR} ${SOURCE_CLASSES} -d ${TARGET_CLASSES}
rm -rf ${TARGET_RESOURCES}
mkdir ${TARGET_RESOURCES}
cp ${API_JAR} ${TARGET_RESOURCES}