package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.DeviceConfigurationException;
import com.comert.gembedded.api.device.i2c.I2CMasterConfigurator;
import com.comert.gembedded.provider.device.i2c.I2CMasterImpl;

public final class I2CMasterFactoryProvider extends I2CMasterFactoryProviderParent {

    @Override
    protected I2CMasterParent _createI2Master(I2CMasterConfigurator i2cMasterConfigurator) throws DeviceConfigurationException {
        return new I2CMasterImpl(i2cMasterConfigurator);
    }

}
