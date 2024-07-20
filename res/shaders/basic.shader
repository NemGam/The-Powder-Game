#shader vertex
#version 330 core
		
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
        
out vec3 vertexColor;

void main()
{
	gl_Position = vec4(position, 1.0);
    vertexColor = color;
};

#shader fragment
#version 330 core

out vec4 FragColor;        
in vec3 vertexColor;      

void main()
{
    FragColor = vec4(vertexColor, 1.0);
};