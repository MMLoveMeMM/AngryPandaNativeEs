package com.panda.org.angrypandanativees.effecttexture;

import android.app.Activity;
import android.os.Bundle;

import com.panda.org.angrypandanativees.R;

public class EffectTextureActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(new EffectTextureSurfaceView(EffectTextureActivity.this)/*R.layout.activity_effect_texture*/);
    }
}
