# OpenGL学习笔记（一）—— 窗体
> 在 [Mac平台搭建OpenGL开发环境](http://blog.shenyuanluo.com/OpenGLEnvironment.html) 一文中，已经配置好了 Mac 平台的 OpenGL 环境。在使用 OpenGL 开始渲染目标图像之前，需要做的就是找一个渲染的 **载体** 进行渲染；GLFW 是一个很好的选择。`GLFW` 是一个专门针对 `OpenGL` 的 `C` 语言库，它提供了渲染物体所需的最低限度的接口。它允许用户创建 `OpenGL` 上下文、定义窗口参数以及处理用户输入，把物体渲染到屏幕所需的必要功能，（注意：`OpenGL` 并不规定窗口创建和管理的部分，这一部分完全交由 `GLFW` 来实现。）


---


## 环境说明
- `Mac OS X` : 10.12.6
- `GLFW` : 3.2.1
- `GLAD` : 3.3
- `Xcode` : 8.4


## 使用 GLFW 要点
1. 使用之前需要对其进行初始化；

	``` C
	glfwInit();
	```
2. 告诉 `GLFW` 所使用的 `OpenGL` 版本以及模式（如果是 `Apple` 则还需要向前兼容）；

	``` C
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	#endif
	```
3. 指定 `OpenGL` 上下文；

	``` C
	glfwMakeContextCurrent(window);
	```
4. 注册相关回调函数；
	- 窗体大小改变回调；

		``` C
		glfwSetFramebufferSizeCallback(window, frameBufferSizeCB);
		```
	- 错误回调；

		``` C
		glfwSetErrorCallback(errorCallback);
		```
		
5. 在使用 `OpenGL` 相关 API 之前，必需先初始化 `GLAD`；

	``` C
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)
	```
6. 开始渲染：
	- 在渲染循环中处理相关输入：键盘、鼠标。。。
	- 设置帧缓存清除时窗体背景颜色，避免帧切换时还出现上一帧内容；

		``` C
		glClearColor(0.2, 0.3, 0.3, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		```


---


# 参考资料
1. [learnopengl.com](https://learnopengl.com/Getting-started/Hello-Window)