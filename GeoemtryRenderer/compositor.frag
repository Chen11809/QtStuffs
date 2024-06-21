#version 430

out vec4 fragColor;

layout(std430, binding = 4)  coherent buffer OverlapSSBO {
    int overlapInfo[];
} overlapSSBO;


uniform vec2 winSize;

void main()
{
    int idx = int(floor(gl_FragCoord.y)) * int(winSize.x) + int(floor(gl_FragCoord.x));
    int overlappingFragCount = atomicExchange(overlapSSBO.overlapInfo[idx], 0);

    fragColor = vec4(0.0, 0.5, 0.5, 0.5);

    // Don't output anything if there's nothing to show
    if (overlappingFragCount <= 1)
        discard;
}

