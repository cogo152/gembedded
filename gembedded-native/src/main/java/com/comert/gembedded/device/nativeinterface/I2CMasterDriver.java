package com.comert.gembedded.device.nativeinterface;

import java.nio.ByteBuffer;

import com.comert.gembedded.api.device.DeviceConfigurationException;
import com.comert.gembedded.api.device.DeviceIOException;
import com.comert.gembedded.api.device.Pin;
import com.comert.gembedded.api.device.i2c.I2CBus;

public abstract class I2CMasterDriver {

    private I2CMasterDriver() {
    }

    static native void setupI2CMasterDriver() throws DeviceConfigurationException;

    static native void shutdownI2CMasterDriver() throws DeviceConfigurationException;

    static native void configureMaster(
            I2CBus i2cBus,
            int busClockInHertz,
            int slaveWaitClockTimeout,
            Pin sdaPin,
            Pin sclPin,
            int sclFallingEdgeClockDelay,
            int sclRisingEdgeClockDelay,
            ByteBuffer writeBuffer,
            ByteBuffer readBuffer) throws DeviceConfigurationException;

    static native byte getI2CBusRegisterSelector(byte i2cBus);

    public static native void sendData(byte registerSelector, byte slaveAddress, int dataToSendSize);

    public static native void sendDataWithException(byte registerSelector, byte slaveAddress, int dataToSendSize)
            throws DeviceIOException;

    public static native void receiveData(byte registerSelector, byte slaveAddress, int dataToReceiveSize);

    public static native void receiveDataWithException(byte registerSelector, byte slaveAddress, int dataToReceiveSize)
            throws DeviceIOException;

    public static native void sendAndReceiveData(byte registerSelector, byte slaveAddress, int dataToSendSize,
            int dataToReceiveSize);

    public static native void sendAndReceiveDataWithException(byte registerSelector, byte slaveAddress,
            int dataToSendSize, int dataToReceiveSize) throws DeviceIOException;

}
