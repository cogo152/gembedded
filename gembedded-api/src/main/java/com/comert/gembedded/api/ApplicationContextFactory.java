package com.comert.gembedded.api;

import com.comert.gembedded.api.device.DeviceContext;
import com.comert.gembedded.api.util.ProviderException;
import com.comert.gembedded.api.device.provider.DeviceContextProviderParent;
import com.comert.gembedded.api.util.ProviderFactory;

public abstract class ApplicationContextFactory {

    private static DeviceContextProviderParent deviceContextProvider;

    private ApplicationContextFactory() {
    }

    /**
     * @return DeviceContext
     * @throws RuntimeException if provider does not obey the api rules.
     */
    public static synchronized DeviceContext getDeviceContextInstance() {
        if (deviceContextProvider == null) {
            final var providerParentClass = DeviceContextProviderParent.class;
            try {
                deviceContextProvider = ProviderFactory.createProviderAndUpcastToParentReference(providerParentClass);
            } catch (ProviderException providerException) {
                throw new RuntimeException(providerException.getMessage());
            }
        }
        return deviceContextProvider;
    }

}
