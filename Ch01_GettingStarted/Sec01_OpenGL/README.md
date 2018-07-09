# OpenGL学习笔记（一）—— 简述

- [**OpenGL**](https://www.opengl.org/):（英语：Open Graphics Library）是用于渲染`2D`、`3D` 矢量图形的跨语言、跨平台（由 [Khronos组织](https://www.khronos.org/) 制定并维护）的**规范(Specification)**。

![图片来源于 www.opengl.org/](OpenGL.jpg)

`OpenGL` 规范严格规定了每个函数该如何执行以及输出值；至于具体每个函数内部是如何实现的，将由编写 `OpenGL` 库的人（通常是显卡的生产商）自行决定。


## 立即渲染模式(Immediate mode)
早期的 `OpenGL` （`3.2` 版本以前）使用立即渲染模式（即固定渲染管线），但其大多数功能都被库隐藏起来，很少能控制 `OpenGL` 如何进行计算的自由。


## 核心模式(Core-profile)
当使用 `OpenGL` （`3.3` 版本开始）的核心模式时，`OpenGL` 迫使开发者使用现代的函数；当开发者试图使用一个已废弃的函数时，`OpenGL` 会抛出一个错误并终止绘图。


## 状态机(State Machine)
`OpenGL` 自身是一个巨大的状态机：一系列的变量描述 `OpenGL` 此刻应当如何运行；`OpenGL` 的状态通常被称为 `OpenGL` **上下文(Context)**。

当应用 `OpenGL` 的时候，使用一些 **状态设置函数(State-changing Function)** 来改变上下文；使用一些 **状态使用函数(State-using Function)** 来让 `OpenGL` 根据当前状态执行一些操作。



---

# 参考资料
- [https://learnopengl.com/](https://learnopengl.com/Getting-started/OpenGL)
