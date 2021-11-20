#version 450 core

in vec4 fColor;
in vec4 normal;
in vec4 world_position;
in vec2 model_tex_coord;

layout( location = 5 ) uniform mat4 view;

uniform sampler2D tex0;
uniform sampler2D tex1;

out vec4 finalColor;

void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;
    vec4 textColor = texture(tex0, model_tex_coord).rgba;
    finalColor = textColor;
    //finalColor = vec4(0.0, 1.0, 0.0, 1.0);
}