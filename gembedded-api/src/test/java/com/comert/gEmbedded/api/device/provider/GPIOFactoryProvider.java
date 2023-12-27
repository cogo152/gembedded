package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.DeviceConfigurationException;
import com.comert.gembedded.api.device.gpio.InputPinConfigurator;
import com.comert.gembedded.api.device.gpio.OutputPinConfigurator;
import com.comert.gembedded.api.device.gpio.ListenerPinConfigurator;
import org.junit.jupiter.api.Disabled;

@Disabled
public class GPIOFactoryProvider extends GPIOFactoryProviderParent {

    public GPIOFactoryProvider() {
    }

    @Override
    protected InputPinParent _createDigitalInputPin(InputPinConfigurator digitalInputPinConfigurator) throws DeviceConfigurationException {
        return null;
    }

    @Override
    protected ListenerPinParent _createListenerPin(ListenerPinConfigurator listenerPinConfigurator) throws DeviceConfigurationException {
        return null;
    }

    @Override
    protected OutputPinParent _createDigitalOutputPin(OutputPinConfigurator digitalOutputPinConfigurator) throws DeviceConfigurationException {
        return null;
    }


}
