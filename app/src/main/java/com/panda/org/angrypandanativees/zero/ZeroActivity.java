package com.panda.org.angrypandanativees.zero;

import android.app.Activity;
import android.os.Bundle;

import com.panda.org.angrypandanativees.R;

public class ZeroActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(new ZeroGLSurfaceView(ZeroActivity.this)/*R.layout.activity_zero*/);
    }

}
