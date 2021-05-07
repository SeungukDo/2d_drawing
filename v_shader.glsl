#version 460

layout (location = 0) in vec3 Position;
uniform mat4 transform;
uniform mat4 model_view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model_view * transform * vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0);
}