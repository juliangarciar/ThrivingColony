#include "Mouse.h"
#include <GraphicEngine/Window.h>
#include <IOEngine/IO.h>


Mouse::Mouse() {
    visible = true;
    currentCursor = CURSOR_NORMAL;
    oldState = GLFW_RELEASE;
    for (i32 i = 0; i < GLFW_MOUSE_BUTTON_LAST;i++) {
        mouseButtonState[i] = Enumeration::UP;
    }

    GLFWwindow *window = Window::Instance() -> getWindow();

    cursor = glfwCreateStandardCursor(CURSOR_NORMAL);
    glfwSetCursor(window, cursor);
    
    //Handle events on queue
    glfwSetCursorPosCallback(window,
            [](GLFWwindow *w, f64 x, f64 y) {
            Window::Instance() -> getGUIEnvironment() -> cursorPosCallbackEvent(x, y);
        }
    );

    glfwSetScrollCallback(window,
        [](GLFWwindow *w, f64 x, f64 y) {
            Window::Instance() -> getGUIEnvironment() -> scrollCallbackEvent(x, y);
            Mouse *s = IO::Instance() -> getMouse();
            s -> wheel.x = x;
            s -> wheel.y = y;
       }
    );

    /* Change this */
    glfwSetMouseButtonCallback(window,
        [](GLFWwindow *w, i32 button, i32 action, i32 modifiers) {
            Window::Instance() -> getGUIEnvironment() -> mouseButtonCallbackEvent(button, action, modifiers);
            Mouse *s = IO::Instance() -> getMouse();
            if (action == GLFW_PRESS /*&& s->getOldState() == GLFW_RELEASE*/) {
                //s->setOldState(action);
                s -> mouseButtonState[button] = Enumeration::PRESSED;
            } else if (action == GLFW_RELEASE /*&& s->getOldState() == GLFW_PRESS*/) {
                //s->setOldState(action);
                s -> mouseButtonState[button] = Enumeration::RELEASED;
            }
        }
    );
    /* Custom cursors */
    customCursor = std::vector< GLFWcursor* >();

   
}

Mouse::~Mouse() {
    glfwDestroyCursor(cursor);
    cursor = nullptr;
}

void Mouse::refreshStates() {
    // Reset pressed
    for (i32 i = 0; i < GLFW_MOUSE_BUTTON_LAST;i++) {
        if (mouseButtonState[i] == Enumeration::PRESSED) {
            mouseButtonState[i] = Enumeration::DOWN; // Set to Pressed
        } else if (mouseButtonState[i] == Enumeration::RELEASED) {
            mouseButtonState[i] = Enumeration::UP; // Set to Pressed
        }
    }

    //Reset scroll
    wheel.x = 0;
    wheel.y = 0;
}

// Left button
bool Mouse::leftMousePressed() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_LEFT] == Enumeration::PRESSED) {
        return true;
    } else {
        return false;
    }
}

bool Mouse::leftMouseReleased() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_LEFT] == Enumeration::RELEASED) {
        return true;
    } else {
        return false;
    }
}
bool Mouse::leftMouseUp() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_LEFT] == Enumeration::UP) {
        return true;
    } else {
        return false;
    }
}

bool Mouse::leftMouseDown() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_LEFT] == Enumeration::DOWN) {
        return true;
    } else {
        return false;
    }
}

// Middle button
bool Mouse::middleMousePressed() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_MIDDLE] == Enumeration::PRESSED) {
        return true;
    } else {
        return false;
    }
}

bool Mouse::middleMouseReleased() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_MIDDLE] == Enumeration::RELEASED) {
        return true;
    } else {
        return false;
    }
}

bool Mouse::middleMouseUp() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_MIDDLE] == Enumeration::UP) {
        return true;
    } else {
        return false;
    }
}

bool Mouse::middleMouseDown() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_MIDDLE] == Enumeration::DOWN) {
        return true;
    } else {
        return false;
    }
}

// Right button
bool Mouse::rightMousePressed() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_RIGHT] == Enumeration::PRESSED) {
        return true;
    } else {
        return false;
    }
}

bool Mouse::rightMouseReleased() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_RIGHT] == Enumeration::RELEASED) {
        return true;
    } else {
        return false;
    }
}

bool Mouse::rightMouseUp() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_RIGHT] == Enumeration::UP) {
        return true;
    } else {
        return false;
    }
}

bool Mouse::rightMouseDown() {
    if (mouseButtonState[GLFW_MOUSE_BUTTON_RIGHT] == Enumeration::DOWN) {
        return true;
    } else {
        return false;
    }
}

// Mouse wheel
f32 Mouse::getWheelX() {
    return wheel.x;
}

f32 Mouse::getWheelY() {
    return wheel.y;
}

// Set position
void Mouse::setPosition(Vector2<i32> p) {
    if (position.x != p.x || position.y != p.y) {
        glfwSetCursorPos(Window::Instance() -> getWindow(), p.x, p.y);
        position.set(p.x, p.y);
    }
}

// Icon
void Mouse::changeIcon(i32 shape) {
    if (isVisible() && shape != currentCursor) {
        //glfwDestroyCursor(cursor);
        cursor = glfwCreateStandardCursor(shape);
        glfwSetCursor(Window::Instance() -> getWindow(), cursor);
        currentCursor = shape;
    }
}

// Mouse visible
void Mouse::show() {
    glfwSetInputMode(Window::Instance() -> getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    visible = true;
}

void Mouse::hide() {
    glfwSetInputMode(Window::Instance() -> getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    visible = false;
}

Vector2<i32> Mouse::getPosition() {
    f64 x, y;
    glfwGetCursorPos(Window::Instance() -> getWindow(), &x, &y);
    position.set(x, y);
    return position;
}

GLFWcursor *Mouse::getMouse() {
    return cursor;
}

bool Mouse::isVisible() {
    return visible;
}

i32 Mouse::getOldState() {
    return oldState;
}

void Mouse::setOldState(i32 data) {

}

// Icon
void Mouse::changeCustomIcon(i32 shape) {
    if (isVisible() && shape != currentCursor && shape < customCursor.size()) {
        //glfwDestroyCursor(cursor);
        //cursor = glfwCreateCursor(&customIcon[shape], 0, 0);
        cursor = customCursor[shape];
        glfwSetCursor(Window::Instance() -> getWindow(), customCursor[shape]);
        currentCursor = shape;
    }
}

void Mouse::loadCursorIcon(unsigned char* _data, i32 _width, i32 _height, i32 _channels) {
    GLFWimage image;
    image.width = _width;
    image.height = _height;
    image.pixels = _data;
    GLFWcursor* newCursor = glfwCreateCursor(&image, 0, 0); 
    customCursor.push_back(newCursor);
}