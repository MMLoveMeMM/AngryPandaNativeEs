package com.panda.org.angrypandanativees.stencil;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

/**
 * Created by rd0348 on 2017/12/8 0008.
 */

public class GLStencilSurfaceView extends GLSurfaceView {

    private float mPreviousY;
    private float mPreviousX;
    StencilRenderer mRender;
    public GLStencilSurfaceView(Context context) {
        super(context);
        setEGLContextClientVersion(2);
        setEGLConfigChooser(8, 8, 8, 8, 16, 8);
        mRender = new StencilRenderer();
        setRenderer(mRender);
    }

    public boolean onTouchEvent(MotionEvent e) {
        float y = e.getY();
        float x = e.getX();
        switch (e.getAction()) {
            case MotionEvent.ACTION_MOVE:
                float dy = y - mPreviousY;
                float dx = x - mPreviousX;
                mRender.yAngle += dx;
                mRender.xAngle+= dy;
                requestRender();
        }
        mPreviousY = y;
        mPreviousX = x;
        return true;
    }

    public void setOpenStencilTest(boolean openStencilTest) {
        if(mRender!=null)
        {
            mRender.setOpenStencilTest(openStencilTest);
        }
    }


}
