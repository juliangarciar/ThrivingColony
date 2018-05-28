#include "DefeatMenu.h"

#include "Game.h"

DefeatMenu::DefeatMenu() {
    buttonQuit = new Button("Quit");
    buttonQuit -> setPosition(Vector2<i32>(600, 400));

    buttonStart = new Button("Main Menu");
    buttonStart -> setPosition(Vector2<i32>(600, 300));

    winText = new Label("Defeat");
    Window::Instance() -> setGUI();
}

DefeatMenu::~DefeatMenu() {
    delete buttonQuit;
    delete buttonStart;
    delete winText;
}

void DefeatMenu::setHUDEvents() {
    buttonQuit -> setCallback([]{
        Window::Instance() -> close();
    });

    buttonStart -> setCallback([]{
        Game::Instance() -> changeState(Enumeration::State::MenuState);
    });
}