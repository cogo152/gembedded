package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.gpio.InputPin;
import com.comert.gembedded.api.util.InstanceCreationException;
import com.comert.gembedded.api.util.InstanceCreationValidator;

public abstract class InputPinParent implements InputPin {

    protected InputPinParent() {
        synchronized (this) {
            final var desiredClass = GPIOFactoryProviderParent.class;
            try {
                InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredClass);
            } catch (InstanceCreationException instanceCreationException) {
                throw new RuntimeException(instanceCreationException.getMessage());
            }
        }

    }

}
