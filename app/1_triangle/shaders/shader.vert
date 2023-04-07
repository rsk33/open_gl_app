#version 330

layout (location = 0) in vec3 pos;
out vec4 vCol;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
    gl_Position = projection * view * model * vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);
};
