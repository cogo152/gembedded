package com.comert.gembedded.api.device;

import com.comert.gembedded.api.ApplicationException;

public class DeviceIOException extends ApplicationException {

    public DeviceIOException(String message) {
        super(message);
    }

    public DeviceIOException(DeviceIOMessage deviceIOMessage, String property) {
        super(deviceIOMessage, property);
    }

}
