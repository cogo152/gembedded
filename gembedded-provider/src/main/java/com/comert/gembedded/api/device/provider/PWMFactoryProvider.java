package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.DeviceConfigurationException;
import com.comert.gembedded.api.device.pwm.PWMPinConfigurator;
import com.comert.gembedded.provider.device.pwm.PWMPinImpl;

public final class PWMFactoryProvider extends PWMFactoryProviderParent {

    @Override
    protected PWMPinParent _createPWMPin(PWMPinConfigurator pwmPinConfigurator) throws DeviceConfigurationException {
        return new PWMPinImpl(pwmPinConfigurator);
    }

}
