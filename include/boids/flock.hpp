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

class Flock{
private:
    std::set<Boid *> boids;
    glm::vec3 center_of_mass;
    glm::vec3 general_direction;
    float collision_distance = 5.0f;
    float speed = 1;
public:
    Flock();
    virtual ~Flock();
    const set<Boid *> &getBoids() const;
    void update(float delta_time);
    void updateParallel();
    void add_boid(Boid* boid);
    void update_centers();
    void separate(float delta_time);
    void align(float delta_time);
    void cohere(float delta_time);
    void move(float delta_time);
    int size();
};


#endif //BOIDS_FLOCK_HPP
