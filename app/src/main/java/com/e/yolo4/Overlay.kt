package com.e.yolo4

import android.content.Context
import android.graphics.*
import android.util.AttributeSet
import android.util.Log
import android.view.View

class Overlay: View{

    private var boxes: Array<Box>? = null

    private val boxPaint = Paint()

    constructor(context: Context) : super(context)

    constructor(context: Context, attributeSet: AttributeSet) : super(context, attributeSet)

    constructor(context: Context, attributeSet: AttributeSet, defStyleAttr: Int) : super(context, attributeSet, defStyleAttr)

    init {
        boxPaint.run {
            style = Paint.Style.STROKE
            strokeWidth = 2.0f
            textSize = 50.0f
            color = Color.WHITE
        }
    }


    override fun onDraw(canvas: Canvas?) {
        super.onDraw(canvas)

        boxes?.forEach { box ->
            canvas?.run {
                drawRect(box.getRect(), boxPaint)
                drawText(String.format("%.2f",box.score),box.x0 * 2.25f,box.y0 * 2.25f,boxPaint)
            }
        }
    }


    fun setData(boxes: Array<Box>){
        this.boxes = boxes
    }

}