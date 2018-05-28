#ifndef CAMERA_H
#define CAMERA_H

#include <OBDEngine/OBDCamera.h>

#include <Types.h>
#include <MathEngine/Vector3.h>

class Camera {
    
    public:
        Camera();
        ~Camera();

        void setCameraPosition(Vector3<f32> position);
        void setTargetPosition(Vector3<f32> position);

        void setFarValue(f32 sd);

        Vector3<f32> getCameraPosition();
        Vector3<f32> getTargetPosition();
    private:
		OBDCamera *c;
};

#endif