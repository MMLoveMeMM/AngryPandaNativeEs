package com.panda.org.angrypandanativees;

import android.app.Activity;
import android.os.Bundle;

import com.panda.org.angrypandanativees.basic.BasicGLSurfaceView;

public class MainActivity extends Activity {

    private BasicGLSurfaceView mGLSurfaceView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mGLSurfaceView = new BasicGLSurfaceView(MainActivity.this);

        setContentView(mGLSurfaceView/*R.layout.activity_main*/);
    }

    @Override
    protected void onResume() {
        super.onResume();

        mGLSurfaceView.onResume();

    }

    @Override
    protected void onPause() {
        super.onPause();

        mGLSurfaceView.onPause();

    }


}
