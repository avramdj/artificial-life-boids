//
// Created by avram on 4.4.21..
//

#ifndef BOIDS_FLOCK_HPP
#define BOIDS_FLOCK_HPP

#include <boids/boid.hpp>
#include <engine/renderable.hpp>
#include <glm/glm.hpp>
#include <cmath>
#include <set>
#include "fish.hpp"

class Flock : public IRenderable{
private:
    std::set<Boid *> boids;
    glm::vec3 center_of_mass;
    glm::vec3 general_direction;
    float sight_distance = 5;
public:
    Flock();
    virtual ~Flock();
    void update();
    void updateParallel();
    void add_boid(Boid* boid);
    void update_centers();
    void separate();
    void align();
    void cohere();
    void move();
    int size();
    void render() override;
    void render(Shader& shader) override;
};


#endif //BOIDS_FLOCK_HPP
