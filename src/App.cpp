#include "App.hpp"
#include "Config.hpp"
#include "MenuScreen.hpp"
#include "Screen.hpp"
#include <iostream>

App::App(Context& ctx) : ctx(ctx), menuScreen(ctx), gameScreen(ctx), scoresScreen(ctx) {
    currentScreen = &menuScreen;
}
App::~App() {}

void App::pollEvents() {
    while (const std::optional event = ctx.window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            ctx.window.close();
        }

        currentScreen->handleEvent(*event);
    }
}

void App::run() {
    sf::Clock clock;
    while (ctx.window.isOpen()) {
        f32 dt = clock.restart().asSeconds();
        this->pollEvents();
        ctx.window.clear();
        switch (ctx.state) {
            case State::Menu:
                currentScreen = &menuScreen;
                break;
            case State::Playing:
                if (currentScreen != &gameScreen) {
                    gameScreen.reset();
                }
                currentScreen = &gameScreen;
                break;

            case State::Scores:
                scoresScreen.loadSaves();
                currentScreen = &scoresScreen;
                break;
            case State::GameOver:
                ctx.needReload = true;
                currentScreen = &scoresScreen;
                break;
        }

        currentScreen->update(dt);
        currentScreen->draw();
        ctx.window.display();
    }
}
