#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性值为0
layout (location = 1) in vec3 aColor; // 颜色变量的属性位置值为1

out vec3 ourColor; // 向片段着色器输出一个颜色
out vec3 ourVertex; // 向片段着色器输出顶点向量

uniform float xOffset;
uniform float yOffset;

void main()
{
  gl_Position = vec4(aPos.x + xOffset, aPos.y + yOffset, aPos.z, 1.0);
  ourColor = aColor;
  ourVertex = aPos;
}