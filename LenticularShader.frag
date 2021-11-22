#version 450 core

in vec4 fColor;
in vec4 normal;
in vec4 world_position;
in vec2 model_tex_coord;
in vec2 B;

uniform mat4 view;

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

    vec2 A = normalize(vec2(camera_position.x, camera_position.z) - vec2(world_position.x, world_position.z));

    int sectors = 512;

    float dot_product = dot(A, B);
    float projection_value = (((dot_product - (-1.0)) * (1.0 - 0.0)) / (1.0 - (-1.0))) + 0.0;
    
    float interval_value = 1.0 / sectors;
    float interval_init = 0.0;
    float interval_end = interval_value;
    float x_coord = model_tex_coord.x;
    float interval_distance, final_coord;
    while(interval_end <= 1.0) { // discover which section the coordinate is
        if(x_coord <= interval_init && x_coord <= interval_end) {
            interval_distance = x_coord - interval_init;
            final_coord = interval_distance * sectors; // final_coord is the percentage value of the fragment inside the sector
            break;
        }
        else {
            interval_init += interval_value;
            interval_end += interval_value;
        }
    }


    vec4 textColor;

    if( dot_product < 0) {
        if (dot_product < final_coord) {
            textColor = texture(tex1, model_tex_coord).rgba;
        }
        else {
            textColor = texture(tex0, model_tex_coord).rgba;
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