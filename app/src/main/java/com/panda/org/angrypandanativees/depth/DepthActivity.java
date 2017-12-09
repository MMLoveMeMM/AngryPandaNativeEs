package com.panda.org.angrypandanativees.depth;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.LinearLayout;

import com.panda.org.angrypandanativees.R;
import com.panda.org.angrypandanativees.blend.BlendActivity;
import com.panda.org.angrypandanativees.blend.GLBlendSurfaceView;

public class DepthActivity extends Activity {

    private Button mStencilBtn;
    private GLDepthSurfaceView mGLStencilSurfaceView;
    private CheckBox mCheckBox;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_stencil);

        LinearLayout layout=(LinearLayout)findViewById(R.id.container);
        mGLStencilSurfaceView=new GLDepthSurfaceView(DepthActivity.this);
        layout.addView(mGLStencilSurfaceView);

        mCheckBox=(CheckBox)findViewById(R.id.checkBox);
        mCheckBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    mCheckBox.setText("深度测试已开");
                }else{
                    mCheckBox.setText("深度测试已关");
                }
            }
        });
        mCheckBox.setText("深度测试已关");

        mStencilBtn=(Button)findViewById(R.id.button);
        mStencilBtn.setText("深度测试");
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
