//
// Created by avram on 5.4.21..
//

#ifndef BOIDS_FISH_HPP
#define BOIDS_FISH_HPP

#include <boids/boid.hpp>
#include <engine/renderable.hpp>
#include <learnopengl/model.h>
#include <learnopengl/shader.h>

class Fish : public Boid {
private:
    static Model model;
public:
    static void initialize();
    Fish(const glm::vec3 &pos, const glm::vec3 &direction);
    Fish();
    void render() override;
    void render(Shader &shader) override;
};

#endif //BOIDS_FISH_HPP
