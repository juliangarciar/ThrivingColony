#ifndef MAP_H
#define MAP_H

#include "CameraController.h"
#include "Human.h"
#include "IA.h"
#include "Hud.h"

#include <GraphicEngine/Terrain.h>
#include <GraphicEngine/Light.h>
#include <GraphicEngine/Skybox.h>

#include <Types.h>

/**
 * @class Map.
 * @brief Create a Map type object. Singleton class.
 */
class Map {

    public:
        /**
         * @brief Get the instance of the class. If it doesn't exist, create a new instance.
         * 
         * @return Pointer to a Map object that will be the value of instance variable.
		 */
        static Map* Instance();

        /**
		 * @brief Initialize all variables.
		 */
        void Init();

        /**
		 * @brief Get the inputs of the camera and the mouse.
		 */
        void Input();

        /**
		 * @brief Update the camera.
         * 
         * @see void Update(f32) method from CameraController class.
		 */
        void Update();

        /**
		 * @brief Render.
		 */
        void Render();

        /**
         * @brief Delete all variables.
         */
        void CleanUp();

		/**
		 * @brief Set the Map object
		 * 
		 */
		void setMap(std::string);

		/**
		 * @brief Set the Breeds object
		 * 
		 */
		void setBreeds(std::string, std::string);

        /**
        * @brief Get the terrain.
        * 
        * @return Pointer to a Terrain object that will be the value of the terrain variable.
        */
        Terrain* getTerrain();

        /**
         * @brief Get the position of the human player's command center.
         * @return Vector2 that will be the value of humanStartPos variable.
         */
        Vector2<f32> getHumanStartPosition();

        /**
         * @brief Get the position of the AI player's command center.
         * 
         * @return Vector2 that will be the value of iaStartPos variable.
         */
        Vector2<f32> getIAStartPosition();

        /**
         * @brief Get the postion of the terrain correspondent to the position of the mouse cursor.
         * 
         * @return Vector3 that will be the value of collisionPoint variable.
         */
        Vector3<f32> getMouseCollitionPoint();

        /**
         * @brief Get the current active camera.
         * 
         * @return Pointer to a CameraController object that will be the value of camera variable.
         */
        CameraController* getCamera();

		/**
		 * @brief Get the Map Margin
		 * 
		 * @return Margins* 
		 */
		Margins *getMapMargins();

		/**
		 * @brief Get the Metal Productivity
		 * 
		 * @return i32 
		 */
		i32 getMetalProductivity();

		/**
		 * @brief Get the Crystal Productivity
		 * 
		 * @return i32 
		 */
		i32 getCrystalProductivity();

		/**
		 * @brief Get the Citizen Increment object
		 * 
		 * @return i32 
		 */
		i32 getCitizenIncrement();
		
		/**
		 * @brief Get the Expansion Increment
		 * 
		 * @return i32 
		 */
		i32 getInfluenceRangeIncrement();

		/**
		 * @brief Get the Influence Range Increment Limit
		 * 
		 * @return i32 
		 */
		i32 getInfluenceRangeIncrementLimit();

    protected:
        /**
		 * @brief Map constructor.
		 */
        Map();

        /**
		 * @brief Map destructor.
		 */
        virtual ~Map();

    private:
        /**
         * @brief Show at the terminal the progress of the map loading.
         * 
         * @param i32 is the value of the current progress.
         */
        void loadProgress(i32);

		//
		bool iaEnabled;

		//
		std::string loadMap;

		//
		std::string humanBreed;
		std::string iaBreed;

        //Pointer to the only instance of Human class.
        static Map* pinstance;

        //Pointer to the current active camera.
        CameraController *camera;

        //Pointer to the human player's object.
        Human *human;

        //Pointer to the AI player's object.
        IA *ia;

        //Pointer to the hud that will be used.
        Hud *hud;

        //Pointer to the terrain.
        Terrain *terrain;

        //Skybox of the map.
        Skybox* skybox;

        //List of lights.
        std::vector<Light*> lights;

        //Position of the human player's command center.
        Vector2<f32> humanStartPos;

        //Position of the AI player's command center.
        Vector2<f32> iaStartPos;

        //Position of the terrain correspondent to the position of the mouse cursor.
        Vector3<f32> collisionPoint;

		//MapMargins
		Margins *mapMargins;
		
        //Production of metal.
        i32 metalProductivity;

        //Production of crystal.
        i32 crystalProductivity;

		//Citizen increment
		i32 citizenIncrement;

		//Terrain increment
		i32 influenceRangeIncrement;

		//Number of times you can expand your terrain
		i32 influenceRangeIncrementLimit;

		//Conditions
		FinishCondition winCondition;
		FinishCondition loseCondition;
};

#endif