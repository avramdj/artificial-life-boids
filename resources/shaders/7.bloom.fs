#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

struct Light {
    vec3 Position;
    vec3 Color;
    vec3 Specular;
};
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;

    float shininess;
};
uniform Light lights[4];
uniform vec3 viewPos;
uniform Material material;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

void main()
{

    vec3 color = texture(material.texture_diffuse1, TexCoords).rgb;
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    // ambient
    vec3 ambient = 0.1 * color;
    // lighting
    vec3 lighting = vec3(0.0);

    //light 1 -- white
    {
    vec3 lightDir = normalize(lights[0].Position - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = lights[0].Color * diff * color;
    vec3 specular = lights[0].Specular * spec * vec3(texture(material.texture_specular1, TexCoords).xxx);
    vec3 result = diffuse + specular;
    // attenuation (use quadratic as we have gamma correction)
    float distance = length(FragPos - lights[0].Position);
    result *= (1.0 / (distance*distance/3.0));
    lighting += result;
    }
    //light 2 -- purple
    {
    vec3 lightDir = normalize(lights[1].Position - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = lights[1].Color * diff * color;
    vec3 specular = lights[1].Specular * spec * vec3(texture(material.texture_specular1, TexCoords).xxx);
    vec3 result = diffuse + specular;
    // attenuation (use quadratic as we have gamma correction)
    float distance = length(FragPos - lights[1].Position);
    result *= (1.0 / (distance*distance/3.0));
    lighting += result;
    }
    //light 3 -- orange
    {
    vec3 lightDir = normalize(lights[2].Position - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(-dot(viewDir, reflectDir), 0.0), material.shininess);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = lights[2].Color * diff * color;
    vec3 specular = lights[2].Specular * spec * vec3(texture(material.texture_specular1, TexCoords));
    vec3 result = diffuse + specular;
    // attenuation (use quadratic as we have gamma correction)
    float distance = length(FragPos - lights[2].Position);
    result *= (1.0 / (distance*distance));
    lighting += result;
    }
    //Directional light 4
    {
    vec3 lightDir = normalize(-lights[3].Position);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = lights[3].Color * diff * color;
    vec3 specular = lights[3].Specular * spec * vec3(texture(material.texture_specular1, TexCoords));
    vec3 result = diffuse + specular;
    // attenuation (use quadratic as we have gamma correction)
//     float distance = length(FragPos - lights[3].Position);
    result *= (1.0 / (2));
    lighting += result;
    }

    vec3 result = ambient + lighting;
    // check whether result is higher than some threshold, if so, output as bloom threshold color
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    FragColor = vec4(result, 1.0);
}
