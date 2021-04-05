//
// Created by avram on 5.4.21..
//

#ifndef BOIDS_FISH_HPP
#define BOIDS_FISH_HPP

#include <boids/boid.hpp>
#include <engine/renderable.hpp>
#include <engine/model.hpp>
#include <engine/camera.hpp>
#include <engine/mesh.hpp>

class Fish : public Boid {
private:
//    Model model = Model("resources/objects/fish/fish.obj");
public:
    static void initialize();
    Fish(const glm::vec3 &pos, const glm::vec3 &direction);
    Fish();
//    void render() override;
//    void render(Shader &shader) override;
//    Model getModel() override;
};

#endif //BOIDS_FISH_HPP
