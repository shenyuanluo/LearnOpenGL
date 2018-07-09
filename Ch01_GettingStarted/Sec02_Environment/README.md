# OpenGL学习笔记（二）—— (macOS)环境搭建

## 版本说明
- Mac OS X : 10.12.6 
- GLFW : 3.2.1
- GLEW : 2.1.0

## 工具准备
1. 下载安装 [Xcode](https://developer.apple.com/xcode/)。
2. 安装 **Command Line Tool**

	``` bash
	$ xcode-select --install 
	```
3. 下载安装 `GUI` 版的 [CMake](https://cmake.org/download/)。
	![](Images/CmakeDownload.png)
	
## 简述
- [**OpenGL**](https://www.opengl.org/):（英语：Open Graphics Library）是用于渲染`2D`、`3D` 矢量图形的跨语言、跨平台（由 [Khronos组织](https://www.khronos.org/) 制定并维护）的**规范(Specification)**。
- [**GLFW**](http://www.glfw.org/)：是一个专门针对 `OpenGL` 的 **C** 语言库，提供了渲染物体所需的最低限度的接口。其允许用户创建 `OpenGL` 上下文，定义窗口参数以及处理用户输入，把物体渲染到屏幕所需的必要功能。（注意：`OpenGL` 并不规定窗口创建和管理的部分，这一部分完全交由 `GLFW` 来实现；还有其他类似的：[GLUT](https://www.opengl.org/resources/libraries/glut/) 和 [SDL](https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideoopengl.html) 等）。
- [**GLEW**](http://glew.sourceforge.net/)：由于 `OpenGL` 只是一种 **标准/规范**，并且是由驱动制造上在驱动中予以实现。`OpenGL` 的大多数函数在编译时*（compile-time）*是未知状态的，需要在运行时*（run-time）*来请求。`GLEW` 的工作就是获取所需的函数的地址，并储存在函数指针中供使用。（还有其他类似的：[GLAD](https://github.com/Dav1dde/glad)）。
- [**GLAD**](https://github.com/Dav1dde/glad)：是一个开源的库，功能跟 `GLEW` 类似。`GLAD` 使用了一个[在线服务](http://glad.dav1d.de/)（在这里能够告诉 `GLAD` 需要定义的 `OpenGL` 版本，并且根据这个版本加载所有相关的 `OpenGL` 函数）。
- [**SOIL**](http://www.lonesock.net/soil.html)：大多数图形学处理的任务都需要读取图片到内存当中。当前存在着各种各样的图片格式，例如 [jpeg](https://jpeg.org/), [bmp](https://zh.wikipedia.org/zh-hans/BMP), [png](https://zh.wikipedia.org/wiki/PNG) 等等；`SOIL` 提供了将图片加载到内存当中的功能，避免了因繁杂的图片格式读取问题。
- [**GLM**](http://glm.g-truc.net/)：提供了大量的矩阵变换，向量变换以及各种针对矩阵和向量的计算操作。

## `GLFW`编译安装

1. 下载**GLFW**[源码](http://www.glfw.org/download.html)，并解压。
2. 打开**CMake**，选择 *源代码目录* 和 *目标文件目录*。
	![](Images/GLFW_Cmake_Config.png)

3. 点击**Configure(设置)**按钮，让CMake读取设置和源代码，然后选择工程的生成器 *Unix Makefiles* 。
	![](Images/GLFW_Cmake_UnixMakefile.png)

4. CMake会显示可选的编译选项用来配置最终生成的库。这里使用默认设置，并再次点击Configure(设置)按钮保存设置。
	![](Images/GLFW_Cmake_Generate.png)

5. 保存之后，点击Generate(生成)按钮，生成的工程文件会在 `Build` 文件夹中。
	![](Images/GLFW_Cmake_Save.png)
	
	![](Images/GLFW_Cmake_Success.png)
	
	![](Images/GLFW_Cmake_Files.png)

6. 打开终端，`cd` 进入 **Build**目录

	``` bash
	$ cd GLFW_Build
	```
7. 执行 `make` 命令进行编译安装库文件。

	``` bash
	$ make
	```
	![](Images/GLFW_Compiling.png)
8. 执行 `make install` 命令进行安装，一般会安装到 `/usr/local/include` 和 `/usr/local/lib` 中。

	``` bash
	$ make instll
	```
	![](Images/GLFW_Installing.png)
9. 查看一下 `/usr/local/include`
	- 安装前：
		![](Images/GLFW_Include_Befor.png)
	- 安装后：	
		![](Images/GLFW_Include_After.png)
10. 查看一下 `/usr/local/lib`
	- 安装前：
		![](Images/GLFW_Lib_Before.png)
	- 安装后：	
		![](Images/GLFW_Lib_After.png)

> 至此，**Mac OS X** 下的 `GLFW` 环境已经配置好了

## `GLEW` 编译安装
1. 下载**GLEW**[源码](http://glew.sourceforge.net/)，并解压。
	![](Images/GLEWDownload.png)
	
	![](Images/GLEW_Source.png)
2. 打开终端，`cd` 进入 解压目录。

	``` bash
	$ cd GLEW_Source/glew-2.1.0
	```
3. 执行 `make` 命令进行编译安装库文件。

	``` bash
	$ make
	```
	![](Images/GLEW_Make.png)
	
	![](Images/GLEW_Source_Make_After.png)
4. 执行 `make install` 命令进行安装，一般会安装到 **/usr/local/include** 和 **/usr/local/lib** 中。

	``` bash
	$ make instll
	```
	![](Images/GLEW_Make_Install.png)

5. 查看一下 `/usr/local/include`
	- 安装前：
		![](Images/GLEW_Include_Before.png)
	- 安装后：	
		![](Images/GLEW_Include_After.png)
6. 查看一下 `/usr/local/lib`
	- 安装前：
		![](Images/GLEW_Lib_Before.png)
	- 安装后：	
		![](Images/GLEW_Lib_After.png)

> 至此，*Mac OS X* 下的 `GLEW` 环境已经配置好了

> **注意：** `glew` 头文件 必须在包含 `glfw`头文件之前，否则回报错：*gl.h included before glew.h*。

![](Images/GLEW_GLAD_Include_Error.png)

## `GLAD` 配置
1. 打开 `GLAD` 的[在线服务](http://glad.dav1d.de/)。
2. 将语言设置为 `C/C++`，在 **API** 选项中，选择 *3.3* 及以上的 `OpenGL` 版本。
3. 将模式 `Profile` 设置为 **Core** ，保证生成加载器 `Generate a loader` 选项是选中的。
4. 先暂时忽略拓展 `Extensions` 中内容。
5. 点击生成 `Generate` 。
	![](Images/GLAD_Config.png)

5. 下载生成的 **zip** 包（包含 **glad.c**、**glad.h** 和 **khrplatform.h**），解压后 `include` 目录下的 `glad` 和 `KHR` 文件夹**复制**到 `/usr/local/include`，`glad.c` 添加到项目中。
	![](Images/GLAD_Download.png)
	
	![](Images/GLAD_Source.png)
	
	![](Images/GLAD_Source_Include.png)
	
	![](Images/GLAD_Source_Include2.png)
6. 测试代码：

	```c
	#include <glad/glad.h>
	#include <GLFW/glfw3.h>
	
	int main()
	{
	    glfwInit();
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	    
	    return 0;
	}
	```

> **注意：** `glad` 头文件 必须在包含 `glfw`头文件之前，否则回报错：*OpenGL header already included, remove this include, glad already provides it*，而且不能与 `glew` 共同使用，否则也会报错：*gl.h included before glew.h*（`glad`头文件在`glew`头文件之前） 或 *OpenGL header already included, remove this include, glad already provides it*（`glad`头文件在`glew`头文件之后） 。

![](Images/GLEW_GLAD_Include_Error.png)

![](Images/GLEW_GLAD_Include_Error2.png)

## 使用
> 要在 **Xcode** 中调用相应的库函数，需要在 **Xcode** 工程中添加相应的*头文件*和*库文件*，这里有两种方式可以让 ***OpenGL*** 工程找到相应的库文件：

1. 将库的 `include` 和 `lib` 文件夹拷贝到 **Xcode** 本身的 `include` 和 `lib` 文件夹中（不推荐）。
2. 在新建的工程中链接库的 `include` 和 `lib` 文件。这样做更加清晰也更加易于管理，但是每次新建工程都要重新链接相应的库文件，如下:
	- 打开 **Xcode** 新建一个空工程或者 `Command Line Tool`。
	- 在工程的 **Build Settings** 中找到 *Header Search Paths*，将 `/usr/local/include` 添加到头文件搜索路径中，记得选上 `recursive` 。
	- 在工程的 **Build Settings** 中找到 *Library Search Paths*，将 `/usr/local/lib` 添加进来，记得选上 `recursive` 。

		![](Images/XcodeSearchPath.png)
	- 在工程的 **Build Phases** 中的 *Link Binary With Libraries* 中，添加以下几个库文件:
		- Cocoa.framework
		- OpenGL.framwork
		- GLUT.framework
		- CoreVideo.framework
		- IOKit.framework
		- libglfw3.a
		- libGLEW.a
	
		> **注意:** *libglfw3.a* 和 *libGLEW.a* 可能需要手动去 `/usr/local/lib` 中寻找添加。	
		![](Images/XcodeAddGlfw.png)
		
		![](Images/XcodeAddLibs.png)
	- **特别注意1：**需要将 `Build Settings` 里的 `Enable Modules(C and Objective-C)` 设为 **No**，否则 GLEW 头文件会报错：（/usr/local/include/GL/glew.h:16426:17: Declaration of ‘PFNGLCOPYTEXSUBIMAGE3DPROC’ must be imported from module ‘OpenGL.GL3’ before it is required）
		
		![](Images/GLEW_Head_Error.png)
		
		![](Images/GLEW_Module_NO.png)
	- **特别注意2：**请确认是在包含 `GLFW` 的头文件之前包含了 `GLAD` **或** `GLEW` 的头文件。`GLAD`/`GLEW`的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于 `OpenGL` 的头文件之前包含 `GLAD`/`GLEW`。
	
## 环境测试
1. 打开 **Xcode** 新建一个 `Command Line Tool` 的工程。
2. 配置环境。
3. 输入以下测试代码：，运行成功将会看到一个三角形。

	```Objective-C
	#import <Foundation/Foundation.h>
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
	
	void Render(void)
	{
	    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT);
	    glBegin(GL_TRIANGLES);
	    {
	        glColor3f(1.0,0.0,0.0);
	        glVertex2f(0, .5);
	        glColor3f(0.0,1.0,0.0);
	        glVertex2f(-.5,-.5);
	        glColor3f(0.0, 0.0, 1.0);
	        glVertex2f(.5, -.5);
	    }
	    glEnd();
	}
	
	int main(int argc, const char * argv[]) {
	    GLFWwindow* win;
	    if(!glfwInit()){
	        return -1;
	    }
	    win = glfwCreateWindow(640, 480, "OpenGL Base Project", NULL, NULL);
	    if(!win)
	    {
	        glfwTerminate();
	        exit(EXIT_FAILURE);
	    }
	    if(!glewInit())
	    {
	        return -1;
	    }
	    glfwMakeContextCurrent(win);
	    while(!glfwWindowShouldClose(win)){
	        Render();
	        glfwSwapBuffers(win);
	        glfwPollEvents();
	    }
	    glfwTerminate();
	    exit(EXIT_SUCCESS);
	    return 0;
	}
	```
	运行结果如下：
	![](Images/OpenGL_Triangle.png)

---
# 参考资料
- [https://learnopengl.com/](https://learnopengl.com/Getting-started/Creating-a-window)
- [guide for compiling GLFW](http://www.glfw.org/docs/latest/compile.html)
- [OpenGL 简介及环境配置](http://kaiyuan.me/2016/07/03/OpenGL_note1/)
- [在Mac系统上搭建OpenGL开发环境](http://aiplay.studio/2016-01-08-mac-config-opengl/)
- [Mac OpenGL踩坑记](http://www.yarpee.com/?p=192)
