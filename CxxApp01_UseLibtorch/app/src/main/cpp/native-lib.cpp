#include <jni.h>
#include <string>
#include <iostream>
#include "torch/torch.h"
extern "C" JNIEXPORT jstring JNICALL
Java_com_clumba_cxxapp01_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    torch::Tensor tensor = torch::rand({2, 3});
    std::cout <<"mycpp"<< tensor << std::endl;

    return env->NewStringUTF(hello.c_str());
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_clumba_cxxapp01_MainActivity_hhstringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    torch::Tensor tensor = torch::rand({3});
    std::cout << tensor << std::endl;

    return env->NewStringUTF(hello.c_str());
}