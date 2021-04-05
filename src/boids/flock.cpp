//
//
// Created by avram on 4.4.21..
#include <boids/flock.hpp>

Flock::Flock() {
    center_of_mass = glm::vec3(0, 0, 0);
    general_direction = glm::vec3(0, 0, 0);
}

Flock::~Flock() {
    for (Boid *boid : boids) {
        delete boid;
    }
}

void Flock::add_boid(Boid *boid) {
    boids.insert(boid);
}

/*
 * Updates the center of mass and general direction of the flock.
 */
void Flock::update_centers() {
    //update center of mass
    center_of_mass = glm::vec3(0, 0, 0);
    for(Boid* boid : boids) {
        center_of_mass += boid->getPos();
    }
    center_of_mass /= size();
    //update general direction
    general_direction = glm::vec3(0, 0, 0);
    for(Boid* boid : boids) {
        general_direction += boid->getDirection();
    }
    general_direction = glm::normalize(general_direction);
}

/*
 * Update direction of all boids to account for collision avoidance.
 */
void Flock::separate() {
    //TODO
}

/*
 * Update direction of all boids to account for the general direction of the flock
 */
void Flock::align() {
    for(Boid* boid : boids) {
        boid->addDirection(general_direction, 0.1f);
    }
}

/*
 * Update diraction of all boids to account for center of mass.
 */
void Flock::cohere() {
    for(Boid* boid : boids) {
        boid->addDirection(center_of_mass - boid->getPos(), 0.1);
    }
}

int Flock::size() {
    return boids.size();
}

void Flock::update() {
    update_centers();
    separate();
    align();
    cohere();
    move();
}

void Flock::move() {
    for(Boid* boid : boids) {
        boid->move();
    }
}

/*
 * Updates all boid parameters in a single loop. Same as update().
 */
void Flock::updateParallel() {
    update_centers();
    for(Boid* boid : boids) {
        //TODO separate
        //align
        boid->addDirection(general_direction, 0.1f);
        //cohere
        boid->addDirection(center_of_mass - boid->getPos(), 0.1);
        //move
        boid->move();
    }
}

void Flock::render() {
    for(Boid* boid : boids){
        boid->render();
    }
}

void Flock::render(Shader& shader) {
    for(Boid* boid : boids){
        boid->render(shader);
    }
}
