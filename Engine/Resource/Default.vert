#version 400 core

layout (location = 0) in vec3 LPosition;
layout (location = 1) in vec2 LUV;

out vec3 Position;
out vec2 UV;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Transform;

uniform sampler2D Normal;
uniform sampler2D Height;

void main()
{
    vec4 WorldPosition = Transform * vec4(LPosition, 1.0);
    
    Position = WorldPosition.xyz;
    UV = LUV;

    gl_Position = Projection * View * WorldPosition;
}