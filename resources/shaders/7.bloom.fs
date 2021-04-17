#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

struct Light {
    vec3 Position;
    vec3 Color;
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
    // ambient
    vec3 ambient = 0.0 * color;
    // lighting
    vec3 lighting = vec3(0.0);
//     vec3 viewDir = normalize(viewPos - FragPos);
    for(int i = 0; i < 1; i++)
    {
        // diffuse
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        float diff = max(dot(lightDir, normal), 1.0);
        vec3 result = lights[i].Color * diff * color;
        // attenuation (use quadratic as we have gamma correction)
        float distance = length(FragPos - lights[i].Position);
        result *= (1.0 / (distance));
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
