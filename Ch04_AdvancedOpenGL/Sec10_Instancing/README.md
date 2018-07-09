# OpenGL学习笔记（三十）—— Instancing

---

## 实例化
在使用 `glDrawArrays` 或 `glDrawElements` 函数绘制顶点数据时，`OpenGL` 需要告诉 `OpenGL` 从哪里读取数据以及从哪里找顶点属性，这会非常消耗性能（因为这些操作都是在相对缓慢的 `CPU` 到 `GPU` 总线( **CPU to GPU Bus** )上进行的）。 

这就导致一个问题，在绘制一个包含非常多（相同）模型的场景时，代码大致如下：

``` C
for(GLuint i = 0; i < amount_of_models_to_draw; i++)
{
    DoSomePreparations(); // 绑定VAO，绑定纹理，设置uniform等
    glDrawArrays(GL_TRIANGLES, 0, amount_of_vertices);
}
```
这样，即使渲染（如，绘制简单的三角形）是瞬间完成的，但是在如此浩瀚的模型渲染时，更多的性能都消耗在了 `CPU` 到 `GPU` 总线上了。实例化就可以很好的解决此类问题。

**实例化(Instancing)：**将数据一次性发送给 `GPU`，然后使用一个绘制函数（`glDrawArraysInstanced` 或 `glDrawElementsInstanced`）让 `OpenGL` 利用这些数据绘制多个相同的物体。

**gl_InstanceID：**每个实例都有唯一的 `ID`，在使用实例化渲染调用时，`gl_InstanceID` 会从 `0` 开始，在每个实例被渲染时递增 `1`。


### 例子，绘制100个2D四边形
1. 顶点着色器：

	``` C
	#version 330 core       /* 指定 GLSL 版本3.3，匹配 OpenGL 版本 */
	
	layout (location = 0) in vec2 aPos;     /* 顶点位置变量的属性位置值为：0 */
	layout (location = 1) in vec3 aColor;   /* 顶点颜色变量的属性位置值为：1 */
	
	out vec3 fColor;    // 输出，颜色
	
	uniform vec2 offsets[100];  // 偏移
	
	void main()
	{
	    /* 顶点着色器内建变量：‘gl_InstanceID’
	     在使用实例化渲染调用(glDrawArraysInstanced 和 glDrawElementsInstanced)时，
	     gl_InstanceID 会从 0 开始，在每个实例被渲染时递增 1 */
	    vec2 offset = offsets[gl_InstanceID];
	    gl_Position = vec4(aPos + offset, 0.0, 1.0);
	    fColor = aColor;
	}
	```
2. 片段着色器：

	``` C
	#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */
	
	in vec3 fColor;         /* 输入，颜色值 */
	
	out vec4 FragColor;     /* 输出，指定片段颜色 */
	
	void main()
	{
	    FragColor = vec4(fColor, 1.0);
	}
	```
3. 偏移量计算并给 uniform 赋值：

	``` C
	// 计算 100 个偏移量
    glm::vec2 translations[100];
    GLint index = 0;
    GLfloat offset = 0.1f;
    for(GLint y = -10; y < 10; y += 2)
    {
        for(GLint x = -10; x < 10; x += 2)
        {
            glm::vec2 translation;
            translation.x = (GLfloat)x / 10.0f + offset;
            translation.y = (GLfloat)y / 10.0f + offset;
            translations[index++] = translation;
        }
    }
    // 100 个 uniform 偏移量赋值
    for(GLuint i = 0; i < 100; i++)
    {
        std::stringstream ss;
        std::string index;
        ss << i;
        index = ss.str();
        quadShader.setUniformVec2(("offsets[" + index + "]").c_str(), translations[i]);
    }
	```
4. 绘制：

	``` C
	quadShader.use();
   glBindVertexArray(quadVAO);
   glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
	```


## 实例化数组
> 发送至着色器的 `uniform` 数据大小是有 [上限](https://www.khronos.org/opengl/wiki/Uniform_(GLSL)#Implementation_limits) 的。

**实例化数组(Instanced Array)：**定义为一个顶点属性（可以储存更多的数据），切仅在顶点着色器渲染一个新的实例时才会更新，是解决 `uniform` 数据大小上限的一个代替方案。

使用常规顶点属性时，顶点着色器的每次运行（如，渲染每个顶点）都会让 `GLSL` 获取新一组适用于当前顶点的属性。而当将顶点属性定义为一个实例化数组时，顶点着色器就只需要对每个实例，而不是每个顶点，更新顶点属性的内容。

### 例子，绘制100个2D四边形 - 优化
1. 顶点着色器：

	``` C
	#version 330 core       /* 指定 GLSL 版本3.3，匹配 OpenGL 版本 */

	layout (location = 0) in vec2 aPos;     /* 顶点位置变量的属性位置值为：0 */
	layout (location = 1) in vec3 aColor;   /* 顶点颜色变量的属性位置值为：1 */
	layout (location = 2) in vec2 aOffset;  /* 顶点偏移量的属性位置值为：2 */
	
	out vec3 fColor;    // 输出，颜色
	
	void main()
	{	    
	    gl_Position = vec4(aPos + aOffset, 0.0, 1.0);
	    fColor = aColor;
	}
	```
2. 计算偏移并存储实例化数组至顶点缓冲对象：

	``` C
	// 计算 100 个偏移量
   glm::vec2 translations[100];
   GLint index = 0;
   GLfloat offset = 0.1f;
   for(GLint y = -10; y < 10; y += 2)
   {
       for(GLint x = -10; x < 10; x += 2)
       {
           glm::vec2 translation;
           translation.x = (GLfloat)x / 10.0f + offset;
           translation.y = (GLfloat)y / 10.0f + offset;
           translations[index++] = translation;
       }
   }
   /* 存储实例化数组至顶点缓存对象 */
   GLuint instanceVBO;
   glGenBuffers(1, &instanceVBO);
   glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
	```
3. 设置实例化数组顶点属性制作，并启用顶点属性：

	``` C
   glBindVertexArray(quadVAO);
   glEnableVertexAttribArray(2);
   glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   /* 函数告诉了 OpenGL 该什么时候更新顶点属性的内容至新一组数据
     第一个参数是需要的顶点属性，第二个参数是属性除数(Attribute Divisor)：
     默认情况下，属性除数是 0，告诉 OpenGL 在顶点着色器的每次迭代(如，渲染每个顶点)时更新顶点属性。
     将其设置为 1 时，告诉 OpenGL 在渲染一个新实例的时候更新顶点属性。
     将其设置为 2 时，告诉 OpenGL 在每 2 个实例更新一次属性，以此类推。*/
   glVertexAttribDivisor(2, 1);
	```


---


# 参考
教程来源：[https://learnopengl.com/](https://learnopengl.com/Advanced-OpenGL/Instancing)。