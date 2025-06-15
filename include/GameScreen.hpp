#pragma once

#include "Screen.hpp"

struct GameState {
    std::string currentWord;
    std::vector<std::string> nextWords;

    std::string userInput;

    u32 wordsTyped = 0;
    u32 lettersTyped = 0;

    f32 timeElapsed = 0.0f;

    bool isFinished = false;
};

class GameScreen : public Screen {
   public:
    explicit GameScreen(Context& ctx);
    ~GameScreen() override = default;

    void handleEvent(const sf::Event& event) override;
    void update(f32 dt) override;
    void draw() override;

   private:
    GameState gstate;
    std::vector<std::string> words;

    std::string pickRandomWord();
};
