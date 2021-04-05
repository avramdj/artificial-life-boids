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
    //TODO change general direction formula
    general_direction = glm::normalize(general_direction);
}

/*
 * Update direction of all boids to account for collision avoidance.
 */
void Flock::separate(float delta_time) {
    //TODO
    for(Boid* boid : boids) {
        for(Boid* other : boids) {
            glm::vec3 sub = boid->getPos() - other->getPos();
            float len = glm::length(sub);
            if(boid != other && abs(len) < collision_distance){
                boid->addDirection(sub, delta_time/sep_const*(1/len+0.5));
            }
        }
    }
}

/*
 * Update direction of all boids to account for the general direction of the flock
 */
void Flock::align(float delta_time) {
    for(Boid* boid : boids) {
        boid->addDirection(general_direction, delta_time/align_const);
    }
}

/*
 * Update diraction of all boids to account for center of mass.
 */
void Flock::cohere(float delta_time) {
    for(Boid* boid : boids) {
        boid->addDirection(center_of_mass - boid->getPos(), delta_time/cohere_const);
    }
}

int Flock::size() {
    return boids.size();
}

void Flock::update(float dt) {
    float delta_time = dt * speed;
    update_centers();
    separate(delta_time);
    align(delta_time);
    cohere(delta_time);
    move(delta_time);
}

void Flock::move(float delta_time) {
    for(Boid* boid : boids) {
        boid->move(delta_time);
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
        boid->move(0);
    }
}

const set<Boid *> &Flock::getBoids() const {
    return boids;
}
