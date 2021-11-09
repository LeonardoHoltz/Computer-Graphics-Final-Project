#version 450 core

in vec2 model_tex_coord;
in vec4 world_position;

layout( location = 5 ) uniform mat4 view;

layout( location = 14 ) uniform sampler2D model_tex;

out vec4 finalColor;

void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;
    vec4 textColor = texture(model_tex, model_tex_coord).rgba;
    finalColor = textColor;
}