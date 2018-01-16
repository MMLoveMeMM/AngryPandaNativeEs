package com.panda.org.angrypandanativees.light;

import android.app.Activity;
import android.os.Bundle;

import com.panda.org.angrypandanativees.R;

public class LightActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(new LightGLSurfaceView(LightActivity.this)/*R.layout.activity_light*/);
    }

}
