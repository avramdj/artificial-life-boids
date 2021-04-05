//
// Created by avram on 5.4.21..
//

#include <boids/fish.hpp>


void Fish::render() {
    //TODO

}

void Fish::initialize() {
    Fish::model = Model("resources/objects/fish/fish.obj");
    Fish::model.SetShaderTextureNamePrefix("material.");
}

Fish::Fish(const glm::vec3 &pos, const glm::vec3 &direction) : Boid(pos, direction) {}

Fish::Fish() : Boid(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)) {}

void Fish::render(Shader &shader) {

    model.Draw(shader);
}