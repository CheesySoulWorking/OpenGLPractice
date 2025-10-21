#version 330 core

// Normalize for safety
in vec3 vertexColor;
out vec4 FragColor;
uniform float uTime;
           
void main() {
    FragColor = vec4(
        abs(tan(uTime)) * vertexColor.x,
        abs(tan(uTime)) * vertexColor.y,
        abs(tan(uTime)) * vertexColor.z,
        1.0
    );
}