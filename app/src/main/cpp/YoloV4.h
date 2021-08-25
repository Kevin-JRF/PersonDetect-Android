#ifndef YOLOV4_H
#define YOLOV4_H

#include "ncnn/net.h"

namespace cv{
    typedef struct{
        int width;
        int height;
    }Size;
}

typedef struct {
    std::string name;
    int stride;
    std::vector<cv::Size> anchors;
}YoloLayerData;

typedef struct BoxInfo {
    float x1;
    float y1;
    float x2;
    float y2;
    float score;
    int label;
} BoxInfo;

class YoloV4 {
public:
    YoloV4(AAssetManager* mgr, const char* param, const char* bin);
    ~YoloV4();
    std::vector<BoxInfo> detect(JNIEnv* env, jobject image);
private:
    static std::vector<BoxInfo> decode_infer(ncnn::Mat &data,const cv::Size& frame_size);
    ncnn::Net* Net;
    int input_size = 640;
public:
    static YoloV4 *detector;
};
#endif