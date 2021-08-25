#include <jni.h>
#include <string>
#include <ncnn/gpu.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include "YoloV4.h"

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    ncnn::create_gpu_instance();
    return JNI_VERSION_1_4;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved)
{
    ncnn::destroy_gpu_instance();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_e_yolo4_Net_initNet(JNIEnv *env, jobject thiz, jobject assetManager) {
    if(YoloV4::detector == nullptr){
        AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
        YoloV4::detector = new YoloV4(mgr,"model.param","model.bin");
    }
}
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_e_yolo4_Net_detect(JNIEnv *env, jobject thiz, jobject bitmap) {
    auto result = YoloV4::detector->detect(env,bitmap);
    auto box_cls = env->FindClass("com/e/yolo4/Box");
    auto cid = env->GetMethodID(box_cls, "<init>", "(FFFFIF)V");
    jobjectArray ret = env->NewObjectArray( result.size(), box_cls, nullptr);
    int i = 0;
    for(auto& box:result){
        env->PushLocalFrame(1);
        jobject obj = env->NewObject(box_cls, cid,box.x1,box.y1,box.x2,box.y2,box.label,box.score);
        obj = env->PopLocalFrame(obj);
        env->SetObjectArrayElement( ret, i++, obj);
    }
    return ret;
}