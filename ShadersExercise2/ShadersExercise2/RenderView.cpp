//
//  RenderView.cpp
//  Shaders
//
//  Created by shenyuanluo on 2017/10/1.
//  Copyright © 2017年 shenyuanluo. All rights reserved.
//

#include "RenderView.h"
#include <math.h>



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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
    // 启动顶点属性
    glEnableVertexAttribArray(0);
    
    // 设置颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    // 启用颜色属性
    glEnableVertexAttribArray(1);
    
    
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
    // 创建着色器程序
    Shaders customShader("vs.glsl", "fs.glsl");
    
    GLuint VAO = createVAO();
    GLuint VBO = createVBO(vertexBuff, buffLen);
    
    // 定义 索引缓存数据数据
    GLuint indices[] =
    {
        0, 1, 2,
    };
    GLuint EBO = createEBO(indices, sizeof(indices));
    
    GLfloat offset = 0.5f;
    
    
    
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
        customShader.setFloat("xOffset", offset);
        
        glBindVertexArray(VAO);
        //        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void *)0);
        
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

