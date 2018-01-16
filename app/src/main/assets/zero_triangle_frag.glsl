precision mediump float;
uniform sampler2D uTexture;
varying vec2 vCoordTexture;
varying float vType;
//const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

const float uD = 80.0; //旋转角度
const float uR = 0.5; //旋转半径

const vec2 TexSize = vec2(400.0, 400.0);
const vec2 mosaicSize = vec2(8.0, 8.0);

const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

// 选择纹理区域内做不通的处理
void main() {

    if(vCoordTexture.x<0.25f && vCoordTexture.y<0.25f){
        gl_FragColor = texture2D(uTexture,vCoordTexture);
    }else if(vCoordTexture.x>0.25f && vCoordTexture.y>0.25f){
        vec4 textcolor=texture2D(uTexture,vCoordTexture);
        float lun=dot(textcolor.rgb,W);
        gl_FragColor=vec4(vec3(lun),textcolor.a);
    }else{
        gl_FragColor=vec4(1.0,0.0,0.0,1.0);
    }


}