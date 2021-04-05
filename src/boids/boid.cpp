//
//
// Created by avram on 4.4.21..
#include <boids/boid.hpp>
#include <glm/glm.hpp>

Boid::Boid(const glm::vec3 &pos, const glm::vec3 &direction) : pos(pos), direction(direction) {}

void Boid::move() {
    pos += direction * dt;
}

void Boid::addDirection(const glm::vec3 &other_direction, float mul) {
    direction += other_direction * mul;
    direction = glm::normalize(direction);
}

void Boid::setPos(const glm::vec3 &pos) {
    Boid::pos = pos;
}

void Boid::setDirection(const glm::vec3 &direction) {
    Boid::direction = direction;
}

void Boid::setDt(float dt) {
    Boid::dt = dt;
}

const glm::vec3 &Boid::getPos() const {
    return pos;
}

const glm::vec3 &Boid::getDirection() const {
    return direction;
}

float Boid::getDt() const {
    return dt;
}

Boid::~Boid() = default;
