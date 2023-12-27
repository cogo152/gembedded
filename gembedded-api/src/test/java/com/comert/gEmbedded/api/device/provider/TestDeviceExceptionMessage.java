package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.DeviceConfigurationMessage;

public enum TestDeviceExceptionMessage implements DeviceConfigurationMessage {

    TEST_CONFIGURATION("Test Configuration");
    TestDeviceExceptionMessage(String message) {
        this.message = message;
    }

    private final String message;

    @Override
    public String toString() {
        return message;
    }

}
