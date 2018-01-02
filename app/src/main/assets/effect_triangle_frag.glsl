precision mediump float;
uniform sampler2D uTexture;
varying vec2 vCoordTexture;
const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);
// 参考 : https://www.cnblogs.com/mazhenyu/p/6707954.html
void main() {
    lowp vec4 textureColor = texture2D(uTexture, vCoordTexture);
    float luminance = dot(textureColor.rgb, W);
    gl_FragColor = vec4(vec3(luminance), textureColor.a);
}


