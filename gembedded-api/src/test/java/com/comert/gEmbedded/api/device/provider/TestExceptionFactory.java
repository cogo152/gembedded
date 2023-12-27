package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.DeviceConfigurationException;

public class TestExceptionFactory {

    public static void throwANewDeviceConfigurationException() throws DeviceConfigurationException {
        throw new DeviceConfigurationException(TestDeviceExceptionMessage.TEST_CONFIGURATION, "Test");
    }

}
