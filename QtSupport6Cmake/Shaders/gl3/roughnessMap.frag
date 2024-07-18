#version 150 core

in vec2 texCoord;

uniform sampler2D diffuseTexture;
uniform sampler2D drawingTexture;

out vec4 fragColor;

void main()
{
    vec3 diffuse = texture(diffuseTexture, texCoord).rgb;
    vec4 drawing = texture(drawingTexture, texCoord);
    vec3 combined = mix(diffuse, drawing.rgb, drawing.a);
    fragColor = vec4(combined, 1.0);
}

