package com.comert.gembedded.api.device.pwm;

import com.comert.gembedded.api.device.DeviceConstant;

public enum PWMMode implements DeviceConstant {

    DEFAULT((byte) 0, "Default"),
    MARK_SPACE((byte) 1, "Mark-Space"),
    SERIALIZER((byte) 2,"Serializer");

    PWMMode(byte digit, String text) {
        this.digit = digit;
        this.text = text;
    }

    private final byte digit;

    private final String text;

    @Override
    public byte getDigit() {
        return digit;
    }

    @Override
    public String getText() {
        return text;
    }

}
