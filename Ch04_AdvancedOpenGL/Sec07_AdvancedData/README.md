# OpenGL学习笔记（二十七）—— Advanced Data

---

## 高级数据
`OpenGL` 中的 **缓冲** 只是一个管理特定内存块的对象，当将其绑定到一个 `Buffer Target` 时，就赋予了其意义（如，当绑定一个缓冲到 `GL_ARRAY_BUFFER` 时，它就是一个顶点数组缓冲。）`OpenGL` 内部会为每个 *缓冲目标* 储存一个缓冲，并且会根据目标的不同，以不同的方式处理缓冲。

- `glBufferData` 函数来填充缓冲对象所管理的内存；该函数会分配一块内存，并将数据添加到这块内存中（如果将 **data** 参数设置为 `NULL`，则该函数将只会分配内存，但不进行数据填充）。
- `glBufferSubData` 填充缓冲的特定区域；该函数不同的地方在于，可以提供一个偏移量，指定从何处开始填充这个缓冲，使其能够插入或者更新缓冲内存的某一部分。(**注意**，缓冲需要有足够的已分配内存，所以对一个缓冲调用 `glBufferSubData` 之前必须要先调用 `glBufferData`。)
- `glMapBuffer` 函数用于请求缓冲内存的指针，直接将数据复制到缓冲当中：

	``` C
	// 数据
    GLfloat data[] =
    {
        0.5f, 1.0f, -0.35f
    };
    // 绑定缓冲到指定的目标
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    // 获取缓冲内存的指针（以只写方式）
    void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    // 复制数据到内存
    memcpy(ptr, data, sizeof(data));
    // 释放指针（当不再需要使用的时候，必需释放）
    GLboolean isSuccess = glUnmapBuffer(GL_ARRAY_BUFFER);
    if (GL_TRUE == isSuccess)
    {
        // 映射（填充）数据成功
    }
    else
    {
        // 映射（填充）数据失败
    }
	```
	
	
## 分批顶点属性
`glVertexAttribPointer` 函数用于指定顶点数组缓冲内容的属性布局：

- **交错(Interleave)布局：**`123123123123`

	``` C
	// 顶点数据
    GLfloat vertices[] =
    {
        // 位置    法线    纹理坐标
           ...    ...       ..
    };
    // 填充缓冲
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    // 设置缓冲内容属性(位置)布局
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    // 设置缓冲内容属性(法线)布局
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    // 设置缓冲内容属性(纹理坐标)布局
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	```
- **分批(Batch)布局：** `111122223333`

	``` C
	// 顶点位置数据
    GLfloat positions[] = { ... };
    // 顶点法线数据
    GLfloat normals[] = { ... };
    // 顶点纹理坐标数据
    GLfloat tex[] = { ... };
    // 填充(位置)缓冲
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), &positions);
    // 填充(法线)缓冲
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(normals), &normals);
    // 填充(纹理坐标)缓冲
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normals), sizeof(tex), &tex);
    // 设置缓冲内容属性(位置)布局
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    // 设置缓冲内容属性(法线)布局
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(sizeof(positions)));
    // 设置缓冲内容属性(纹理坐标)布局
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(sizeof(positions) + sizeof(normals)));
	```
	
## 复制缓冲
`glCopyBufferSubData` 函数可以从一个缓冲中复制数据到另一个缓冲中，原型如下：

``` C
void glCopyBufferSubData(GLenum readtarget, GLenum writetarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size);
```
- **readtarget：**复制 `源` 缓冲目标（如，`GL_COPY_READ_BUFFER`，需提前将缓冲绑定到该缓冲目标上）
- **writetarget：**复制 `目标` 缓冲目标（如，`GL_COPY_WRITE_BUFFER`，需提前将缓冲绑定到该缓冲目标上）
- **readoffset：**读取缓冲起始位置(偏移量)
- **writeoffset：**写入缓冲起始位置(偏移量)
- **size：**读取数据的大小

### 例子
- 如何复制两个顶点数组缓冲：

	``` C
	// 顶点数据
    GLfloat vertexData[] = { ... };
    // 绑定缓冲到指定缓冲目标·复制'读'缓冲
    glBindBuffer(GL_COPY_READ_BUFFER, vbo1);
    // 绑定缓冲到指定缓冲目标·复制'写'缓冲
    glBindBuffer(GL_COPY_WRITE_BUFFER, vbo2);
    // 复制缓冲数据
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, sizeof(vertexData));
	```
- 只将 `writetarget` 缓冲绑定为新的缓冲目标类型之一：

	``` C
	// 顶点数据
    GLfloat vertexData[] = { ... };
    // 绑定缓冲到指定缓冲目标·顶点数组缓冲
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    // 绑定缓冲到指定缓冲目标·复制'写'缓冲
    glBindBuffer(GL_COPY_WRITE_BUFFER, vbo2);
    // 复制缓冲数据
    glCopyBufferSubData(GL_ARRAY_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, sizeof(vertexData));
	```


---


# 参考
教程来源：[https://learnopengl.com/](https://learnopengl.com/Advanced-OpenGL/Advanced-Data)。