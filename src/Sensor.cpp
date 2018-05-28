#include "Sensor.h"
#include "Unit.h"
#include <WorldEngine/WorldGeometry.h>
#include <Enumeration.h>

Sensor::Sensor(Entity* _entity) :
	propietary(_entity),
    /*priorityTarget(nullptr),*/
    sensorHitbox(Vector2<f32>(0,0),
    Vector2<f32>(std::sqrt(std::pow(_entity->getViewRadius(),2) + std::pow(_entity->getViewRadius(),2)),
    std::sqrt(std::pow(_entity->getViewRadius(),2) + std::pow(_entity->getViewRadius(),2))))
{}

Sensor::~Sensor() {

}

void Sensor::update() {
    //if (priorityTarget != nullptr) {
    //    priorityTarget->removeHostile(propietary);
    //}
    Entity* priorityTarget(nullptr);
    WorldGeometry::Instance()->getCollidingEntities(sensorHitbox, &priorityTarget, propietary->getTeam());
    if(priorityTarget != nullptr){
        if(propietary -> getTarget() == nullptr){
            propietary->setTarget(priorityTarget);
        }
        else{
            propietary->getTarget()->removeHostile(propietary);
            propietary->setTarget(priorityTarget);
        }
    }
}

void Sensor::move(Vector2<f32> _vectorPosition) {
    sensorHitbox.moveHitbox(_vectorPosition);
}