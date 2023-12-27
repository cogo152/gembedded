package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.i2c.I2CMaster;
import com.comert.gembedded.api.util.InstanceCreationException;
import com.comert.gembedded.api.util.InstanceCreationValidator;

public abstract class I2CMasterParent implements I2CMaster {

    protected I2CMasterParent() {
        synchronized (this) {
            final var desiredClass = I2CMasterFactoryProviderParent.class;
            try {
                InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredClass);
            } catch (InstanceCreationException instanceCreationException) {
                throw new RuntimeException(instanceCreationException.getMessage());
            }
        }
    }

}
