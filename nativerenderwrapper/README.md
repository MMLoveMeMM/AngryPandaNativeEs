这个测试样例,是将GLRender在native层实现,而android本身是在GLSurfaceView类
里面实现的GLThread,然后开了一个线程维持.

GLSurfaceView[java] GLThread[c++],GLRenderer[c++]

具体原理参照 :
https://github.com/MMLoveMeMM/AngryPandaEGL.git