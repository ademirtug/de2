
#version 330 core
out vec4 frag_color;

in vec2 tex_coord;

uniform sampler2D mesh_texture;

void main()
{
    frag_color = texture(mesh_texture, tex_coord);
}