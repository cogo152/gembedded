package com.comert.gembedded.provider.device.i2c;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import com.comert.gembedded.api.device.DeviceConfigurationException;
import com.comert.gembedded.api.device.DeviceIOException;
import com.comert.gembedded.api.device.i2c.I2CMasterConfigurator;
import com.comert.gembedded.api.device.provider.I2CMasterParent;
import com.comert.gembedded.device.nativeinterface.ConfigurationVisitor;
import com.comert.gembedded.device.nativeinterface.I2CMasterDriver;

public class I2CMasterImpl extends I2CMasterParent {

    private final ByteBuffer writeBuffer;

    private final ByteBuffer readBuffer;

    private final byte registerSelector;

    public I2CMasterImpl(I2CMasterConfigurator i2cMasterConfigurator) throws DeviceConfigurationException {
        writeBuffer = ByteBuffer.allocateDirect(16);
        writeBuffer.order(ByteOrder.nativeOrder());
        readBuffer = ByteBuffer.allocateDirect(16 * 4);
        readBuffer.order(ByteOrder.nativeOrder());
        i2cMasterConfigurator.setReadBuffer(readBuffer);
        i2cMasterConfigurator.setWriteBuffer(writeBuffer);
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(i2cMasterConfigurator);
        this.registerSelector = configurationVisitor.getI2CBusRegisterSelector(i2cMasterConfigurator);
    }

    @Override
    public synchronized void writeSlave(byte slaveAddress, byte dataToSend) {
        writeBuffer.put(0, dataToSend);
        I2CMasterDriver.sendData(registerSelector, slaveAddress, 1);
    }

    @Override
    public synchronized void writeSlaveWithException(byte slaveAddress, byte dataToSend) throws DeviceIOException {
        writeBuffer.put(0, dataToSend);
        I2CMasterDriver.sendDataWithException(registerSelector, slaveAddress, 1);
    }

    @Override
    public synchronized int readSlave(byte slaveAddress) {
        I2CMasterDriver.receiveData(registerSelector, slaveAddress, 1);
        return readBuffer.getInt(0);
    }

    @Override
    public synchronized int readSlaveWithException(byte slaveAddress) throws DeviceIOException {
        I2CMasterDriver.receiveDataWithException(registerSelector, slaveAddress, 1);
        return readBuffer.getInt(0);
    }

    @Override
    public synchronized int writeAndReadSlave(byte slaveAddress, byte dataToSend) {
        writeBuffer.put(0, dataToSend);
        I2CMasterDriver.sendAndReceiveData(registerSelector, slaveAddress, 1, 1);
        return readBuffer.getInt(0);
    }

    @Override
    public synchronized int writeAndReadSlaveWithException(byte slaveAddress, byte dataToSend)
            throws DeviceIOException {
        writeBuffer.put(0, dataToSend);
        I2CMasterDriver.sendAndReceiveDataWithException(registerSelector, slaveAddress, 1, 1);
        return readBuffer.getInt(0);
    }

    @Override
    public synchronized void writeRegister(byte slaveAddress, byte registerAddress, byte dataToSend) {
        writeBuffer.put(0, registerAddress);
        writeBuffer.put(1, dataToSend);
        I2CMasterDriver.sendData(registerSelector, slaveAddress, 2);
    }

    @Override
    public synchronized void writeRegisterWithException(byte slaveAddress, byte registerAddress, byte dataToSend)
            throws DeviceIOException {
        writeBuffer.put(0, registerAddress);
        writeBuffer.put(1, dataToSend);
        I2CMasterDriver.sendDataWithException(registerSelector, slaveAddress, 2);
    }

    @Override
    public synchronized int readRegister(byte slaveAddress, byte registerAddress) {
        writeBuffer.put(0, registerAddress);
        I2CMasterDriver.sendAndReceiveData(registerSelector, slaveAddress, 1, 1);
        return readBuffer.getInt(0);
    }

    @Override
    public synchronized int readRegisterWithException(byte slaveAddress, byte registerAddress)
            throws DeviceIOException {
        writeBuffer.put(0, registerAddress);
        I2CMasterDriver.sendAndReceiveDataWithException(registerSelector, slaveAddress, 1, 1);
        return readBuffer.getInt(0);
    }

    @Override
    public synchronized int writeAndReadRegister(byte slaveAddress, byte registerAddress, byte dataToSend) {
        writeBuffer.put(0, registerAddress);
        writeBuffer.put(1, dataToSend);
        I2CMasterDriver.sendAndReceiveData(registerSelector, slaveAddress, 2, 1);
        return readBuffer.getInt(0);
    }

    @Override
    public synchronized int writeAndReadRegisterWithException(byte slaveAddress, byte registerAddress, byte dataToSend)
            throws DeviceIOException {
        writeBuffer.put(0, registerAddress);
        writeBuffer.put(1, dataToSend);
        I2CMasterDriver.sendAndReceiveDataWithException(registerSelector, slaveAddress, 2, 1);
        return readBuffer.getInt(0);
    }

    // Check if Bytebuffer can be passed as argument

    @Override
    public synchronized void sendData(byte slaveAddress, byte[] dataToSend) {
        writeBuffer.clear();
        writeBuffer.put(dataToSend);
        I2CMasterDriver.sendData(registerSelector, slaveAddress, dataToSend.length);
    }

    @Override
    public synchronized void sendDataWithException(byte slaveAddress, byte[] dataToSend) throws DeviceIOException {
        writeBuffer.clear();
        writeBuffer.put(dataToSend);
        I2CMasterDriver.sendDataWithException(registerSelector, slaveAddress, dataToSend.length);
    }

    @Override
    public synchronized void receiveData(byte slaveAddress, int[] dataToReceive) {
        final int dataToReceiveLength = dataToReceive.length;
        I2CMasterDriver.receiveData(registerSelector, slaveAddress, dataToReceiveLength);
        for (int i = 0; i < dataToReceive.length; i++) {
            dataToReceive[i] = readBuffer.getInt(i);
        }
    }

    @Override
    public synchronized void receiveDataWithException(byte slaveAddress, int[] dataToReceive) throws DeviceIOException {
        final int dataToReceiveLength = dataToReceive.length;
        I2CMasterDriver.receiveDataWithException(registerSelector, slaveAddress, dataToReceiveLength);
        for (int i = 0; i < dataToReceive.length; i++) {
            dataToReceive[i] = readBuffer.getInt(i);
        }

    }

    @Override
    public synchronized void sendAndReceiveData(byte slaveAddress, byte[] dataToSend, int[] dataToReceive) {
        writeBuffer.clear();
        writeBuffer.put(dataToSend);
        I2CMasterDriver.sendAndReceiveData(registerSelector, slaveAddress, dataToSend.length, dataToReceive.length);
        for (int i = 0; i < dataToReceive.length; i++) {
            dataToReceive[i] = readBuffer.getInt(i);
        }
    }

    @Override
    public synchronized void sendAndReceiveDataWithException(byte slaveAddress, byte[] dataToSend, int[] dataToReceive)
            throws DeviceIOException {
        writeBuffer.clear();
        writeBuffer.put(dataToSend);
        I2CMasterDriver.sendAndReceiveDataWithException(registerSelector, slaveAddress, dataToSend.length,
                dataToReceive.length);
        for (int i = 0; i < dataToReceive.length; i++) {
            dataToReceive[i] = readBuffer.getInt(i);
        }
    }

}
