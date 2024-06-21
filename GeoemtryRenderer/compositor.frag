#version 430

uniform sampler2D colorTexture;

out vec4 fragColor;

layout(std430, binding = 4)  coherent buffer OverlapSSBO {
    int overlapInfo[];
} overlapSSBO;


uniform vec2 winSize;

void main()
{
    vec2 texCoord = gl_FragCoord.xy / textureSize(colorTexture, 0);
    int idx = int(gl_FragCoord.y) * int(winSize.x) + int(gl_FragCoord.x);
    int overlappingFragCount = atomicExchange(overlapSSBO.overlapInfo[idx], 0);

    vec4 color = texture(colorTexture, texCoord);
    if (overlappingFragCount > 1)
        color *= vec4(vec3(0.8), 1.0);
    fragColor = color;
}

