#include "GameScreen.hpp"
#include "Config.hpp"
#include <fstream>
#include <random>

GameScreen::GameScreen(Context& ctx) : Screen(ctx) {
    std::ifstream file(Config::WORDS_FILE_PATH);
    if (!file) {
        std::cerr << "Error - can't open: " << Config::WORDS_FILE_PATH << std::endl;
    }

    std::string word;
    while (std::getline(file, word)) {
        if (!word.empty()) words.push_back(word);
    }
    std::cout << "Loaded " << words.size() << " words." << std::endl;
    file.close();

    gstate.currentWord = pickRandomWord();
    for (int i = 0; i < 5; ++i) {
        gstate.nextWords.push_back(pickRandomWord());
    }
}

std::string GameScreen::pickRandomWord() {
    if (words.empty()) {
        std::cerr << "Empty `GameScreen.words vector` in pickRandomWord()";
        exit(EXIT_FAILURE);
    }

    std::uniform_int_distribution<> distrib(0, words.size() - 1);
    return words[distrib(ctx.rng)];
}

void GameScreen::handleEvent(const sf::Event& event) {
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>()) {
        if (kp->scancode == sf::Keyboard::Scancode::Escape) {
            ctx.state = State::Menu;
        }
    }

    if (const auto* te = event.getIf<sf::Event::TextEntered>()) {
        if (te->unicode < 128 && std::isprint(te->unicode)) {
            gstate.userInput += static_cast<char>(te->unicode);
        } else if (te->unicode == 8 && !gstate.userInput.empty()) {
            gstate.userInput.pop_back();
        }
    }
}

void GameScreen::update(f32 dt) {
    if (gstate.isFinished) return;

    // Timer
    gstate.timeElapsed += dt;
    if (gstate.timeElapsed >= Config::GAME_DURATION_SECONDS) {
        gstate.isFinished = true;
        ctx.state = State::GameOver;
    }

    // auto-advance
    if (gstate.userInput == gstate.currentWord) {
        gstate.wordsTyped++;
        gstate.currentWord = gstate.nextWords.front();
        gstate.nextWords.erase(gstate.nextWords.begin());
        gstate.nextWords.push_back(pickRandomWord());
        gstate.userInput.clear();
    }
}

void GameScreen::draw() {
    f32 y = Config::WINDOW_HEIGHT / 2;
    f32 spacing = 25.0f;

    f32 fontSize = 50.f;
    f32 letterSpacing = fontSize / 2;
    f32 wordWidth = letterSpacing * gstate.currentWord.size();
    f32 x = (Config::WINDOW_WIDTH / 5) - (wordWidth / 2);

    for (size_t i = 0; i < gstate.currentWord.size(); ++i) {
        char c = gstate.currentWord[i];
        sf::Text letter(ctx.fontBold, std::string(1, c), fontSize);
        letter.setPosition({x + i * letterSpacing, y});

        if (i < gstate.userInput.size()) {
            if (gstate.userInput[i] == c) {
                letter.setFillColor(sf::Color::Green);
            } else {
                letter.setFillColor(sf::Color::Red);
            }
        } else {
            letter.setFillColor(sf::Color(150, 150, 150));
        }

        ctx.window.draw(letter);
    }

    f32 nextX = (Config::WINDOW_WIDTH / 5) + (wordWidth / 2) + spacing;

    for (const auto& w : gstate.nextWords) {
        sf::Text wordText(ctx.fontRegular, w, 50);
        wordText.setFillColor(sf::Color::White);
        wordText.setPosition({nextX, y});

        ctx.window.draw(wordText);

        nextX += wordText.getLocalBounds().size.x + spacing;
    }

    sf::Text score(ctx.fontRegular, "Score: " + std::to_string(gstate.wordsTyped), 30);
    score.setPosition({100, 50});
    ctx.window.draw(score);

    sf::Text time(ctx.fontRegular,
                  "Time: " + std::to_string(static_cast<int>(Config::GAME_DURATION_SECONDS -
                                                             gstate.timeElapsed)),
                  30);
    time.setPosition({300, 50});
    ctx.window.draw(time);
}
