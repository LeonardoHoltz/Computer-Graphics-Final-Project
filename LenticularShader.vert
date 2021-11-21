#version 450 core

layout( location = 0 ) in vec4 vPosition;
layout( location = 1 ) in vec2 texCoord;
layout( location = 2 ) in vec4 vNormal;

layout( location = 3 ) uniform vec4 vColor;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;




out vec4 fColor;
out vec4 normal;
out vec4 world_position;
out vec2 model_tex_coord;

void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    //vec4 camera_position = inverse(view) * origin;
    world_position = model * vPosition; // usually is model * vPosition, but since the model matrix is always the identity, let's make things simple.
    normal = inverse(transpose(model)) * vNormal;
    normal.w = 0.0;
    model_tex_coord = texCoord;

    gl_Position = projection * view *  model * vPosition;
    //gl_Position = vPosition;

    fColor = vColor;
}