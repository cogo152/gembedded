package com.comert.gembedded.api.device.i2c;

import java.nio.ByteBuffer;

import com.comert.gembedded.api.device.Pin;

public interface I2CMasterConfigurator {

    I2CBus getBus();

    int getBusClockInHertz();

    int getSlaveWaitClockTimeout();

    Pin getSDAPin();

    Pin getSCLPin();

    int getSCLFallingEdgeClockDelay();

    int getSCLRisingEdgeClockDelay();

    void setWriteBuffer(ByteBuffer writeBuffer);

    ByteBuffer getWriteBuffer();

    void setReadBuffer(ByteBuffer readBuffer);

    ByteBuffer getReadBuffer();

    static I2CMasterPropertyConfigurator getBuilder() {
        return new I2CMasterConfiguratorImpl.I2CMasterPropertyConfiguratorImpl();
    }

    interface I2CMasterPropertyConfigurator {

        I2CMasterPropertyConfigurator bus(I2CBus i2CBus);

        I2CMasterPropertyConfigurator busClockInHertz(int busClockInHertz);

        I2CMasterPropertyConfigurator slaveWaitClockTimeout(int slaveWaitClockTimeout);

        I2CMasterPropertyConfigurator sdaPin(Pin sdaPin);

        I2CMasterPropertyConfigurator sclPin(Pin sclPin, int fallingEdgeClockDelay, int risingEdgeClockDelay);

        I2CMasterConfigurator build();

    }

}
