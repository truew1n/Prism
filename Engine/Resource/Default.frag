#version 400 core

out vec4 FragmentColor;

in vec3 Position;
in vec2 UV;

uniform sampler2D Diffuse;
uniform sampler2D Normal;


void main()
{
    vec3 LightPos = vec3(0.0f, 20.0f, 0.0f);
    vec3 LightColor = vec3(1.0f, 0.0f, 0.0f);

    vec3 norm = normalize(texture(Normal, UV).rgb * 2.0 - 1.0);
    vec3 lightDir = normalize(LightPos - Position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * LightColor;
    vec3 baseColor = texture(Diffuse, UV).rgb;
    FragmentColor = vec4(baseColor * diffuse, 1.0);
}
