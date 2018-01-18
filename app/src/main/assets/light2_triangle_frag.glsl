precision mediump float;
varying vec4 vAmbient;

void main()                         
{
    vec4 vFinalColor = vec4(1.0, 0.0, 1.0, 0.0);

    gl_FragColor = vFinalColor * vAmbient;  //通过环境光强度获得最终颜色
}