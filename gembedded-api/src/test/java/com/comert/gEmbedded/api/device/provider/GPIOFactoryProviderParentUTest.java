package com.comert.gembedded.api.device.provider;

import com.comert.gembedded.api.ApplicationContextFactory;
import com.comert.gembedded.api.device.DeviceContext;
import com.comert.gembedded.api.device.gpio.GPIOFactory;
import com.comert.gembedded.api.util.InstanceExceptionMessage;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledForJreRange;
import org.junit.jupiter.api.condition.JRE;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.*;

@EnabledForJreRange(min = JRE.JAVA_17)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class GPIOFactoryProviderParentUTest {

    private DeviceContext deviceContext;

    @BeforeAll
    public void setUpTest(){
        deviceContext = ApplicationContextFactory.getDeviceContextInstance();
        deviceContext.setupDevice();
    }

    @AfterAll
    public void tearDownTest(){
        deviceContext.shutdownDevice();
    }

    @Test
    public void testFailWhenProviderIsBeingCreatedOutOfFactory() {
        final var desiredClass = DeviceContextProviderParent.class;

        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        GPIOFactoryProvider::new
                )
                .withMessage(InstanceExceptionMessage.OUT_OF_DESIRED_CLASS +" : "+desiredClass.getName());
    }

    @Test
    public void testSuccessWhenProviderIsBeingCreatedInFactoryClass() {
        assertDoesNotThrow(
                () -> ApplicationContextFactory.getDeviceContextInstance().getGPIOFactoryInstance()
        );
    }

    @Test
    public void testPool(){
        DeviceContext device = ApplicationContextFactory.getDeviceContextInstance();

        GPIOFactory factory = device.getGPIOFactoryInstance();

    }

}