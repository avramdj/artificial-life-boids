//
// Created by avram on 5.4.21..
//

#ifndef BOIDS_RENDERABLE_HPP
#define BOIDS_RENDERABLE_HPP

#include <learnopengl/mesh.h>

class IRenderable {
public:
    virtual void render() = 0;
    virtual void render(Shader& shader) = 0;
};

#endif //BOIDS_RENDERABLE_HPP
