#Shader vertex
#version 120

attribute vec4 position;

void main()
{
    gl_Position = position;
}

#Shader fragment
#version 120

void main()
{
    gl_FragColor = vec4(0.39, 0.58, 0.92, 1.0);
}
