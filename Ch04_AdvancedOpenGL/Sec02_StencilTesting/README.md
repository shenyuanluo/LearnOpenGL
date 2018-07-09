# OpenGL学习笔记（二十二）—— Stencil Testing

---

## 模板测试
当片段着色器处理完一个片段之后，**模板测试(Stencil Test)** 会开始执行（可能会丢弃片段）；被保留的片段会进入 **深度测试**（可能会丢弃更多的片段）。

一个模板缓冲中，（通常）每个模板值(Stencil Value)是 `8` 位的；所以每个像素/片段一共能有 `256` 种不同的模板值。

**模板缓冲使用步骤：**

- 启用模板缓冲的写入（`glEnable(GL_STENCIL_TEST`);）。
- 渲染物体，更新模板缓冲的内容（`glStencilFunc` 、`glStencilOp`）。
- 禁用模板缓冲的写入（`glStencilMask(GL_FALSE)` 、 `glStencilMask(0x00); `）。
- 渲染（其它）物体，这次根据模板缓冲的内容丢弃特定的片段。


## 模板函数
有两个函数能够用来配置模板测试：`glStencilFunc` 和 `glStencilOp`：

1. **`glStencilFunc(GLenum func, GLint ref, GLuint mask);`**：(描述了 `OpenGL` 应该对模板缓冲内容做什么）

	- **func：**设置模板测试函数(Stencil Test Function)；这个测试函数将会应用到已储存的模板值上和 glStencilFunc 函数的 `ref` 值上。可用的选项有：

		| 函数 | 描述 |
		| -------- | -------- |
		| `GL_ALWAYS` | 永远通过深度测试 |
		| `GL_NEVER` | 永远不通过深度测试 |
		| `GL_LESS` | 在片段模板值小于（ `＜` ）缓冲的模板值时通过测试 |
		| `GL_EQUAL` | 在片段模板值等于（ `＝` ）缓冲的模板值时通过测试 |
		| `GL_LEQUAL` | 在片段模板值小于等于（ `≤` ）缓冲的模板值时通过测试 |
		| `GL_GREATER` | 在片段模板值大于（ `＞` ）缓冲的模板值时通过测试 |
		| `GL_GEQUAL` | 在片段模板值大于等于（ `≥` ）缓冲的模板值时通过测试 |
		| `GL_NOTEQUAL` | 在片段模板值不等于（ `≠` ）缓冲的模板值时通过测试 |
	- **ref：**设置了模板测试的参考值(Reference Value)；模板缓冲的内容将会与这个值进行比较。
	- **mask：**设置一个掩码；它将会与参考值和储存的模板值在测试比较它们之前进行与(AND)运算（初始情况下所有位都为 `1`）。
2. **glStencilOp(GLenum sfail, GLenum dpfail, GLenum dppass);**：（描述了 `OpenGL` 应该如何更新缓冲，默认情况下是设置为 `(GL_KEEP, GL_KEEP, GL_KEEP)` ）

	- **sfail：**模板测试失败时采取的行为。
	- **dpfail：**模板测试通过，但深度测试失败时采取的行为。
	- **dppass：**模板测试和深度测试都通过时采取的行为。

		> 每个选项都可以选用以下的其中一种行为：

		| 行为 | 描述 |
		| -------- | -------- |
		| `GL_KEEP` | 保持当前储存的模板值 |
		| `GL_ZERO` | 将模板值设置为 `0` |
		| `GL_REPLACE` | 将模板值设置为 **glStencilFunc** 函数设置的 `ref` 值 |
		| `GL_INCR` | 如果模板值小于最大值则将模板值加 `1` |
		| `GL_INCR_WRAP` | 与 **GL_INCR** 一样，但如果模板值超过了最大值则归零 |
		| `GL_DECR` | 如果模板值大于最小值则将模板值减 `1` |
		| `GL_DECR_WRAP` | 与 **GL_DECR** 一样，但如果模板值小于 `0` 则将其设置为最大值 |
		| `GL_INVERT` | 按位翻转当前的模板缓冲值 |


## 物体轮廓
**物体轮廓：**将会为每个（或者一个）物体在它的周围创建一个很小的有色边框。

为物体创建轮廓的步骤如下：

1. 在绘制（需要添加轮廓的）物体之前，将模板函数设置为 `GL_ALWAYS`，每当物体的片段被渲染时，将模板缓冲更新为 `1`。
2. 渲染物体。
3. 禁用模板写入以及深度测试。
4. 将每个物体缩放一点点。
5. 使用一个不同的片段着色器，输出一个单独的（边框）颜色。
6. 再次绘制物体，但只在它们片段的模板值不等于 `1` 时才绘制。
7. 再次启用模板写入和深度测试。

# 效果
![StencilTesting](StencilTesting.png)

---


# 参考
教程来源：[https://learnopengl.com/](https://learnopengl.com/Advanced-OpenGL/Stencil-testing)。