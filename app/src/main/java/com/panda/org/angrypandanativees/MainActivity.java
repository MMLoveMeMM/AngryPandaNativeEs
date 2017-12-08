package com.panda.org.angrypandanativees;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.panda.org.angrypandanativees.basic.BasicGLSurfaceView;
import com.panda.org.angrypandanativees.blend.BlendActivity;
import com.panda.org.angrypandanativees.stencil.StencilActivity;
import com.panda.org.nativerenderwrapper.NSActivity;

public class MainActivity extends Activity implements View.OnClickListener{

    private BasicGLSurfaceView mGLSurfaceView;

    private Button mNSBtn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mGLSurfaceView = new BasicGLSurfaceView(MainActivity.this);

        setContentView(/*mGLSurfaceView*/R.layout.activity_main);

        mNSBtn=(Button)findViewById(R.id.nsbtn);
        mNSBtn.setOnClickListener(this);

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


    @Override
    public void onClick(View v) {

        int id=v.getId();
        switch (id)
        {
            case R.id.nsbtn:
                Intent intent = new Intent(MainActivity.this, BlendActivity.class/*StencilActivity.class*//*NSActivity.class*/);
                startActivity(intent);
                break;
        }

    }
}
