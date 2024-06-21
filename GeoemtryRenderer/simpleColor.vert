#version 430

in vec3 vertexPosition;

out vec3 color;

uniform mat4 modelViewProjection;

void main()
{
    color = vertexPosition;
    gl_Position = modelViewProjection * vec4( vertexPosition, 1.0 );
}
