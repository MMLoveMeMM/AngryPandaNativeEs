uniform mat4 uMVPMatrix; //总变换矩阵
// attribute vec3 aPosition;
uniform vec3 uCamera;           //摄像机位置
uniform vec3 uLightLocation;    //光源位置
attribute vec3 aPosition;       //顶点位置
attribute vec3 aNormal;         //顶点法向量

varying vec4 vAmbient;
void main()     
{                                   
   gl_Position = uMVPMatrix * vec4(aPosition,1);
   vAmbient = vec4(0.55, 0.15, 0.45, 1.0);    //设置环境光强度
}