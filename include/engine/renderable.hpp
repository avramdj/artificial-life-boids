//
// Created by avram on 5.4.21..
//

#ifndef BOIDS_RENDERABLE_HPP
#define BOIDS_RENDERABLE_HPP

#include <engine/model.hpp>

class IRenderable {
public:
    virtual void render() = 0;
    virtual void render(Shader& shader) = 0;
    virtual Model getModel() = 0;
};

#endif //BOIDS_RENDERABLE_HPP
