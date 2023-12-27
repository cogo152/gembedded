package com.comert.gembedded.api.device.gpio;

import com.comert.gembedded.api.device.Pin;

public interface OutputPinConfigurator {

    Pin getPin();

    static OutputPinPropertyConfigurator getBuilder() {
        return new OutputPinConfiguratorImpl.OutputPinPropertyConfiguratorImpl();
    }

    interface OutputPinPropertyConfigurator {

        OutputPinPropertyConfigurator pin(Pin pin);

        OutputPinConfigurator build();

    }

}
