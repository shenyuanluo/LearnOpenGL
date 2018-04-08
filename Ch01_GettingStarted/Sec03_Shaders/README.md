# OpenGL学习笔记（三）—— 着色器
> [上一篇](https://github.com/shenyuanluo/LearnOpenGL/tree/master/Ch01_GettingStarted/Sec02_HelloTriangle) 已经通过使用 `Shader` 来渲染三角形，并且已经了解到了两个重要的 `Shader` ： **顶点着色器** 、 **片段着色器**。


---


## 环境说明
- Mac OS X : 10.12.6
- GLFW : 3.2.1
- GLAD : 3.3
- Xcode : 8.4


## GLSL
着色器是运行在 `GPU` 的小程序，用于渲染管线的特定阶段工作。着色器是使用 **GLSL** 语言编写的，其格式大致如下：

``` C
#version 版本号

in 数据类型 变量名;
in 数据类型 变量名;

out 数据类型 变量名;

uniform 数据类型 变量名;

void main() 
{
	// 处理过程
	 输出变量 = 处理结果；
}
```
其中：`#version` 用于指定使用的 `OpenGL` 对应的版本号；`in` 类型是用于输入的数据（也就是上一阶段的输出数据）；`out` 类型是用于输出的数据（也就是下一阶段的输入数据）；`uniform` 是全局数据类型，其作用是用于在 `CPU` 配置 `GPU` 的数据。


## 数据类型
**GLSL** 中包含默认基础数据类型：`int`、`float`、`double`、`uint` 和 `bool`；以及两种容器类型： `向量(Vector)` 和 `矩阵(Matrix)`。

### 向量
`GLSL` 中的向量是一个可以包含有 `1`、`2`、`3` 或者 `4` 个分量的容器；分量的类型是默认基础类型的任意一个；如下（ `n` 代表分量的数量）：

| 类型 | 含义 |
| :--------: | :-------- |
| `vecn` | 包含 `n` 个 **float** 分量的默认向量 |
| `bvecn` | 包含 `n` 个 **bool** 分量的向量 |
| `ivecn` | 包含 `n` 个 **int** 分量的向量 |
| `uvecn` | 包含 `n` 个 **unsigned int** 分量的向量 |
| `dvecn` | 包含 `n` 个 **double** 分量的向量 |


### Uniform
**Uniform** 是一种从 `CPU` 中的应用向 `GPU` 中的着色器发送数据的方式，且是全局唯一的。
使用方式：

1. 获取 `Uniform` 变量在着色器程序中的位置（顶点着色器和片段着色器链接的着色器程序）。
2. 通过 `glUniform*` 函数对其进行赋值。

---


# 参考资料
1. [learnopengl.com](https://learnopengl.com/Getting-started/Shaders)