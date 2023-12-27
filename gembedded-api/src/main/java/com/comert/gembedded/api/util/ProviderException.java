package com.comert.gembedded.api.util;

import com.comert.gembedded.api.ApplicationException;
public final class ProviderException extends ApplicationException {
    public ProviderException(ProviderMessage providerMessage, String property) {
        super(providerMessage, property);
    }

}
