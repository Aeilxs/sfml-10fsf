#pragma once

#include "Screen.hpp"

class ScoresScreen : public Screen {
   public:
    explicit ScoresScreen(Context& ctx);
    ~ScoresScreen() override = default;

    void handleEvent(const sf::Event& event) override;
    void update(f32 dt) override;
    void draw() override;

   private:
};
