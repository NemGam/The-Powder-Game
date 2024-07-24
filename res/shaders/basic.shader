#shader vertex
#version 330 core
		
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texPos;
        
out vec2 texCoords;

void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
    texCoords = texPos;
};


#shader fragment
#version 330 core

out vec4 FragColor; 

in vec2 texCoords;

uniform sampler2D aTexture;

void main()
{
    FragColor = texture(aTexture, texCoords);
};