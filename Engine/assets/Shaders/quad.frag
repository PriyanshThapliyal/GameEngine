#version 330 core

in vec4 v_Color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    FragColor = v_Color;
}