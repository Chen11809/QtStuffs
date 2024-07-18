#version 450 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;

layout(location = 0) out vec3 position;
layout(location = 1) out vec2 texCoord;

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 modelView;
    mat4 modelViewProjection;
    vec2 texCoordOffset;
};

void main()
{
    texCoord = vertexTexCoord + texCoordOffset;
    position = vec3(modelView * vec4(vertexPosition, 1.0));

    gl_Position = modelViewProjection * vec4(vertexPosition, 1.0);
}
