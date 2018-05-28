#include "CBuild.h"
#include "../IA.h"

CBuild::CBuild(Action* relatedAction, std::string buildingType, i32 buildingMetalCost, i32 BuildingCrystalCost):Condition(relatedAction) {
    type = buildingType;
    metal = buildingMetalCost;
    crystal = BuildingCrystalCost;
}

CBuild::~CBuild() {

}

Enumeration::BehaviourState CBuild::Update() {
    if (IA::Instance() -> getRootNode() -> getPriority() == nullptr) {
        if (type == "Barn") {
                if (IA::Instance() -> getTree() -> getRequireBarn() && IA::Instance() -> getCityLevel() >= IA::Instance()-> getTree()->barnMilestone) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildBarn);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
        } else if (type == "Barrack") {
                if (IA::Instance() -> getTree() -> getRequireBarrack()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildBarrack);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
        } else if (type == "DefenseBarrack") {
                if (IA::Instance() -> getUnderAttack() == true && IA::Instance() -> getTree() -> getRequireBarrack()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildBarrack);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
        } else if (type == "Hospital") {
                if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getHospitalMilestone()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildHospital);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
        } else if (type == "House") {
                bool needHouse = IA::Instance() -> getLimitReached();
                if (IA::Instance() -> getMaxPeople() != 200) { //El maximo?
                    needHouse = false;
                }
                if (IA::Instance() -> getMaxPeople() / IA::Instance() -> getCityLevel() >= 0.2) {
                    needHouse = false;
                }


                if (needHouse || (IA::Instance() -> getTree() -> calculateCitizensRate() < IA::Instance() -> getTree() -> getCitizensThreshold())) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildHome);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
        } else if (type == "LastChoiceHouse") {
                IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildHome);
                actionToDo();
                return Enumeration::BehaviourState::Success;
        } else if (type == "Market") {
                if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getMarketMilestone()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildMarket);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
        } else if (type == "Quarry") {
                if (IA::Instance() -> getTree() -> getRequireCrystal() || (IA::Instance() -> getTree() -> getShortOnCrystal() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getQuarryMilestone())) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildQuarry);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
        } else if (type == "School") {
                if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildSchool);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
        } else if (type == "Siderurgy") {
                if (IA::Instance() -> getTree() -> getShortOnMetal()) { 
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildSiderurgy);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
        } else if (type == "Workshop" ) {
                if (IA::Instance() -> getTree() -> getRequireWorkshop() && IA::Instance() -> getCityLevel() >= IA::Instance()-> getTree()->workshopMilestone) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildWorkshop);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
        }
        return Enumeration::BehaviourState::Failure;
    } else {
        actionToDo();
        return Enumeration::BehaviourState::Success;
    }
}

void CBuild::actionToDo() {
    if (IA::Instance() -> isSolvent(metal, crystal, 0)) {
        action -> Update(type);
        IA::Instance() -> getRootNode() -> setPriority(nullptr);
    } else {
        IA::Instance() -> getRootNode() -> setPriority(this);
    }
}