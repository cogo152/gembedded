package com.comert.gembedded.api.device.gpio;

public interface ListenerCallBack {

    void onFalling(long timeStamp);

    void onRising(long timeStamp);

    void onTimeout();

    void onError();

}
