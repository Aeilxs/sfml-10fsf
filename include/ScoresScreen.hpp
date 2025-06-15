#pragma once

#include "GameScreen.hpp"
#include "Screen.hpp"

class ScoresScreen : public Screen {
   public:
    explicit ScoresScreen(Context& ctx);
    ~ScoresScreen() override = default;

    void handleEvent(const sf::Event& event) override;
    void update(f32 dt) override;
    void draw() override;

    void loadSaves();

   private:
    std::vector<GameState> saves;
    u32 index = 0;
};
