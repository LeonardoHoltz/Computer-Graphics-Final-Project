#version 450 core

layout( location = 0 ) in vec4 vPosition;

uniform mat4 model_view_proj;

void main()
{
    gl_Position = model_view_proj * vPosition;
}