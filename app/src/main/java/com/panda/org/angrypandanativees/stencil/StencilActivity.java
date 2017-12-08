package com.panda.org.angrypandanativees.stencil;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.LinearLayout;

import com.panda.org.angrypandanativees.R;

public class StencilActivity extends Activity {

    private Button mStencilBtn;
    private GLStencilSurfaceView mGLStencilSurfaceView;
    private CheckBox mCheckBox;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_stencil);

        LinearLayout layout=(LinearLayout)findViewById(R.id.container);
        mGLStencilSurfaceView=new GLStencilSurfaceView(StencilActivity.this);
        layout.addView(mGLStencilSurfaceView);

        mCheckBox=(CheckBox)findViewById(R.id.checkBox);

        mStencilBtn=(Button)findViewById(R.id.button);
        mStencilBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(mCheckBox.isChecked()==false){
                    mGLStencilSurfaceView.setOpenStencilTest(false);
                }else{
                    mGLStencilSurfaceView.setOpenStencilTest(true);
                }
            }
        });

    }
}
