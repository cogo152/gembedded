package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.DeviceConfigurationException;
import com.comert.gembedded.api.device.gpio.InputPinConfigurator;
import com.comert.gembedded.api.device.gpio.ListenerPinConfigurator;
import com.comert.gembedded.api.device.gpio.OutputPinConfigurator;
import com.comert.gembedded.provider.device.gpio.InputPinImpl;
import com.comert.gembedded.provider.device.gpio.ListenerPinImpl;
import com.comert.gembedded.provider.device.gpio.OutputPinImpl;

public final class GPIOFactoryProvider extends GPIOFactoryProviderParent {

    @Override
    protected InputPinParent _createInputPin(InputPinConfigurator inputPinConfigurator) throws DeviceConfigurationException {
        return new InputPinImpl(inputPinConfigurator);
    }

    @Override
    protected ListenerPinParent _createListenerPin(ListenerPinConfigurator listenerPinConfigurator) throws DeviceConfigurationException {
        return new ListenerPinImpl(listenerPinConfigurator);
    }

    @Override
    protected OutputPinParent _createOutputPin(OutputPinConfigurator outputPinConfigurator) throws DeviceConfigurationException {
        return new OutputPinImpl(outputPinConfigurator);
    }

}
