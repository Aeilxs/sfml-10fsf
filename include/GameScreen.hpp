#pragma once

#include "Screen.hpp"

struct GameState {
    std::string currentWord;
    std::vector<std::string> nextWords;

    std::string userInput;

    u32 wordsTyped = 0;
    u32 totalTypedWords = 0;
    u32 lettersTyped = 0;
    u32 correctLettersTyped = 0;
    u32 incorrectLettersTyped = 0;
    u32 backspacesUsed = 0;
    u32 maxCombo = 0;
    u32 currentCombo = 0;

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
    // === DATA ===
    GameState gstate;
    std::vector<std::string> words;
    sf::RectangleShape wordBox;  // pour éviter de le recréer à chaque frame

    // === CORE ===
    std::string pickRandomWord();
    void loadWords();
    void initWordsBuffer();

    // === EVENTS ===
    void handleEscape(const sf::Event& event);
    void handleTyping(const sf::Event& event);
    void updateLetterStats(char typedChar);

    // === UPDATE ===
    void updateTimer(f32 dt);
    void checkWordCompletion();

    // === DRAW ===
    void drawWordBox();
    void drawWords();
    void drawInputBox();
    void drawStats();
};
