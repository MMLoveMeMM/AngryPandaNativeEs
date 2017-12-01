package com.panda.org.nativerenderwrapper;

import android.app.Activity;
import android.os.Bundle;

public class NSActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(new NativeSurfaceView(NSActivity.this)/*R.layout.activity_ns*/);

    }
}
