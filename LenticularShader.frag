#version 450 core

in vec4 fColor;
in vec4 normal;
in vec4 world_position;
in vec2 model_tex_coord;
in vec2 B;

uniform mat4 view;

uniform int sectors;

uniform sampler2D tex0;
uniform sampler2D tex1;

out vec4 finalColor;

void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    /* discover in what position the camera are related to the interval of the image width.
       Which means to discover the projection (xxxxxxx) of the angle incident from the position p
       To the camera position (cam). */

    /* ________________________________________________________
                                    p---------------->
                             xxxxxx/ theta   B
                                  / 
                                 /  
                                / A  
                               /    
                              /     
                             V      
                           cam      
    */

    /* The projection of the vector A on the vector B is proj_A(B) = ||A|| * cos(theta)
       but we can desconsiderate the lenght of the A vector.
       The vector A is easy obtain, we can calculate using the camera position.
       The vector B is the orthogonal vector to the vertices normals and the vector
       vec3(0.0, 1.0, 0.0), we can calculate it through a cross product */

    vec2 A = vec2(camera_position.x, camera_position.z) - vec2(world_position.x, world_position.z);

    float dot_product = dot(A, B);
    float sector = ceil(model_tex_coord.x * sectors);
    float final_coord = model_tex_coord.x * sectors - sector;

    vec4 textColor;

    if( dot_product < 0) {
        if (dot_product < final_coord) {
            textColor = texture(tex1, model_tex_coord).rgba;//texture(tex1, model_tex_coord).rgba;
        }
        else {
            textColor = texture(tex0, model_tex_coord).rgba; //texture(tex0, model_tex_coord).rgba;
        }
    }
    else {
        if (-dot_product > final_coord) {
            textColor = texture(tex0, model_tex_coord).rgba;
        }
        else {
            textColor = texture(tex1, model_tex_coord).rgba;
        }
    }
  
    finalColor = textColor;
}