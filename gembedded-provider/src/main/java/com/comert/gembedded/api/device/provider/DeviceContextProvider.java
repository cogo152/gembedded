package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.device.DeviceConfigurationException;
import com.comert.gembedded.api.device.provider.DeviceContextProviderParent;
import com.comert.gembedded.device.nativeinterface.ConfigurationVisitor;
import com.comert.gembedded.device.nativeinterface.DeviceDriver;

public final class DeviceContextProvider extends DeviceContextProviderParent {

    public DeviceContextProvider() {
    }

    @Override
    protected void _setupDevice() throws DeviceConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.setupDevice();
    }

    @Override
    protected void _shutdownDevice() throws DeviceConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.shutdownDevice();
    }

    @Override
    protected String getDeviceName() {
        return DeviceDriver.getDeviceName();
    }

}
