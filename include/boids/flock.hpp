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
    float base_collision_distance = 2.0f;
    float collision_distance = 2.0f;
    float speed = 1;
    float sep_const = 50;
    float align_const = 10;
    float cohere_const = 50;
    float pad = 50;
    float turn = 0.5;
    float diameter = 0;
public:
    bool b_cohere = true;
    bool b_separate = true;
    bool b_align = true;
    Flock();
    virtual ~Flock();
    void setCubeDimension(float pad);
    const set<Boid *> &getBoids() const;
    const glm::vec3 &getCenterOfMass() const;
    void update(float delta_time);
    void updateParallel();
    void add_boid(Boid* boid);
    void update_centers();
    void separate(float delta_time);
    void align(float delta_time);
    void cohere(float delta_time);
    void move(float delta_time);
    int size();
    void mulScale(float mul);
    void avoid_edges(float delta_time);
    float getCollisionDistence() const;
    float getDiameter() const;
    const glm::vec3 &getGeneralDirection() const;
};


#endif //BOIDS_FLOCK_HPP
