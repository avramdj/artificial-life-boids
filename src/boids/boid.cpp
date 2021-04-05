//
//
// Created by avram on 4.4.21..
#include <boids/boid.hpp>
#include <glm/glm.hpp>

Boid::Boid(const glm::vec3 &pos, const glm::vec3 &direction) : pos(pos), direction(direction) {}

void Boid::move(float delta_time) {
    pos += direction * delta_time;
}

void Boid::addDirection(const glm::vec3 &other_direction, float mul) {
    setDirection(direction + other_direction * mul);
}

void Boid::setPos(const glm::vec3 &pos) {
    Boid::pos = pos;
}

void Boid::setDirection(const glm::vec3 &new_direction) {
    Boid::direction = new_direction;
    if(glm::length(direction) > 5) {
        direction = glm::normalize(direction) * 5.0f;
    } else if (glm::length(direction) < 0.5) {
        direction = glm::normalize(direction) * 0.5f;
    }
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
