package com.panda.org.angrypandanativees.fog;

import android.app.Activity;
import android.os.Bundle;

import com.panda.org.angrypandanativees.R;

public class FogActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(new FogGLSurfaceView(FogActivity.this)/*R.layout.activity_fog*/);
    }
}
