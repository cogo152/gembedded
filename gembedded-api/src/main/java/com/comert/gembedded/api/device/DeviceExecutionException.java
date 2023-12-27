package com.comert.gembedded.api.device;

import com.comert.gembedded.api.ApplicationException;
public class DeviceExecutionException extends ApplicationException {

    public DeviceExecutionException(DeviceExecutionMessage deviceExecutionMessage, String property) {
        super(deviceExecutionMessage, property);
    }

}
