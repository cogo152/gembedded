package com.comert.gembedded.api.testutil;

import org.junit.jupiter.api.Disabled;

@Disabled
@FunctionalInterface
public interface InstanceProducer<I> {
    I getInstance();
}
