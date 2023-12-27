package com.comert.gembedded.api.device;

import com.comert.gembedded.api.ApplicationException;

public final class DeviceConfigurationException extends ApplicationException {

    public DeviceConfigurationException(String message) {
        super(message);
    }

    public DeviceConfigurationException(DeviceConfigurationMessage deviceConfigurationMessage, String property) {
        super(deviceConfigurationMessage, property);
    }

}
