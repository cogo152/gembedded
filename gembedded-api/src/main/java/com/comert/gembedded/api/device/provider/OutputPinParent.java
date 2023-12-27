package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.gpio.OutputPin;
import com.comert.gembedded.api.util.InstanceCreationException;
import com.comert.gembedded.api.util.InstanceCreationValidator;

public abstract class OutputPinParent implements OutputPin {

    protected OutputPinParent() {
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
