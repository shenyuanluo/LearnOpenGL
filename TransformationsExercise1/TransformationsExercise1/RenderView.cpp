//
//  RenderView.cpp
//  Shaders
//
//  Created by shenyuanluo on 2017/10/1.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "RenderView.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


#pragma mark - Private
#pragma mark -- 窗体大小改变回调
void RenderView::frameBuffSizeCB(GLFWwindow* window, GLint width, GLint height)
{
    if (!window)
    {
        return;
    }
    // 告诉 OpenGL 渲染窗口的位置、大小（确保渲染大小跟窗体大小一致，也可用比窗体小，在视网膜显示屏时甚至比窗体大）
    glViewport(0, 0, width, height);
}


#pragma mark -- 处理用户输入
void RenderView::processInput(GLFWwindow* window)
{
    if (!window)
    {
        return;
    }
    // 判断用户是否按 ‘esc’ 按键，是则关闭窗体
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        // 关闭窗体
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


#pragma mark -- 创建顶点数组对象
GLuint RenderView::createVAO()
{
    // 声明一个引用 顶点数组对象 ID
    GLuint VAO  /* 顶点数组对象（Vertex Array Object） */;
    // 生成一个顶点数组对象(可包含：VBO，EBO，VertexAttribPointer )
    glGenVertexArrays(1, &VAO);
    
    // 绑定顶点数组对象在先，然后再绑定和设置顶点缓存对象，并且配置顶点属性
    // 绑定顶点数组对象
    glBindVertexArray(VAO);
    
    return VAO;
}


#pragma mark -- 创建顶点缓冲对象
GLuint RenderView:: createVBO(GLfloat* vertexBuff, GLuint buffLen)
{
    if (NULL == vertexBuff || 0 >= buffLen)
    {
        std::cout << "VertexBuff is NULL, can not create Vertex Buffer Object !" << std::endl;
        return 0;
    }
    // 声明一个引用 顶点缓存对象 ID
    GLuint VBO  /* 顶点缓冲对象（Vertex Buffer Object） */;
    
    // 生成一个 顶点缓存对象
    glGenBuffers(1, &VBO);
    
    // 绑定顶点缓存对象类型
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 拷贝顶点数据到顶点缓存对象ID引用的缓存中
    glBufferData(GL_ARRAY_BUFFER, buffLen, vertexBuff, GL_STATIC_DRAW);
    // 设置顶点属性 （告诉 OpenGL 如何解释使用顶点数据）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);
    // 启动顶点属性
    glEnableVertexAttribArray(0);
    
    // 设置颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    // 启用颜色属性
    glEnableVertexAttribArray(1);
    
    // 设置纹理属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)( 6 * sizeof(GLfloat)));
    // 启用纹理属性
    glEnableVertexAttribArray(2);
    
    
    return VBO;
}


#pragma mark -- 创建索引缓冲对象
GLuint RenderView::createEBO(GLuint* indexBuff, GLuint buffLen)
{
    if (NULL == indexBuff || 0 >= buffLen)
    {
        std::cout << "IndexBuff is NULL, can not create Element Buffer Object !" << std::endl;
        return 0;
    }
    // 声明一个引用 索引缓存对象 ID
    GLuint EBO  /* 索引缓冲对象（Element Buffer Object） */;
    // 生成一个 索引缓存对象
    glGenBuffers(1, &EBO);
    
    // 绑定 索引缓存对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 拷贝 索引数据到索引缓存对象 ID 引用的缓存中
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffLen, indexBuff, GL_STATIC_DRAW);
    
    return EBO;
}


#pragma mark -- 创建纹理对象
GLuint RenderView::createTexture(GLint internalformat, GLenum pixelFormat, const GLchar* imgName)
{
    // 声明一个引用 纹理对象 ID
    GLuint textureId;
    // 生成一个纹理对象
    glGenTextures(1, &textureId);
    // 绑定纹理对象
    glBindTexture(GL_TEXTURE_2D, textureId);
    /* ----- 设置纹理的环绕（wraping）/ 过滤（filtering） 选项 ----- */
    // 设置纹理‘S’轴环绕方式：重复
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // 设置纹理‘T’轴环绕方式：重复
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 设置纹理缩小（Minify）过滤方式：线性过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // 设置纹理放大（Magnify）过滤方式：线性过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // 加载并生成纹理
    GLint width;        // 纹理宽度
    GLint height;       // 纹理高度
    GLint nrChannels;   // 纹理颜色通道数
    // 将加载的纹理在‘y’轴上翻转（因为OpenGL要求y轴0.0坐标是在图片的底部的，但是图片的y轴0.0坐标通常在顶部。）
    stbi_set_flip_vertically_on_load(true);
    // 加载纹理图片
    GLubyte* imgData = stbi_load(imgName, &width, &height, &nrChannels, 0);
    if (imgData)
    {
        // 生成纹理数据
        glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, pixelFormat, GL_UNSIGNED_BYTE, imgData);
        // 生成多级渐远纹理
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // 成功生成纹理对象后，可以释放图像文件内存
    stbi_image_free(imgData);
    
    return textureId;
}


#pragma mark - Public
#pragma mark -- 初始化窗体
RenderView::RenderView(const GLuint width, const GLuint height, const GLchar* title):SCR_Width(width), SCR_Height(height), SCR_Title(title)
{
    // 初始化 GLFW
    if (!glfwInit())
    {
        std::cout << "Init GLFW failure !" << std::endl;
        return;
    }
    // 告诉 GLFW 使用的 OpenGL 版本为：3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 使用 OpenGL 的 Core-profile 模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__ // macOS 系统表示
    // 指定 OpenGL 上下文需向前兼容
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // 创建 GLFWWindow 对象
    this->window = glfwCreateWindow(SCR_Width, SCR_Height, SCR_Title, NULL, NULL);
    if (!this->window)
    {
        std::cout << "Create window failure ！" << std::endl;
        // 退出 GLFW
        glfwTerminate();
        return;
    }
    // 通知 GLFW 将窗体的上下文设置为当前线程的上下文
    glfwMakeContextCurrent(window);
    // 注册 GLFW widow 大小改变的回调函数
    glfwSetFramebufferSizeCallback(window, frameBuffSizeCB);
}


RenderView::~RenderView()
{
    window    = NULL;
    SCR_Title = NULL;
}


#pragma mark -- 初始化 GLAD
RetStatus RenderView::initGlad()
{
    // GLAD 是用来管理 OpenGL 的函数指针的，所以在调用任何 OpenGL 的 API 之前先需要初始化 GLAD 。（GLFW 给我们的是 glfwGetProcAddress， 它根据我们编译的系统定义正确的函数。）
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Init GLAD failure ！" << std::endl;
        return RetError;
    }
    return RetSuccess;
}


#pragma mark -- 渲染顶点数据
void RenderView::render(GLfloat* vertexBuff, GLuint buffLen)
{
    if (!window || !vertexBuff || 0 == buffLen)
    {
        std::cout << "Rendering failure !" << std::endl;
        return ;
    }
    
    // 定义 索引缓存数据数据
    GLuint indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // 创建着色器程序
    Shaders customShader("vs.glsl", "fs.glsl");
    
    GLuint VAO      = createVAO();
    GLuint VBO      = createVBO(vertexBuff, buffLen);
    GLuint EBO      = createEBO(indices, sizeof(indices));
    
    GLuint texture1 = createTexture(GL_RGB, GL_RGB, "container.jpg");
    GLuint texture2 = createTexture(GL_RGB, GL_RGBA, "awesomeface.png");

    customShader.use();
    // 设置 ‘texture1’ 纹理单元为：0
    customShader.setInt("texture1", 0);
    // 设置 ‘texture2’ 纹理单元为：1
    customShader.setInt("texture2", 1);
    
    // 如果想画线框，去掉下面的注释
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // 渲染循环
    while (!glfwWindowShouldClose(this->window))
    {
        // 处理输入
        processInput(this->window);
        
        //渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 状态设置函数
        glClear(GL_COLOR_BUFFER_BIT);           // 状态使用函数
        
        // -------------------------- 开始画三角形 --------------------------
        // 激活着色器程序
        customShader.use();
        
        // （在绑定纹理之前先）激活纹理单元
        glActiveTexture(GL_TEXTURE0);
        // 绑定纹理
        glBindTexture(GL_TEXTURE_2D, texture1);
        // 激活纹理单元
        glActiveTexture(GL_TEXTURE1);
        // 绑定纹理单
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        // 变换（注意，矩阵乘法是不遵守交换律的，这意味着它们的顺序很重要。建议在组合矩阵时，先进行缩放操作，然后是旋转，最后才是位移，否则它们会（消极地）互相影响。）
        // 【当矩阵相乘时，在最右边的矩阵是第一个与向量相乘的；应该从右向左读这个乘法。】（记住，实际的变换顺序应该与阅读顺序相反：尽管在代码中我们先位移再旋转，实际的变换却是先应用旋转再是位移的。）
        // 变换顺序：【缩放 ——> 旋转 ——> 位移】
        glm::mat4 trans;    // 定义一个矩阵（默认是单位矩阵）
        // 旋转 v(0.0f, 0.0f, 1.0f) 绕 ‘Z’ 轴旋转
        trans = glm::rotate(trans, (GLfloat)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        // 平移 v(0.5f, -0.5f, 0.0f)
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        // GLM 的默认布局是'列主序'，所以打印出来的是‘列主序’
//        std::cout << "2 trans = " << glm::to_string(trans) << std::endl;
        // 设定‘变换’矩阵的值
        customShader.setTrans("transform", glm::value_ptr(trans));
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // 交换缓存
        glfwSwapBuffers(window);
        // 检查是否有事件（键盘输入或鼠标移动）更新窗体状态
        glfwPollEvents();
    }
    
    // 释放对象
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    glfwTerminate();
}

