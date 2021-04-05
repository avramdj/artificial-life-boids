//
// Created by avram on 4.4.21..
//

#ifndef BOIDS_BOID_HPP
#define BOIDS_BOID_HPP

#include <glm/glm.hpp>
#include <vector>
#include <engine/renderable.hpp>

class Boid : public IRenderable{
protected:
    glm::vec3 pos;
    glm::vec3 direction;
    float dt;
public:
    Boid(const glm::vec3 &pos, const glm::vec3 &direction);
    virtual ~Boid();
    void move();
    const glm::vec3 &getPos() const;
    const glm::vec3 &getDirection() const;
    float getDt() const;
    void addDirection(const glm::vec3 &other_direction, float mul);
    void setPos(const glm::vec3 &pos);
    void setDirection(const glm::vec3 &direction);
    void setDt(float dt);
};

#endif //BOIDS_BOID_HPP
