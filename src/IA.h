#ifndef IA_H
#define IA_H

#include "Player.h"
#include "AIEngine/BehaviourTree.h"
#include "AIEngine/ActiveSelector.h"
#include <Types.h>

/**
 * @class IA.
 * @brief Create a IA type object. Public heritage from Player class. Singleton class.
 */
class IA : public Player {
    
    public:
        /**
         * @brief Get the instance of the class. If it doesn't exist, create a new instance.
         * 
         * @return Pointer to a IA object that will be the value of instance variable.
		 */
        static IA* Instance();

        /**
		 * @brief Initialize all variables.
		 */
        void Init(std::string _race);

		/**
		 * @brief 
		 * 
		 */
		void Input();

        /**
         * @brief Update buildings, units variables and choice the next step when is time.
         */
        void Update();
        
        /**
         * @brief Delete all variables.
         */
        void CleanUp();

        /**
         * @brief Deteerminate the position where will be built the next building.
         * 
         * @return Vector2 that will be the position where the next uilding wiil be built.
         */
        Vector2<f32> determinatePositionBuilding(const Box2D& buildingHitbox) const;

        /**
         * @brief Initialize all choices that can do the AI player.
         */
        void initializeChoices();

        /**
         * @brief Choose the behaviour that is going to have the AI.
         */
        void chooseBehaviour();
        
        /**
         * @brief Set choiceIndex variable as the value passed by parameter.
         * 
         * @param i32 is the value that is going to be set to choiceIndex variable.
         */
        void setChoiceIndex(i32);

        /**
         * @brief Determinate if the AI's city is under attack.
         * 
         * @return True if there ir any enemie troop near the AI's city and false in other case.
         */
        bool getUnderAttack();
        
        /**
         * @brief Get the next choice of the AI.
         * 
         * @return std::string that will be the value of choices variable at choiceIndex position.
         */
        std::string getNextChoice();

        /**
         * @brief Get the choosen beahviour of the AI.
         * 
         * @return std::string that will be the value of chosenBehaviour variable.
         */
        std::string getChosenBehaviour();

        /**
         * @brief Get the beahaviour tree of the AI.
         * 
         * @return Pointer to a BehaviourTree object that will be the value of tree variable.
         */
        BehaviourTree* getTree();

        /**
         * @brief Get the behaviour trre of the AI.
         * 
         * @return Pointer to a ActiveSelector that will be the value of rootNode variable.
         */
        ActiveSelector* getRootNode();

        /**
         * @brief Checks if there are units idling.
         * 
         * @return true there are units idling or moving.
         * @return false if there are units attacking.
         */
        bool getIdleTroops();
        
        /**
         * @brief Get the speed at which is going to be update the next choose of the AI.
         * 
         * @return True if it updates fast and false in other case.
         */
        bool getFast();

        /**
         * @brief Create a very happy behaviour tree for the AI.
         */
        void veryHappyBehaviour();

        /**
         * @brief Create a happy behaviour tree for the AI.
         */
        void happyBehaviour();

        /**
         * @brief Create a neutral behaviour tree for the AI.
         */
        void neutralBehaviour();

        /**
         * @brief Create a unhappy behaviour tree for the AI.
         */
        void unhappyBehaviour();

        /**
         * @brief Create a very unhappy behaviour tree for the AI.
         */
        void veryUnhappyBehaviour();

        /**
         * @brief Get the AI's city level plus the city level that is going to recive when all the buildings that are being built finish.
         * 
         * @return i32 that will be the sum of the values of cityLevel and cityLevelInComing variables.
         */
        i32 getCityLevel();

        /**
         * @brief Get the happiness of the AI's city plus the happiness that is going to recive when all the buildings that are being built finish.
         * 
         * @return i32 that will be the sum of the values of happiness and happinessInComing variables.
         */
        i32 getHappiness();

        /**
         * @brief Get the maximum people of the AI's city plus the people that is going to recive when all the buildings that are being built finish.
         * 
         * @return i32 that will be the sum of the values of maxPeople and maxPeopleInComing variables.
         */
        i32 getMaxPeople();

        /**
         * @brief Get the army level of the AI's city plus the army level that is going to recive when all the buildings that are being built finish.
         * 
         * @return i32 that will be the sum of the values of armyLevel and armyLevelInComing variables.
         */
        i32 getArmyLevel();
        
        /**
         * @brief Modify the AI's city level that is going to recive when all the buildings that are being built finish based on the city level passed by parameter.
         * 
         * @param i32 that will be the amount that is going to be added to or substracted from the cityLevelInComing variable.
         */
        void modifyCityLevelInComing(i32);

        /**
         * @brief Modify the happiness of the AI's city that is going to recive when all the buildings that are being built finish based on the happiness passed by parameter.
         * 
         * @param i32 that will be the amount that is going to be added to or substracted from the happinessInComing variable.
         */
        void modifyHappinessInComing(i32);

        /**
         * @brief Modify the maximum people of the AI's city that is going to recive when all the buildings that are being built finish based on the maximum people passed by parameter.
         * 
         * @param i32 that will be the amount that is going to be added to or substracted from the maxPeopleInComing variable.
         */
        void modifyMaxPeopleInComing(i32);

        /**
         * @brief Modify the army level of the AI's city that is going to recive when all the buildings that are being built finish based on the army level passed by parameter.
         * 
         * @param i32 that will be the amount that is going to be added to or substracted from the armyLevelInComing variable.
         */
        void modifyArmyLevelInComing(i32);

    protected:
        /**
         * @brief IA constructor.
         */
        IA();

        /**
         * @brief IA destructor.
         */
        virtual ~IA();

    private:
        //Pointer to the only instance of IA class.
        static IA* instance;

        //Pointer to the root of the behaviour tree.
        BehaviourTree* tree;

        //Pointer to the root of the behaviour tree.
        ActiveSelector *rootNode;

        //Type of behaviour.
        Enumeration::IABehaviour behaviour;

        //Behaviour of the AI.
        std::string chosenBehaviour;

        //All choices the AI can do.
        std::vector<std::string> *choices;

        //Current choice of the AI.
        i32 choiceIndex;

        //Determine if the choice of the AI is updated fast or not. True will be the fast mode and false the slow one.
        bool fast;

        //Timer used to update fast the AI's choices.
        Timer* updateFastTimer;

        //Timer used to update slow tha AI's choices.
        Timer* updateSlowTimer;

        //Happiness of the AI's city that is going to recive when all the buildings that are being built finish.
        i32 happinessInComing;

        //AI's city level that is going to recive when all the buildings that are being built finish.
        i32 cityLevelInComing;

        //AI's army level that is going to recive when all the buildings that are being built finish.
        i32 armyLevelInComing;

		//Player's max people amount that is going to recive when all the buildings that are being built finish.
		i32 maxPeopleInComing;
};

#endif