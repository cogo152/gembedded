package com.comert.gembedded.api.device.gpio;

public interface ListenerPin {

    void start();

    void suspend();

    void resume();

    void terminate();

    boolean isStarted();

    boolean isSuspended();

    boolean isResumed();

    boolean isTerminated();

}
