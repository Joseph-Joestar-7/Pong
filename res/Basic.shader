#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;

// Uniforms for transformation matrices
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    // Apply the transformations: Projection * View * Model * Position
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

uniform vec4 uColor;

void main()
{
    // Set the fragment color
    FragColor = uColor;
}
