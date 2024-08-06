#version 400 core

out vec4 FragmentColor;

in vec3 Position;
in vec2 UV;

uniform sampler2D Diffuse;
uniform int X;
uniform int Y;

float MapValue(float Value, float InputMin, float InputMax, float OutputMin, float OutputMax) {
    return OutputMin + ((Value - InputMin) * (OutputMax - OutputMin) / (InputMax - InputMin));
}

void main()
{
    // FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    // FragColor = vec4(UV.y, UV.x, 0.0f, 1.0f);
    float Width = 18.0f;
    float Height = 7.0f;
    float XF = X;
    float YF = (Height - 1.0f) - Y;
    float UVWidth = 1.0f / Width;
    float UVHeight = 1.0f / Height;
    vec2 NewUV = vec2(
        MapValue(UV.x, 0.0f, 1.0f, XF * UVWidth, (XF + 1.0f) * UVWidth),
        MapValue(UV.y, 0.0f, 1.0f, YF * UVHeight, (YF + 1.0f) * UVHeight)
    );
    FragmentColor = texture(Diffuse, NewUV);
}
