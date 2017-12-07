package com.panda.org.nativerenderwrapper;

import android.app.Activity;
import android.os.Bundle;

public class NSActivity extends Activity {

    private NativeSurfaceView mNativeSurfaceView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mNativeSurfaceView=new NativeSurfaceView(NSActivity.this);
        setContentView(mNativeSurfaceView/*R.layout.activity_ns*/);

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        /*
        * 这个地方打印日志,似乎程序都合理运行完
        * 但是始终会出现ANR
        * */
        // mNativeSurfaceView.surfaceDestroyed();
    }
}
