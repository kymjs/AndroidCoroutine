//
// Created by zhangtao on 2022/2/11.
//

#include "pthread.h"

#ifndef COROUTINE_PARKER_H
#define COROUTINE_PARKER_H

class Suspender {
private:
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;

public:
    Suspender();

    void park(long millis);

    void unpark();

};


#endif //COROUTINE_PARKER_H
