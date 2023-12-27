package com.comert.gembedded.device.nativeinterface;

import com.comert.gembedded.api.device.DeviceConfigurationException;
import com.comert.gembedded.api.device.DeviceIOException;
import com.comert.gembedded.api.device.Pin;
import com.comert.gembedded.api.device.pwm.PWMMode;
import com.comert.gembedded.api.device.pwm.PWMSilence;
import com.comert.gembedded.api.device.pwm.PWMPolarity;

public abstract class PWMDriver {

    private PWMDriver() {
    }

    static native void setupPWMMDriver() throws DeviceConfigurationException;


    static native void shutdownPWMDriver() throws DeviceConfigurationException;

    static native void configurePWMPin(Pin pin, PWMMode pwmMode, PWMPolarity pwmPolarity, PWMSilence pwmSilence, int range) throws DeviceConfigurationException;

    static native byte getPWMPinRegisterSelector(byte pin);

    public static native void enablePWMPin(byte registerSelector);

    public static native void disablePWMPin(byte registerSelector);


    public static native void writePWMPinData(byte registerSelector, int data);


    public static native void writePWMPinDataWithException(byte registerSelector, int data) throws DeviceIOException;

}
