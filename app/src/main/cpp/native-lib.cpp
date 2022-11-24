#include <jni.h>
#include <string>
#include <android/log.h>
#include "breakpad/src/client/linux/handler/minidump_descriptor.h"
#include "breakpad/src/client/linux/handler/exception_handler.h"


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jnicrashdemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

// crash 方法
void Crash(){
    volatile int *a = (int *) (NULL);
    *a = 1;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnicrashdemo_MainActivity_testCrash(JNIEnv *env, jclass clazz){
    __android_log_print(ANDROID_LOG_ERROR, "native", "Java_com_example_myapplication_MainActivity_testCrash");
    Crash(); // 调用crash
}

bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor, void* context, bool succeeded){
    __android_log_print(ANDROID_LOG_ERROR, "native", "DumpCallback");
    printf("Dump path: %s\n", descriptor.path());
    return false;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnicrashdemo_MainActivity_initNative(JNIEnv *env, jclass clazz, jstring path_){
    const char* path = env->GetStringUTFChars(path_, 0);
    google_breakpad::MinidumpDescriptor descriptor(path);
    static google_breakpad::ExceptionHandler eh(descriptor, NULL, DumpCallback, NULL, true, -1);
    env->ReleaseStringUTFChars(path_, path);
}
