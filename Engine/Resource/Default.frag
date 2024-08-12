#version 400 core

out vec4 FragmentColor;

in vec3 Position;
in vec2 UV;

uniform sampler2D Diffuse;

void main()
{
    // FragmentColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    // FragmentColor = vec4(UV.y, UV.x, 0.0f, 1.0f);
    FragmentColor = texture(Diffuse, UV);
}
