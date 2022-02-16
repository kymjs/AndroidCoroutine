package com.kymjs.coroutine;

import java.util.concurrent.atomic.AtomicLong;

public class Coroutine {
    private static final AtomicLong count = new AtomicLong();
    public final long coroutineId;
    public final long threadId;

    public Coroutine() {
        this(Thread.currentThread().getId());
    }

    public Coroutine(long id) {
        coroutineId = count.incrementAndGet();
        threadId = id;
        init(threadId);
    }

    public <T> void onAwait(T result) {
    }

    public Object run() {
        return null;
    }

    private native void init(long threadId);

    public native void async();

    public native void delay(long millis);
}
