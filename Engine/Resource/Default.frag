#version 400 core

out vec4 EFragmentColor;

in vec3 EPosition;
in vec3 ENormal;
in vec2 EUV;
in vec3 EViewPosition;

uniform sampler2D UDiffuse;
uniform sampler2D UNormal;

void main()
{
    vec3 LightPosition = vec3(0.0f, 20.0f, 0.0f);
    vec3 LightColor = vec3(0.7f, 0.7f, 1.0f);

    float SpecularStrength = 0.5f;
    float Shininess = 32.0f;
    vec3 AmbientColor = vec3(0.05f, 0.05f, 0.05f);

    vec3 Normal = normalize(texture(UNormal, EUV).rgb * 2.0 - 1.0);

    vec3 LightDirection = normalize(LightPosition - EPosition);

    vec3 ViewDirection = normalize(EViewPosition - EPosition);

    vec3 HalfwayDir = normalize(LightDirection + ViewDirection);

    float Diff = max(dot(Normal, LightDirection), 0.0);
    vec3 Diffuse = Diff * LightColor;

    float Spec = pow(max(dot(Normal, HalfwayDir), 0.0), Shininess);
    vec3 Specular = SpecularStrength * Spec * LightColor;

    vec3 BaseColor = texture(UDiffuse, EUV).rgb;

    vec3 Result = AmbientColor + Diffuse + Specular;
    EFragmentColor = vec4(BaseColor * Result, 1.0);
}
