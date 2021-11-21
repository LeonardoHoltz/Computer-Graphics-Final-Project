#version 450 core

layout( location = 0 ) in vec4 vertexLocation;
layout( location = 1 ) in vec4 normalLocation;
layout( location = 2 ) in vec2 textCoordLocation;

layout( location = 3 ) uniform vec4 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 fColor;
out vec4 normal;
out vec4 world_position;
out vec2 model_tex_coord;
out vec2 B;

void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    world_position = model * vertexLocation;
    vec4 BVector = vec4(1.0, 0.0, 0.0, 1.0);
    BVector = inverse(transpose(model)) * BVector;
    B = vec2(BVector.x, BVector.y);
    normal = inverse(transpose(model)) * normalLocation;
    normal.w = 0.0;
    model_tex_coord = textCoordLocation;

    gl_Position = projection * view *  model * vertexLocation;

    fColor = vColor;
}