#include "Human.h"

#include "Enumeration.h"
#include "IA.h"
#include "GraphicEngine/Window.h"
#include "IOEngine/IO.h"
#include <OBDEngine/ResourceManager/ResourceJSON.h>

Human* Human::instance = 0;

Human* Human::Instance() {
    if (instance == 0) {
        instance = new Human();
    }
    return instance;
}

Human::Human() : Player(Enumeration::Team::Human) {
}

Human::~Human() {
    delete buildings;
	buildings = nullptr;
    delete units;
	units = nullptr;
}

void Human::Init(std::string _race) {
    Player::Init();

    buildings = new BuildingManager(Enumeration::Team::Human, _race);
    units = new UnitManager(Enumeration::Team::Human, _race);
}

void Human::Input() {
	buildings -> testRaycastCollisions();
	units -> testRaycastCollisions();
}

void Human::Update() {
	Player::Update();
	
	buildings -> drawBuilding();
    units -> updateUnitManager();
}

void Human::CleanUp() {
// Add a call to clean the cells the buildings inhabit
    delete buildings;
    delete units;
}

bool Human::getUnderAttack() {
    if (underAttack == false) {
        Vector2<f32> pos = buildings -> getBuildings() -> begin() -> second -> getPosition();
        i32 requesterRange = 1000;
        
        f32 xaux = 0;
        f32 yaux = 0;
        f32 dist = 0;
        // Get units in the map of the opposing team
        std::map<i32, Unit*> *inMapTroops = IA::Instance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end() && underAttack == false; ++it) {
            if (it  -> second != nullptr) {
            // Calculate distance between troop requesting target and posible targets
                xaux = it -> second -> getPosition().x - pos.x;

                yaux = it -> second -> getPosition().y - pos.y;
                dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                if (dist <= requesterRange) {
                    underAttack = true;
                }
            }
        }
    }
    return underAttack;
}