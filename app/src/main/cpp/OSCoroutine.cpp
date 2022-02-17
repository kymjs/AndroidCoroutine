//
// Created by zhangtao on 2022/2/14.
//

#include "OSCoroutine.h"

OSCoroutine::OSCoroutine(JNIEnv *env, jobject jobj) {
    env->GetJavaVM(&(this->jvm));
    this->jCoroutine = env->NewGlobalRef(jobj);
    jclass jCoroutineClass = env->GetObjectClass(jCoroutine);
    jfieldID jCoroutineId = env->GetFieldID(jCoroutineClass, "coroutineId", "J");
    this->coroutineId = env->GetLongField(jCoroutine, jCoroutineId);
}

OSCoroutine::~OSCoroutine() {
}

void OSCoroutine::async(JNIEnv *env) {
    if (suspendState == NEED_RESUME) {
        resume(env);
    } else {
        suspendState = NONE;
        if (jvm->AttachCurrentThread(&env, NULL) != 0) {
            LOGD("faile to attach");
        }

        jclass jCoroutineClass = env->GetObjectClass(jCoroutine);
        jmethodID runId = env->GetMethodID(jCoroutineClass, "run", "()Ljava/lang/Object;");
        if (runId != nullptr) {
            suspendAwait(env, env->CallObjectMethod(jCoroutine, runId));
        } else {
            LOGD("No run method found in Coroutine");
        }
    }
}

void OSCoroutine::suspendAwait(JNIEnv *env, jobject result) {
    if (suspendState == SUSPEND) {
        if (setjmp(suspendPoint)) {
            await(env, result);
        } else {
            suspendState = NEED_RESUME;
            LOGD("挂起协程：%lld", coroutineId);
        }
    } else if (suspendState == NONE) {
        await(env, result);
    }
}

void OSCoroutine::await(JNIEnv *env, jobject result) {
    jclass jCoroutineClass = env->GetObjectClass(jCoroutine);
    jmethodID onAwaitMethod = env->GetMethodID(jCoroutineClass, "onAwait", "(Ljava/lang/Object;)V");
    if (onAwaitMethod != nullptr) {
        env->CallVoidMethod(jCoroutine, onAwaitMethod, result);
    }
    suspendState = FINISHED;
    LOGD("协程：%lld，执行完成", coroutineId);
    env->DeleteGlobalRef(jCoroutine);
}

void OSCoroutine::delay(jlong millis) {

}

void OSCoroutine::resume(JNIEnv *env) {
    LOGD("恢复协程%lld", coroutineId);
    suspendState = RESUMED;
    longjmp(suspendPoint, 1);
}
