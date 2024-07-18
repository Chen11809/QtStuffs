#version 450 core

layout(location = 0) in vec2 texCoord;

layout(binding = 0) uniform sampler2D diffuseTexture;
layout(binding = 1) uniform sampler2D drawingTexture;

layout(location = 0) out vec4 fragColor;

void main()
{
    vec3 diffuse = texture(diffuseTexture, texCoord).rgb;
    vec4 drawing = texture(drawingTexture, texCoord);
    vec3 combined = mix(diffuse, drawing.rgb, drawing.a);
    fragColor = vec4(combined, 1.0);
}
