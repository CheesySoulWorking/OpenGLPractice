#version 330 core

// Normalize for safety
in vec3 vertexWorldNormal;
in vec3 vertexWorldPosition;
// here would be the passed in texture coordinate from the vertex shader

out vec4 FragColor;

uniform vec3 uCameraPosition;
uniform vec3 uLightDirection;
// here would be where the sampler2D texture(actual image)

void main() {

    vec3 lightDirection = normalize(uLightDirection);

    vec3 worldNormal = normalize(vertexWorldNormal);

    float lambertTerm = max(dot(worldNormal, lightDirection), 0.0);

    vec3 viewDirection = normalize(vec3(uCameraPosition) - vec3(vertexWorldPosition));

    float scalar = dot(lightDirection, worldNormal) * 2.0;
    vec3 reflection = scalar * vec3(worldNormal) - vec3(lightDirection);

    float phongTerm = pow(max(dot(reflection, viewDirection), 0.0), 64.0);

    // here we would be the vec4 textureColor using textur2D(uniform texture, passed in texCoord);
    // then set the diffuse color to the textureColor we just made multiplied by the lambert term.
    vec3 diffuseColor = vec3(1.0, 1.0, 1.0) * lambertTerm;

    vec3 specMaterialColor = vec3(0.3);

    // here would be the vec3 albedo set by another texture2D(uniform texture, passed in texCoord).rgb (we specifically want to express the rgb of the texture)
    // then replace the vec3 with the albedo.
    vec3 ambient = vec3(1.0, 1.0, 1.0) * 0.1;
    vec3 specularColor = phongTerm * specMaterialColor * 1.0;

    vec3 finalColor = ambient + diffuseColor + specularColor;

    FragColor = vec4(finalColor, 1.0);

}