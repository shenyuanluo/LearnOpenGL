#  Depth Testing

---

1. 场景效果：

	![场景效果](DepthTesting1.png)
2. 将深度函数改为 `GL_ALWAYS`：

	![修改深度测试函数](DepthTesting2.png)
3. 将（线性）深度值输出为颜色：

	![线性·深度值](DepthTesting3.png)
4. 将（非线性）深度值输出为颜色：

	![非线性·深度值](DepthTesting4.png)
5. 深度冲突（箱子底面与地平面）：

	![深度冲突](DepthTesting5.png)
6. 防止深度冲突（箱子底面与地平面）：

	![防止深度冲突](DepthTesting6.png)

---


# 参考
教程来源：[https://learnopengl.com/](https://learnopengl.com/Advanced-OpenGL/Depth-testing)。