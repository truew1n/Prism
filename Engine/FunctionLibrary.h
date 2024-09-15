#ifndef PE_FUNCTION_LIBRARY_H
#define PE_FUNCTION_LIBRARY_H

#include <type_traits>
#include <glm/gtc/noise.hpp>

template <typename T, typename U>
bool IsA(const U &Object)
{
    return std::is_same<T, U>::value;
}

template <typename T, typename U>
T Cast(U Object)
{
    return dynamic_cast<T>(Object);
}

template <typename T, typename U>
T ForceCast(U Object)
{
    return (T)Object;
}

inline float Perlin(float X, float Y, float Zoom = 1.0f, int Octaves = 1, float Persistence = 0.5f, float Lacunarity = 2.0f, float Scale = 1.0f)
{
    float Total = 0.0f;
    float Frequency = 1.0f;
    float Amplitude = 1.0f;
    float MaxValue = 0.0f;

    X *= Zoom;
    Y *= Zoom;

    for (int I = 0; I < Octaves; ++I) {
        float NoiseValue = glm::perlin(glm::vec2(X * Frequency, Y * Frequency) * Scale);

        Total += NoiseValue * Amplitude;

        MaxValue += Amplitude;
        Amplitude *= Persistence;
        Frequency *= Lacunarity;
    }

    return Total / MaxValue;
}

inline float Perlin(glm::vec2 Location, float Zoom = 1.0f, int Octaves = 1, float Persistence = 0.5f, float Lacunarity = 2.0f, float Scale = 1.0f)
{
    return Perlin(Location.x, Location.y, Zoom, Octaves, Persistence, Lacunarity, Scale);
}

inline float Perlin(float X, float Y, float Z, float Zoom = 1.0f, int Octaves = 1, float Persistence = 0.5f, float Lacunarity = 2.0f, float Scale = 1.0f)
{
    float Total = 0.0f;
    float Frequency = 1.0f;
    float Amplitude = 1.0f;
    float MaxValue = 0.0f;

    X *= Zoom;
    Y *= Zoom;
    Z *= Zoom;

    for (int I = 0; I < Octaves; ++I) {
        float NoiseValue = glm::perlin(glm::vec3(X * Frequency, Y * Frequency, Z * Frequency) * Scale);

        Total += NoiseValue * Amplitude;

        MaxValue += Amplitude;
        Amplitude *= Persistence;
        Frequency *= Lacunarity;
    }

    return Total / MaxValue;
}

inline float Perlin(glm::vec3 Location, float Zoom = 1.0f, int Octaves = 1, float Persistence = 0.5f, float Lacunarity = 2.0f, float Scale = 1.0f)
{
    return Perlin(Location.x, Location.y, Location.z, Zoom, Octaves, Persistence, Lacunarity, Scale);
}

#endif