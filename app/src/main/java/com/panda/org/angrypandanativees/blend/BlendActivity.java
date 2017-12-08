package com.panda.org.angrypandanativees.blend;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.LinearLayout;

import com.panda.org.angrypandanativees.R;
import com.panda.org.angrypandanativees.stencil.GLStencilSurfaceView;

public class BlendActivity extends Activity {

    private Button mStencilBtn;
    private GLBlendSurfaceView mGLStencilSurfaceView;
    private CheckBox mCheckBox;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_stencil);

        LinearLayout layout=(LinearLayout)findViewById(R.id.container);
        mGLStencilSurfaceView=new GLBlendSurfaceView(BlendActivity.this);
        layout.addView(mGLStencilSurfaceView);

        mCheckBox=(CheckBox)findViewById(R.id.checkBox);
        mCheckBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    mCheckBox.setText("混合已开");
                }else{
                    mCheckBox.setText("混合已关");
                }
            }
        });
        mCheckBox.setText("混合已关");

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
