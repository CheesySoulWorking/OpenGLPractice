#version 330 core

// Normalize for safety
in vec3 vertexWorldNormal;
in vec3 vertexWorldPosition;
// here would be the passed in texture coordinate from the vertex shader

out vec4 FragColor;

uniform vec3 uCameraPosition;
uniform vec3 uLightDirection;
uniform vec3 uLightPosition;
// here would be where the sampler2D texture(actual image)

void main() {
    // Phong Constants ==================================================================
    vec3 worldNormal = normalize(vertexWorldNormal);
    vec3 viewDirection = normalize(vec3(uCameraPosition) - vec3(vertexWorldPosition));
    vec3 specMaterialColor = vec3(0.3);

    // here would be the vec3 albedo set by another texture2D(uniform texture, passed in texCoord).rgb (we specifically want to express the rgb of the texture)
    // then replace the vec3 with the albedo.
    vec3 ambient = vec3(1.0, 1.0, 1.0) * 0.1;



    // Directional Light ================================================================
    vec3 directionalLightDirection = normalize(uLightDirection);
    float directionalLambertTerm = max(dot(worldNormal, directionalLightDirection), 0.0);
    float directionalScalar = dot(directionalLightDirection, worldNormal) * 2.0;
    vec3 directionalReflection = directionalScalar * vec3(worldNormal) - vec3(directionalLightDirection);
    float directionalPhongTerm = pow(max(dot(directionalReflection, viewDirection), 0.0), 64.0);

    // here we would be the vec4 textureColor using textur2D(uniform texture, passed in texCoord);
    // then set the diffuse color to the textureColor we just made multiplied by the lambert term.
    vec3 directionalDiffuseColor = vec3(1.0, 1.0, 1.0) * directionalLambertTerm;
    
    vec3 specularColor = directionalPhongTerm * specMaterialColor * 1.0;
    vec3 directionalFinalColor = directionalDiffuseColor + specularColor;



    // Positional light ================================================================
    vec3 unNormalizedPointLightDir = vec3(uLightPosition) - vec3(vertexWorldPosition);
    float distance = length(unNormalizedPointLightDir);
    float attenuation = 1.0 / (1.0 + (0.14 * distance) + (0.07 * distance * distance));

    vec3 pointLightDirection = normalize(unNormalizedPointLightDir);
    float pointLambertTerm = max(dot(worldNormal, pointLightDirection), 0.0);
    float pointScalar = dot(pointLightDirection, worldNormal) * 2.0;
    vec3 pointReflection = pointScalar * vec3(worldNormal) - vec3(pointLightDirection);
    float pointPhongTerm = pow(max(dot(pointReflection, viewDirection), 0.0), 64.0);

    // here we would be the vec4 textureColor using textur2D(uniform texture, passed in texCoord);
    // then set the diffuse color to the textureColor we just made multiplied by the lambert term.
    vec3 pointDiffuseColor = vec3(1.0, 1.0, 1.0) * pointLambertTerm;

    vec3 pointSpecularColor = pointPhongTerm * specMaterialColor * 1.0;
    vec3 pointFinalColor = (pointDiffuseColor * attenuation) + (pointSpecularColor * attenuation);



    // Final combination of point light and directional light shading ==================
    vec3 finalColor = directionalFinalColor + pointFinalColor + ambient;
    FragColor = vec4(finalColor, 1.0);
}