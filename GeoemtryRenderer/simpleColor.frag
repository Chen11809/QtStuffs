#version 430

in vec3 color;

out vec4 fragColor;

layout(std430, binding = 4) coherent buffer OverlapSSBO {
    int overlapInfo[];
} overlapSSBO;

uniform vec2 winSize;

void main()
{
    int idx = int(ceil(gl_FragCoord.y)) * int(winSize.x) + int(ceil(gl_FragCoord.x));
    atomicAdd(overlapSSBO.overlapInfo[idx], 1);

    fragColor = vec4(color, 0.5);
}

