//
// Created by avram on 5.4.21..
//

#include <boids/cone.hpp>


void Cone::render() {
    //TODO

}

void Cone::initialize() {
//    model.SetShaderTextureNamePrefix("material.");
}

Cone::Cone(const glm::vec3 &pos, const glm::vec3 &direction) : Boid(pos, direction) {
}

Cone::Cone() : Boid(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)) {
}

void Cone::render(Shader &shader) {
    model.Draw(shader);
}

Model Cone::getModel() {
    return model;
}
