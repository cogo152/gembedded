package com.comert.gembedded.api.util;

import com.comert.gembedded.api.ApplicationException;

public final class InstanceCreationException extends ApplicationException {

    public InstanceCreationException(InstanceMessage instanceMessage, String property) {
        super(instanceMessage, property);
    }

}
