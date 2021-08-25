package com.e.yolo4

import android.content.res.AssetManager
import android.graphics.Bitmap

object Net {

    init{
        System.loadLibrary("yolov4")
    }

    external fun detect(bitmap: Bitmap): Array<Box>

    external fun initNet(assetManager: AssetManager)

}