//
// Created by avram on 4.4.21..
//

#ifndef BOIDS_BOID_HPP
#define BOIDS_BOID_HPP

#include <glm/glm.hpp>
#include <vector>
#include <engine/renderable.hpp>
#include <engine/model.hpp>

class Boid {
protected:
    glm::vec3 pos;
    glm::vec3 direction;
    float dt = 0.001;
public:
    Boid(const glm::vec3 &pos, const glm::vec3 &direction);
    virtual ~Boid();
    void move(float delta_time);
    const glm::vec3 &getPos() const;
    const glm::vec3 &getDirection() const;
    float getDt() const;
    void addDirection(const glm::vec3 &other_direction, float mul);
    void setPos(const glm::vec3 &pos);
    void setDirection(const glm::vec3 &direction);
    void setDt(float dt);
};

#endif //BOIDS_BOID_HPP
