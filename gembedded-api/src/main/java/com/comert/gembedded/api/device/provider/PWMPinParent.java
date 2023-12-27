package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.pwm.PWMPin;
import com.comert.gembedded.api.util.InstanceCreationException;
import com.comert.gembedded.api.util.InstanceCreationValidator;

public abstract class PWMPinParent implements PWMPin {

    protected PWMPinParent() {
        synchronized (this) {
            final var desiredClass = PWMFactoryProviderParent.class;
            try {
                InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredClass);
            } catch (InstanceCreationException instanceCreationException) {
                throw new RuntimeException(instanceCreationException.getMessage());
            }
        }

    }

}
