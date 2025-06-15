#pragma once

#include "Screen.hpp"

class GameScreen : public Screen {
   public:
    explicit GameScreen(Context& ctx);
    ~GameScreen() override = default;

    void handleEvent(const sf::Event& event) override;
    void update(f32 dt) override;
    void draw() override;

   private:
};
