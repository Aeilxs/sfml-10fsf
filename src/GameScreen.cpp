#include "GameScreen.hpp"
#include "Config.hpp"
#include <fstream>
#include <random>

GameScreen::GameScreen(Context& ctx) : Screen(ctx) {
    loadWords();
    initWordsBuffer();
}

void GameScreen::loadWords() {
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
}

void GameScreen::initWordsBuffer() {
    gstate.currentWord = pickRandomWord();
    for (int i = 0; i < 30; ++i) {
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
    handleEscape(event);
    handleTyping(event);
}

void GameScreen::handleEscape(const sf::Event& event) {
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>()) {
        if (kp->scancode == sf::Keyboard::Scancode::Escape) {
            ctx.state = State::Menu;
        }
    }
}

void GameScreen::handleTyping(const sf::Event& event) {
    if (const auto* te = event.getIf<sf::Event::TextEntered>()) {
        if (te->unicode < 128 && std::isprint(te->unicode)) {
            gstate.userInput += static_cast<char>(te->unicode);
            gstate.lettersTyped++;
            updateLetterStats(te->unicode);
        } else if (te->unicode == 8 && !gstate.userInput.empty()) {
            gstate.userInput.pop_back();
            gstate.backspacesUsed++;
        }
    }
}

void GameScreen::updateLetterStats(char typedChar) {
    if (gstate.userInput.size() <= gstate.currentWord.size()) {
        char correct = gstate.currentWord[gstate.userInput.size() - 1];
        if (typedChar == correct) {
            gstate.correctLettersTyped++;
        } else {
            gstate.incorrectLettersTyped++;
        }
    } else {
        gstate.incorrectLettersTyped++;
    }
}

void GameScreen::update(f32 dt) {
    if (gstate.isFinished) return;

    updateTimer(dt);
    checkWordCompletion();
}

void GameScreen::updateTimer(f32 dt) {
    gstate.timeElapsed += dt;
    if (gstate.timeElapsed >= Config::GAME_DURATION_SECONDS) {
        gstate.isFinished = true;
        ctx.state = State::GameOver;
    }
}

void GameScreen::checkWordCompletion() {
    if (gstate.userInput == gstate.currentWord) {
        gstate.wordsTyped++;
        gstate.totalTypedWords++;
        gstate.currentCombo++;
        if (gstate.currentCombo > gstate.maxCombo) {
            gstate.maxCombo = gstate.currentCombo;
        }

        gstate.currentWord = gstate.nextWords.front();
        gstate.nextWords.erase(gstate.nextWords.begin());
        gstate.nextWords.push_back(pickRandomWord());
        gstate.userInput.clear();
    }
}

void GameScreen::draw() {
    drawWordBox();
    drawWords();
    drawInputBox();
    drawStats();
}

void GameScreen::drawWordBox() {
    wordBox.setSize({Config::WINDOW_WIDTH * 0.8f, Config::WINDOW_HEIGHT * 0.4f});
    wordBox.setFillColor(sf::Color(50, 50, 50));
    wordBox.setOutlineThickness(2.f);
    wordBox.setOutlineColor(sf::Color::White);
    wordBox.setOrigin(wordBox.getSize() / 2.f);
    wordBox.setPosition({Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT / 2.f - 50});
    ctx.window.draw(wordBox);
}

void GameScreen::drawWords() {
    f32 margin = 20.f;
    f32 x = wordBox.getPosition().x - wordBox.getSize().x / 2.f + margin;
    f32 y = wordBox.getPosition().y - wordBox.getSize().y / 2.f + margin;

    for (size_t i = 0; i < gstate.currentWord.size(); ++i) {
        char c = gstate.currentWord[i];
        sf::Text letter(ctx.fontBold, std::string(1, c), 40);
        if (i < gstate.userInput.size()) {
            letter.setFillColor(gstate.userInput[i] == c ? sf::Color::Green : sf::Color::Red);
        } else {
            letter.setFillColor(sf::Color(200, 200, 200));
        }
        letter.setPosition({x, y});
        ctx.window.draw(letter);
        x += letter.getLocalBounds().size.x + 5.f;
    }

    x += 20.f;
    for (const auto& word : gstate.nextWords) {
        sf::Text wordText(ctx.fontRegular, word, 40);
        wordText.setFillColor(sf::Color::White);
        wordText.setPosition({x, y});

        if (x + wordText.getLocalBounds().size.x >=
            wordBox.getPosition().x + wordBox.getSize().x / 2.f - margin) {
            x = wordBox.getPosition().x - wordBox.getSize().x / 2.f + margin;
            y += wordText.getLocalBounds().size.y + 10.f;
            wordText.setPosition({x, y});
        }

        ctx.window.draw(wordText);
        x += wordText.getLocalBounds().size.x + 20.f;
    }
}

void GameScreen::drawInputBox() {
    sf::RectangleShape inputBox;
    inputBox.setSize({wordBox.getSize().x, 60.f});
    inputBox.setFillColor(sf::Color(30, 30, 30));
    inputBox.setOutlineThickness(2.f);
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setOrigin({inputBox.getSize().x / 2.f, 0.f});
    inputBox.setPosition(
        {wordBox.getPosition().x, wordBox.getPosition().y + wordBox.getSize().y / 2.f + 20.f});
    ctx.window.draw(inputBox);

    sf::Text inputText(ctx.fontRegular, gstate.userInput, 40);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition({inputBox.getPosition().x - inputBox.getSize().x / 2.f + 10.f,
                           inputBox.getPosition().y + 10.f});
    ctx.window.draw(inputText);
}

void GameScreen::drawStats() {
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
