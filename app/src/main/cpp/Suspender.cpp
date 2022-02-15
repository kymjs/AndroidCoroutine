//
// Created by zhangtao on 2022/2/11.
//

#include <cerrno>
#include "Suspender.h"

Suspender::Suspender() {
    pthread_mutex_init(&_mutex, NULL);
    pthread_cond_init(&_cond, NULL);
}

void Suspender::park(long millis) {
    struct timespec ts;
    struct timeval now;
    int status = pthread_mutex_lock(&_mutex);
    gettimeofday(&now, NULL);
    ts.tv_sec = time(NULL) + millis / 1000;
    ts.tv_nsec = now.tv_usec * 1000 + 1000 * 1000 * (millis % 1000);
    ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
    ts.tv_nsec %= (1000 * 1000 * 1000);
    status = pthread_cond_timedwait(&_cond, &_mutex, &ts);
    if (status == 0) {
        // success
    } else if (status == ETIMEDOUT) {
        // time out
    } else {
    }

    status = pthread_mutex_unlock(&_mutex);
}

void Suspender::unpark() {
    int status = pthread_mutex_lock(&_mutex);
    status = pthread_cond_signal(&_cond);
    status = pthread_mutex_unlock(&_mutex);
}
