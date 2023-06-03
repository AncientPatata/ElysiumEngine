#version 330 core

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture1;
uniform vec3 objectColor;
uniform vec3 lightPosition;
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;

void main()
{
    // Debugging outputs
    vec3 debugColor = vec3(0.0, 1.0, 0.0); // Debug color to visualize normals
    FragColor = vec4(Normal * 0.5 + 0.5, 1.0); // Visualize normals (debugging)

    // Uncomment the following line to see the texture instead of debugging outputs
    // FragColor = texture(texture1, TexCoord);

    // Uncomment the following lines to use lighting
    
    vec3 ambient = objectColor * lightAmbient;
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diffuseStrength = max(dot(normalize(Normal), lightDir), 0.0);
    vec3 diffuse = objectColor * lightDiffuse * diffuseStrength;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, normalize(Normal));
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = lightSpecular * specularStrength;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
    
}
