package com.comert.gembedded.provider.device.gpio;

import com.comert.gembedded.api.device.DeviceConfigurationException;
import com.comert.gembedded.api.device.gpio.InputPinConfigurator;
import com.comert.gembedded.api.device.provider.InputPinParent;
import com.comert.gembedded.device.nativeinterface.GPIODriver;
import com.comert.gembedded.device.nativeinterface.ConfigurationVisitor;

public final class InputPinImpl extends InputPinParent {

    private final byte registerSelector;
    private final int bitField;

    public InputPinImpl(InputPinConfigurator inputPinConfigurator) throws DeviceConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(inputPinConfigurator);
        this.registerSelector = configurationVisitor.getInputPinRegisterSelector(inputPinConfigurator);
        this.bitField = configurationVisitor.getInputPinBitField(inputPinConfigurator);
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
