package com.comert.gembedded.api.device.pwm;

public interface PWMFactory {

    PWMPin createPWMPin(PWMPinConfigurator pwmPinConfigurator);

}
