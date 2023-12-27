package com.comert.gembedded.api.device.gpio;

import com.comert.gembedded.api.device.Pin;

public interface InputPinConfigurator {

    Pin getPin();

    PullUpDown getPullUpDown();

    static InputPinPropertyConfigurator getBuilder() {
        return new InputPinConfiguratorImpl.InputPinPropertyConfiguratorImpl();
    }

    interface InputPinPropertyConfigurator {

        InputPinPropertyConfigurator pin(Pin pin);

        InputPinPropertyConfigurator pullUpDown(PullUpDown pullUpDown);

        InputPinConfigurator build();

    }

}
