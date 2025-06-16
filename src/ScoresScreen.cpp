#include "ScoresScreen.hpp"
#include <fstream>
#include <sstream>

ScoresScreen::ScoresScreen(Context& ctx) : Screen(ctx) { loadSaves(); }

void ScoresScreen::loadSaves() {
    if (!ctx.needReload) return;
    ctx.needReload = false;
    std::ifstream file(Config::SAVES_FILE_PATH);
    if (!file) {
        std::cerr << "Cannot open CSV: " << Config::SAVES_FILE_PATH << std::endl;
        return;
    }

    std::string line;
    bool skipHeader = true;
    while (std::getline(file, line)) {
        if (skipHeader) {
            skipHeader = false;
            continue;
        }

        std::stringstream ss(line);
        std::string cell;
        GameState gs;

        std::getline(ss, cell, ',');
        gs.wordsTyped = std::stoi(cell);
        std::getline(ss, cell, ',');
        gs.totalTypedWords = std::stoi(cell);
        std::getline(ss, cell, ',');
        gs.lettersTyped = std::stoi(cell);
        std::getline(ss, cell, ',');
        gs.correctLettersTyped = std::stoi(cell);
        std::getline(ss, cell, ',');
        gs.incorrectLettersTyped = std::stoi(cell);
        std::getline(ss, cell, ',');
        gs.backspacesUsed = std::stoi(cell);
        std::getline(ss, cell, ',');
        gs.maxCombo = std::stoi(cell);
        std::getline(ss, cell, ',');
        gs.timeElapsed = std::stof(cell);

        saves.push_back(gs);
    }
}

void ScoresScreen::handleEvent(const sf::Event& event) {
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>()) {
        switch (kp->scancode) {
            case sf::Keyboard::Scancode::Escape:
                ctx.state = State::Menu;
                break;
            case sf::Keyboard::Scancode::Down:
                if (index + 1 < saves.size()) index++;
                break;
            case sf::Keyboard::Scancode::Up:
                if (index > 0) index--;
                break;
            default:
                break;
        }
    }
}

void ScoresScreen::update(f32 dt) {}
void ScoresScreen::draw() {
    f32 y = 100.f;

    u32 blocksPerPage = 5;

    for (u32 i = index; i < std::min(index + blocksPerPage, (u32)saves.size()); ++i) {
        const auto& gs = saves[i];

        std::vector<std::string> lines = {
            "Run #" + std::to_string(i + 1),
            "Words Typed: " + std::to_string(gs.wordsTyped),
            "Total Letters: " + std::to_string(gs.lettersTyped),
            "Accuracy: " +
                std::to_string(
                    gs.lettersTyped > 0 ? (100 * gs.correctLettersTyped / gs.lettersTyped) : 0) +
                "%",
            "Max Combo: " + std::to_string(gs.maxCombo),
            "Time: " + std::to_string(gs.timeElapsed) + "s"};

        f32 blockX = 100.f;
        f32 blockY = y;

        for (const auto& line : lines) {
            sf::Text t(ctx.fontRegular, line, 30);
            t.setPosition({blockX, blockY});
            ctx.window.draw(t);
            blockY += 35.f;
        }

        sf::RectangleShape sep;
        sep.setSize({800.f, 2.f});
        sep.setFillColor(sf::Color(200, 200, 200));
        sep.setPosition({blockX, blockY});
        ctx.window.draw(sep);

        y = blockY + 20.f;
    }

    sf::Text hint(ctx.fontItalic, "UP/DOWN to scroll, ESC to return", 25);
    hint.setPosition({100.f, y + 20.f});
    ctx.window.draw(hint);
}
