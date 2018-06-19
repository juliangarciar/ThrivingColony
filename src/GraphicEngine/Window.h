#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <nanogui/nanogui.h>
#include <OBDEngine/OBDEngine.h>

#include <Types.h>
#include <MathEngine/Vector2.h>

class Window {
    public:
        static Window* Instance();

		void Init(i32, i32);

        void handleGUIEvents();

        void setGUI();

        void beginScene();
        void endScene();

        void close();

        bool isOpen();
        
        void onClose();

		OBDEngine *getEngine();

		void setResizeCallback(std::function<void(i32, i32)>);

		void triggerResizeCallback(i32, i32);
		
        nanogui::Screen* getGUIEnvironment();

        i32 getWindowWidth();
        i32 getWindowHeight();

        f32 getDeltaTime() const;
        f32 getLastDeltaTime() const;
        f32 getDeltaTimeVariance() const;
        
        GLFWwindow *getWindow() {
            return window;
        }

		/**
		 * @brief Get the Engine Resource Manager object
		 * 
		 * @return ResourceManager* 
		 */
		ResourceManager *getEngineResourceManager();

        /**
         * @brief calculates the framerate of the window. It is important to call
         * this function after the game logic has fully executed to see how long it
         * took to get through it, otherwise results won't be correct.
         * 
         */
        void calculateFramerate();

        /**
         * @brief returns the current framerate
         * 
         * @return i32 framerate
         */
        i32 getFrameRate();

        /**
         * @brief Get the program where are going to be created all Skybox.
         * 
         * @return OBDShaderProgram* that is going to be the value of SkyboxLayer.
         */
        OBDShaderProgram* getSkyboxProgram();

        /**
         * @brief Get the layer where are going to be created all Skybox.
         * 
         * @return OBDSceneNode* that is going to be the value of SkyboxLayer.
         */
        OBDSceneNode* getSkyboxLayer();

        /**
         * @brief Get the program where are going to be created all billboards.
         * 
         * @return OBDShaderProgram* that is going to be the value of billboardLayer.
         */
        OBDShaderProgram* getBillboardProgram();

        /**
         * @brief Get the layer where are going to be created all billboards.
         * 
         * @return OBDSceneNode* that is going to be the value of billboardLayer.
         */
        OBDSceneNode* getBillboardLayer();

        /**
         * @brief Get the program where are going to be created all image.
         * 
         * @return OBDShaderProgram* that is going to be the value of imageLayer.
         */
        OBDShaderProgram* getImageProgram();

        /**
         * @brief Get the layer where are going to be created all image.
         * 
         * @return OBDSceneNode* that is going to be the value of imageLayer.
         */
        OBDSceneNode* getImageLayer();
        
        i32 windowWidth;
        i32 windowHeight;
		Vector2<i32> screenCenter;
    protected:
        Window();
        virtual ~Window();
        Window(const Window & );
        Window &operator = (const Window & );
    private:
        void setGLAttributes();

        static Window* pinstance;

        GLFWwindow* window;

        bool closeWindow;

		OBDEngine *engine;

        //Layer where are going to be created all skybox;
		OBDShaderProgram *skyboxProgram;
        OBDSceneNode* skyboxLayer;

        //Layer where are going to be created all billboards;
		OBDShaderProgram *billboardProgram;
        OBDSceneNode* billboardLayer;

        //Layer where are going to be created all image;
		OBDShaderProgram *imageProgram;
        OBDSceneNode* imageLayer;
		
		GLuint VAO;
        nanogui::Screen* gui;
        
        f64 dtThen;
        f64 deltaTime;
        f64 lastDeltaTime;
        i32 framerate;

		std::function<void(i32, i32)> resizeCallback;
};

#endif