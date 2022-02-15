package com.kymjs.thread;

import java.util.concurrent.atomic.AtomicInteger;

public class LiteThread {
    private static final AtomicInteger count = new AtomicInteger();
    public final int threadId;

    public LiteThread() {
        threadId = count.incrementAndGet();
    }

    public void run() {
    }

    public void start() {
        startNative();
    }

    private native void startNative();

    public native void yield();

    public static native void sleep(long millis, int threadId);

    public native boolean isInterrupt();

    public native void interrupt();

    public native void resume();
}
