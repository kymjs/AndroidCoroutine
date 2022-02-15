package com.kymjs.coroutine;

import java.util.concurrent.atomic.AtomicInteger;

public class Coroutine {
    private static final AtomicInteger count = new AtomicInteger();
    public final int coroutineId;

    public Coroutine() {
        coroutineId = count.incrementAndGet();
    }

    public <T> T run() {
        return null;
    }

    private native void async();

    public native <T> T await();

    public native void delay(long millis);
}
