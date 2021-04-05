//
// Created by avram on 5.4.21..
//

#include <boids/fish.hpp>


//void Fish::render() {
//    //TODO
//
//}

void Fish::initialize() {
//    model.SetShaderTextureNamePrefix("material.");
}

Fish::Fish(const glm::vec3 &pos, const glm::vec3 &direction) : Boid(pos, direction) {
//    model.SetShaderTextureNamePrefix("material.");
}

Fish::Fish() : Boid(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)) {
//    model.SetShaderTextureNamePrefix("material.");
}

//void Fish::render(Shader &shader) {
//    model.Draw(shader);
//}
//
//Model Fish::getModel() {
//    return model;
//}
