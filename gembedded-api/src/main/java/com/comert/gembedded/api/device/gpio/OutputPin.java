package com.comert.gembedded.api.device.gpio;

import com.comert.gembedded.api.device.DeviceIOException;

public interface OutputPin {

    void setHigh();

    void setHighWithException() throws DeviceIOException;

    void setLow();

    void setLowWithException() throws DeviceIOException;

    boolean isHigh();

    boolean isLow();

}
