#pragma once

#include "App.hpp"
#include "Context.hpp"
#include "GameScreen.hpp"
#include "MenuScreen.hpp"
#include "ScoresScreen.hpp"
#include "Screen.hpp"

class App {
   public:
    App(Context& ctx);
    ~App();

    void run();

   private:
    Context& ctx;

    void pollEvents();

    Screen* currentScreen;
    MenuScreen menuScreen;
    GameScreen gameScreen;
    ScoresScreen scoresScreen;
};