#version 460 core

out vec4 EFragmentColor;

in vec3 EPosition;
in vec3 ENormal;
in vec2 EUV;

in vec3 EWorldPosition;

uniform sampler2D UDiffuse;

uniform vec3 UCameraPosition;
uniform float UFogStart = -1.0;
uniform float UFogEnd = -1.0;
uniform vec3 UFogColor = vec3(0.0, 0.0, 0.0);

void main()
{
    vec4 TempColor = texture(UDiffuse, EUV);
    
    if(UFogColor != vec3(0.0)) {
        float CameraDistance = length(EWorldPosition - UCameraPosition);
        float FogFactor = clamp((UFogEnd - CameraDistance) / (UFogEnd - UFogStart), 0.0, 1.0);

        TempColor = mix(vec4(UFogColor, 1.0), TempColor, FogFactor);
    }
    EFragmentColor = TempColor;
}
