precision mediump float;
uniform sampler2D uTexture;
varying vec2 vCoordTexture;
varying vec2 vBlendTexture;
varying float vType;
void main() {
    vec4 textureColor = texture2D(uTexture, vCoordTexture);
    gl_FragColor = textureColor;//vec4(vec3(luminance), textureColor.a);
}