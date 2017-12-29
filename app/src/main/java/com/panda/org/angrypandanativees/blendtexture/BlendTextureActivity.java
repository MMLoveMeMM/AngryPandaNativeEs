package com.panda.org.angrypandanativees.blendtexture;

import android.app.Activity;
import android.os.Bundle;

import com.panda.org.angrypandanativees.R;

public class BlendTextureActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(new BlendTextureSurfaceView(BlendTextureActivity.this)/*R.layout.activity_blend_texture*/);
    }

}
