#version 400 core

layout (location = 0) in vec3 LPosition;
layout (location = 1) in vec3 LNormal;
layout (location = 2) in vec2 LUV;

out vec3 EPosition;
out vec3 ENormal;
out vec2 EUV;
out vec3 EViewPosition;

uniform mat4 UProjection;
uniform mat4 UView;
uniform mat4 UTransform;

uniform sampler2D UNormal;
uniform sampler2D UHeight;

void main()
{
    vec4 WorldPosition = UTransform * vec4(LPosition, 1.0);
    
    EPosition = WorldPosition.xyz;
    ENormal = LNormal;
    EUV = LUV;

    mat4 InverseView = inverse(UView);
    EViewPosition = InverseView[3].xyz;

    gl_Position = UProjection * UView * WorldPosition;
}
