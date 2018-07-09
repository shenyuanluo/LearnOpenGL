# OpenGL学习笔记（二十八）—— Advanced GLSL

---

## GLSL的内建变量
### 顶点着色器变量
- **gl_Position：**顶点着色器 *输出* 变量，类型：`vec4`，作用：设置裁剪空间输出位置向量。
- **gl_PointSize：**顶点着色器 *输出* 变量，类型：`float`，作用：设置点的宽高（像素）。（该功能默认禁止，需要启用 `GL_PROGRAM_POINT_SIZE`）
- **gl_VertexID：**顶点着色器 *输入* 变量，类型：`int`，作用：当使用 `glDrawElements` 进行索引渲染的时候，该变量会存储当前正在绘制顶点的 **索引**；而当使用 `glDrawArrays` 不使用索引进行绘制的时候，该变量会储存从渲染调用开始的已处理 **顶点数量**。
- **gl_InstanceID：**顶点着色器 *输入* 变量，类型：`unsigned int`，作用：获取当前实例化渲染调用( `glDrawArraysInstanced` 和 `glDrawElementsInstanced`)时正在渲染的是第几个实例（在使用实例化渲染时 `gl_InstanceID` 会从 `0` 开始，在每个实例被渲染时递增 `1`）。

### 片段着色器变量
- **gl_FragCoord：**片段着色器 *输入* 变量，类型：`vec3`，作用：获取片段的位置向量。（其中，`x` 和 `y` 分量是片段的窗口空间(Window-space)坐标，其原点为窗口的左下角；`z` 分量片段的深度值。）
- **gl_FrontFacing：**片段着色器 *输入* 变量，类型：`bool`，作用：标识当前片段是属于正面的一部分还是背面的一部分（前提是没有启用 *面剔除* `GL_FACE_CULL`）。
- **gl_FragDepth：**片段着色器 *输出* 变量，类型：`float`，作用：设置片段的深度值。（注意：如果着色器没有写入值到 `gl_FragDepth`，它会自动取用 `gl_FragCoord.z`的值；但是，只要在片段着色器中对 `gl_FragDepth` 进行写入，`OpenGL` 就会禁用所有的 *提前深度测试(Early Depth Testing)*，其原因是，`OpenGL` 无法在片段着色器运行之前得知片段将拥有的深度值，因为片段着色器可能会完全修改这个深度值。）


## 接口块
`GLSL`提供了一个叫做 **接口块(Interface Block)** 的数据类型，来方便组合输入/输出变量；根据是一个输入还是输出块(Block)，使用 `in` 或 `out` 关键字来定义的。

- 顶点着色器大致如下：

	``` C
	#version 330 core   /* 指定GLSL版本3.3，匹配 OpenGL 版本 */
	
	layout (location = 0) in vec3 aPos;         /* 顶点位置变量的属性位置值为：0 */
	layout (location = 1) in vec2 aTexCoords;   /* 顶点纹理坐标变量的属性位置值为：1 */
	
	uniform mat4 modelMat;          /* 模型矩阵 */
	uniform mat4 viewMat;           /* 观察矩阵 */
	uniform mat4 projectionMat;     /* 投影矩阵 */
	
	/* out 定义输出接口块，‘VS_OUT’：块名，在下一个
	  着色器(片段着色器)中的输入接口块必须一致；
	  ‘vs_out’：实例名，任意起 */
	out VS_OUT
	{
	    vec2 TexCoords;
	} vs_out;
	
	void main()
	{
	    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
	    vs_out.TexCoords = aTexCoords;  // 接口块赋值
	}
	```
- 片段着色器大致如下：

	``` C
	#version 330 core   /* 指定GLSL版本3.3，匹配 OpenGL 版本 */
	
	out vec4 FragColor; /* 输出，指定片段颜色 */
	
	/* in 定义输入接口块，‘VS_OUT’：接口块类型名，与
	   上一个着色器(顶点着色器)中的输出接口块一致；
	   ‘fs_in’：实例名，随意起 */
	in VS_OUT
	{
	    vec2 TexCoords;
	} fs_in;
	
	uniform sampler2D texture1;  /* 纹理采样 1 */
	
	void main()
	{
	    FragColor = texture(texture1, fs_in.TexCoords);
	}
	```
	
## Uniform缓冲对象
**Uniform缓冲对象(Uniform Buffer Object)：**定义一系列在多个着色器中相同的全局 `Uniform`变量，当使用 `Uniform`缓冲对象的时候，只需要设置相关的 `uniform` 一次。

``` C
#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec3 aPos;         /* 顶点位置变量的属性位置值为：0 */

uniform mat4 modelMat;          /* 模型矩阵 */

/* layout (std140) 表示，当前定义的 Uniform 块对使用的内存布局。 */
layout (std140) uniform Matrices
{
    mat4 viewMat;               /* 观察矩阵 */
    mat4 projectionMat;         /* 投影矩阵 */
};

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
}
```
如上，声明了一个叫做 `Matrices` 的 `Uniform 块`，它储存了两个 `4x4` 矩阵。`Uniform 块`中的变量可以直接访问，不需要加块名作为前缀。


## Uniform 块布局
`Uniform` 块布局有三类：

- share(共享)布局
- packed布局
- std140布局

### std140布局
**std140布局：**显示声明了每个变量类型的内存布局（每个变量的偏移量都是由一系列 [规则](http://www.opengl.org/registry/specs/ARB/uniform_buffer_object.txt) 所决定的）；其中包括：

- **基准对齐量(Base Alignment)**：一个变量在 `Uniform` 块中所占据的字节空间量（包括填充量 `Padding`）。
- **对齐偏移量(Aligned Offset)**：一个变量从 `Uniform` 块起始位置的字节偏移量（注意：对齐偏移量必须等于基准对齐量的倍数）。

`GLSL` 中的每个变量，比如说 `int`、`float` 和 `bool`，都被定义为 `4` 字节量（每 `4` 个字节将会用一个 **N** 来表示）。

#### GLSL 常见数据类型的(std140)布局规则：
| 类型 | 布局规则 |
| -------- | -------- |
| 标量(如 `int` 和 `bool`) | 每个标量的基准对齐量为 `N` |
| 向量 | `2N` 或者 `4N`(这意味着 `vec3`的基准对齐量为 `4N`) |
| 标量或向量的数组 | 每个元素的基准对齐量与 `vec4` 的相同 |
| 矩阵 | 储存为列向量的数组，每个向量的基准对齐量与 `vec4` 的相同 |
| 结构体 | 等于所有元素根据规则计算后的大小，但会填充到 `vec4` 大小的倍数 |

### 绑定点
**绑定点(Binding point)：**用于让 `OpenGL` 知道哪个 `Uniform` 缓冲对应的是哪个 `Uniform` 块（在创建 `Uniform` 缓冲之后将其链接至绑定点；同时将着色器中的 `Uniform` 块绑定到相同的绑定点，这样就可以绑定了相对应的关系）。如下图所示：

![图片来源于：learnopengl.com](AdvancedGLSLBindingPoints.png)

- 使用 `glBindBufferBase(GLenum target, GLuint index, GLuint buffer);`函数将 `Uniform` 缓冲对象绑定到一个特定的绑定点上：

	- **target：**缓冲目标（如，GL_UNIFORM_BUFFER）。
	- **index：**链接到的绑定点（`0, 1, 2 ··· n`）。
	- **buffer：**`Uniform` 缓冲对象(引用 ID)。
- 或使用 `glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);` 函数将 `Uniform` 缓冲的某一部分绑定到一个特定的绑定点上：

	- **target：**缓冲目标（如，GL_UNIFORM_BUFFER）。
	- **index：**链接到的绑定点（`0, 1, 2 ··· n`）。
	- **buffer：**`Uniform` 缓冲对象(引用 ID)。
	- **offset：**`Uniform` 缓冲起始偏移量。
	- **size：**需要绑定的缓冲大小。
- 使用 `glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);` 函数将 `Uniform` 块绑定到一个特定的绑定点上：

	- **program：**着色器程序对象。
	- **uniformBlockIndex：** `Uniform` 块索引(Uniform Block Index)是着色器中已定义 `Uniform` 块的位置值索引（通过 `glGetUniformBlockIndex` 获取）。
	- **uniformBlockBinding：**链接到的绑定点（`0, 1, 2 ··· n`）。

### 例子分析：
- 定义 `Uniform` 块：

	``` C
	layout (std140) uniform ExampleUniformBlock		// 表明使用 std140 布局
	{
	                     // 基准对齐量       // 对齐偏移量
	    float value;     // 4               // 0 
	    vec3 vector;     // 16              // 16  (0 ＋ 4 ＝ 4，但是根据规则‘对齐偏移量必须等于基准对齐量的倍数’，但 4 不是 16 的倍数，所以 4->16)
	    mat4 matrix;     // 16              // 32  (列 0)（16 ＋ 16 ＝ 32 刚好是 16 的倍数）
	                     // 16              // 48  (列 1)
	                     // 16              // 64  (列 2)
	                     // 16              // 80  (列 3)
	    float values[3]; // 16              // 96  (values[0])（80 ＋ 16 ＝ 96 刚好是 16 的倍数）
	                     // 16              // 112 (values[1])
	                     // 16              // 128 (values[2])
	    bool boolean;    // 4               // 144（128 ＋ 16 ＝ 144 刚好是 4 的倍数）
	    int integer;     // 4               // 148（144 ＋ 4 ＝ 148 刚好是 4 的倍数）
	}; 
	```
- 创建 `Uniform` 缓冲对象

	``` C
	GLuint uboExampleBlock;     // 声明 Uniform 缓存对象引用 ID
    glGenBuffers(1, &uboExampleBlock);  // 创建 Uniform 缓冲
    glBindBuffer(GL_UNIFORM_BUFFER, uboExampleBlock);   // 绑定缓冲到 ‘GL_UNIFORM_BUFFER’ 缓冲目标
    glBufferData(GL_UNIFORM_BUFFER, 152, NULL, GL_STATIC_DRAW); // 分配 152(通过如上分析对齐偏移量计算得到) 字节的内存（暂时不填充数据，后续用 ‘glBufferSubData’ 进行更新）
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // 解绑缓冲
	```
- 链接 `Uniform` 块到绑定点：

	``` C
	// 获取 ‘ExampleUniformBlock’ 块索引
    GLuint ubIndex = glGetUniformBlockIndex(programId, "ExampleUniformBlock");
    // 绑定 Uniform 块到绑定点：2
    glUniformBlockBinding(programId, ubIndex, 2);
	```
- 链接 `Uniform` 缓冲到绑定点：

	``` C
	// 链接 Uniform 缓冲到绑定点：2
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, uboExampleBlock);
    /*
     或使用
    glBindBufferRange(GL_UNIFORM_BUFFER, 2, uboExampleBlock, 0, 152);
     */
	```
- 向 `Uniform` 缓冲添加/更新数据：

	``` C
	/* 添加/更新上述定义中的 ‘boolean’ 的数据 */
    glBindBuffer(GL_UNIFORM_BUFFER, uboExampleBlock);   // 绑定 Uniform 缓冲
    GLint b = true; // GLSL 中的 bool 是 4 字节的，所以将它存为一个 integer
    glBufferSubData(GL_UNIFORM_BUFFER, 144, 4, &b);     // 添加/更新 数据
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // 解绑缓冲
	```


---


# 参考
教程来源：[https://learnopengl.com/](https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL)。