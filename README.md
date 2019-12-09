# 简易Wavefront Obj 文件加载工具

## 简介：
一个基础模型(导出只有顶点，uv，法线数据)的 Wavefront Obj 文件数据的读取器，并附带一个使用例子

## 编译环境：
vs2019 + glm 库

## 使用方式：

```c++
std::vector<glm::vec3>& vertices;

std::vector<glm::vec2>& uvs;

std::vector<glm::vec3>& normals;

LoadFromFile("obj path", vertices, uvs, normals);
```

## 参考来源

[OpenGL-Tutorial 第七课 模型加载](http://www.opengl-tutorial.org/cn/beginners-tutorials/tutorial-7-model-loading/)

[Learn OpenGL CN](https://learnopengl-cn.github.io/)