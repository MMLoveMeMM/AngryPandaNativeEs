package com.panda.org.angrypandanativees.multitexture;

import android.app.Activity;
import android.os.Bundle;

import com.panda.org.angrypandanativees.R;

public class MultitextureActivity extends Activity {

    private MultitextureSurfaceView mSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mSurfaceView=new MultitextureSurfaceView(MultitextureActivity.this);
        setContentView(mSurfaceView/*R.layout.activity_multitexture*/);

    }

    @Override
    protected void onResume() {
        super.onResume();
        mSurfaceView.onResume();
    }

    @Override
    protected void onStop() {
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
}
