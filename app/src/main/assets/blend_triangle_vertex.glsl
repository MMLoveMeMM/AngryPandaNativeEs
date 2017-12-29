uniform mat4 uMVPMatrix;
attribute vec3 aPosition;
attribute vec2 aCoordTexture;
varying vec2 vCoordTexture;
varying vec2 vBlendTexture;
uniform float uType;
varying float vType;
void main() {

    gl_Position=uMVPMatrix * vec4(aPosition,1);
    vCoordTexture=aCoordTexture;
    vType=uType;
}