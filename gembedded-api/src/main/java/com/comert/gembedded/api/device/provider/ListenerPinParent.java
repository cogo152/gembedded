package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.gpio.ListenerPin;
import com.comert.gembedded.api.util.InstanceCreationException;
import com.comert.gembedded.api.util.InstanceCreationValidator;

public abstract class ListenerPinParent implements ListenerPin {

    protected ListenerPinParent() {
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
