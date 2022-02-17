#ifndef CORE_LOG_H
#define CORE_LOG_H

#define APP_NAME "com.kymjs.coroutine"
#define DEBUG 1

#ifdef __ANDROID__

#include <jni.h>
#include <android/log.h>

#ifdef DEBUG
#define LOGV(...) __android_log_print(2, APP_NAME, __VA_ARGS__)
#define LOGD(...) __android_log_print(3, APP_NAME, __VA_ARGS__)
#define LOGI(...) __android_log_print(4, APP_NAME, __VA_ARGS__)
#define LOGW(...) __android_log_print(5, APP_NAME, __VA_ARGS__)
#define LOGE(...) __android_log_print(6, APP_NAME, __VA_ARGS__)
#else
#define LOGV(...) {}
#define LOGD(...) {}
#define LOGI(...) {}
#define LOGW(...) {}
#define LOGE(...) {}
#endif

#else // __ANDROID__

///================= package define =====================
#define ARG_COUNT_PRIVATE(\
     _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, \
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
    _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
    _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
    _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
    _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
    _60, _61, _62, _63, _64, N, ...) N

#define ARG_COUNT(...)      ARG_COUNT_PRIVATE(0, __VA_ARGS__,\
    64, 63, 62, 61, 60, \
    59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
    49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
    39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
    29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
    19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
     9,  8,  7,  6,  5,  4,  3,  2,  1,  0)

#define FUN_COUNT_GLUE(M, count)     M##count
#define FUN_JOIN_COUNT(M, count)     FUN_COUNT_GLUE(M,count)
#define FUN_JOIN_ARGS(x, y)     x y

#define CallSomeOne(fn, ...)    FUN_JOIN_ARGS(FUN_JOIN_COUNT(fn, ARG_COUNT(__VA_ARGS__)), (__VA_ARGS__))

#if defined QS_LOG
#include "QsLog.h"
#define PR QLOG_INFO() // QsLog 输出（一个用Qt封装的日志类，挺好用的，在此推荐一下）
#define ENDL ""
#elif defined QT_CORE_LIB  // Qt 标准输出
#include <QDebug>
#define PR qDebug()
#define ENDL ""
#elif defined __cplusplus

#include <iostream>

using namespace std;
#define PR std::cout
#define ENDL std::endl
#endif

#define OUT_RED     "\033[0;31;1m"
#define OUT_GREEN   "\033[0;32;1m"
#define OUT_YELLOW  "\033[0;33;1m"
#define OUT_BLUE    "\033[0;34;1m"
#define OUT_END     "\033[0m"

#define FILE_INFO   "[" << __FILE__ << '@' << __FUNCTION__ << '#' << __LINE__  << "]"

#define param1(a)               #a":" << a
#define param2(a, b)             #a":" << a << ", "#b":" << b
#define param3(a, b, c)           #a":" << a << ", "#b":" << b << ", "#c":" << c
#define param4(a, b, c, d)         #a":" << a << ", "#b":" << b << ", "#c":" << c << ", "#d":" << d

#define pr0()           "null param out"
#define pr1(...)        param1(__VA_ARGS__)
#define pr2(...)        param2(__VA_ARGS__)
#define pr3(...)        param3(__VA_ARGS__)
#define pr4(...)        param4(__VA_ARGS__)
#define pr5(a, b, c, d, e)              pr3(a,b,c) << ", " << param2(d,e)
#define pr6(a, b, c, d, e, f)            pr3(a,b,c) << ", " << param3(d,e,f)
#define pr7(a, b, c, d, e, f, g)          pr4(a,b,c,d) << ", " << param3(e,f,g)
#define pr8(a, b, c, d, e, f, g, h)        pr4(a,b,c,d) << ", " << param4(e,f,g,h)
#define pr9(a, b, c, d, e, f, g, h, i)      pr8(a,b,c,d,e,f,g,h) << ", " << param1(i)
#define pr10(a, b, c, d, e, f, g, h, i, j)   pr9(a,b,c,d,e,f,g,h,i) << ", " << param1(j)
//....  有兴趣可以继续扩充

#define LOGV(x)       PR << FILE_INFO << x << ENDL  // 原样输出，无需格式化

#define LOGD(...)    PR << ""         << "DEBUG " << FILE_INFO << CallSomeOne(pr, __VA_ARGS__) << ENDL
#define LOGI(...)    PR << OUT_GREEN  << "INFO  " << FILE_INFO << CallSomeOne(pr, __VA_ARGS__) << OUT_END << ENDL
#define LOGW(...)    PR << OUT_YELLOW << "WARN  " << FILE_INFO << CallSomeOne(pr, __VA_ARGS__) << OUT_END << ENDL
#define LOGE(...)    PR << OUT_RED    << "ERROR " << FILE_INFO << CallSomeOne(pr, __VA_ARGS__) << OUT_END << ENDL
#endif // ANDROID_H

#endif //CORE_LOG_H

