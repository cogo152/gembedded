package com.comert.gembedded.provider.device.gpio;

import com.comert.gembedded.api.device.DeviceConfigurationException;
import com.comert.gembedded.api.device.DeviceIOException;
import com.comert.gembedded.api.device.gpio.OutputPinConfigurator;
import com.comert.gembedded.api.device.provider.OutputPinParent;
import com.comert.gembedded.device.nativeinterface.GPIODriver;
import com.comert.gembedded.device.nativeinterface.ConfigurationVisitor;

public final class OutputPinImpl extends OutputPinParent {

    private final byte registerSelector;
    private final int bitField;

    public OutputPinImpl(OutputPinConfigurator outputPinConfigurator) throws DeviceConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(outputPinConfigurator);
        this.registerSelector = configurationVisitor.getOutputPinRegisterSelector(outputPinConfigurator);
        this.bitField = configurationVisitor.getOutputPinBitField(outputPinConfigurator);
    }

    @Override
    public void setHigh() {
        GPIODriver.setPinHigh(registerSelector, bitField);
    }

    @Override
    public void setHighWithException() throws DeviceIOException {
        GPIODriver.setPinHighWithException(registerSelector, bitField);
    }

    @Override
    public void setLow() {
        GPIODriver.setPinLow(registerSelector, bitField);
    }

    @Override
    public void setLowWithException() throws DeviceIOException {
        GPIODriver.setPinLowWithException(registerSelector, bitField);
    }

    @Override
    public boolean isHigh() {
        return GPIODriver.isPinHigh(registerSelector, bitField);
    }

    @Override
    public boolean isLow() {
        return GPIODriver.isPinLow(registerSelector, bitField);
    }

}
