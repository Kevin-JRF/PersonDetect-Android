package com.e.yolo4

import android.app.Application
import android.graphics.Color
import android.graphics.RectF
import android.view.Display




class Box(val x0: Float, val y0: Float, val x1: Float, val y1: Float, val label: Int, val score: Float){

    fun getRect(): RectF {
        //原图宽为480，2.25f为适应1080p屏幕所得比例
        return RectF(x0 * 2.25f, y0 * 2.25f, x1 * 2.25f, y1 * 2.25f)
    }

}