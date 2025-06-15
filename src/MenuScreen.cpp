#include "MenuScreen.hpp"
#include "Config.hpp"
#include "GameScreen.hpp"
#include "Screen.hpp"

MenuScreen::MenuScreen(Context& ctx) : Screen(ctx) {
    f32 y = 200.0f;
    for (MenuOptions opt : optionOrder) {
        sf::Text t(ctx.fontRegular, optionToString(opt), 50);
        sf::FloatRect bounds = t.getLocalBounds();
        t.setOrigin(bounds.getCenter());
        t.setPosition({Config::WINDOW_WIDTH / 2.0f, y});
        texts.push_back(t);
        y += 70.0f;
    }
}

void MenuScreen::handleEvent(const sf::Event& event) {
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>()) {
        switch (kp->scancode) {
            case sf::Keyboard::Scancode::Down:
                index = (index + 1) % optionOrder.size();
                break;
            case sf::Keyboard::Scancode::Up:
                index = (index + optionOrder.size() - 1) % optionOrder.size();
                break;
            case sf::Keyboard::Scancode::Enter:
                switch (optionOrder[index]) {
                    case MenuOptions::Start:
                        ctx.state = State::Playing;
                        break;
                    case MenuOptions::Scores:
                        ctx.state = State::Scores;
                        break;
                    case MenuOptions::Quit:
                        ctx.window.close();
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void MenuScreen::update(f32 dt) {
    for (std::size_t i = 0; i < texts.size(); ++i) {
        if (i == index) {
            texts[i].setFillColor(sf::Color::Green);
            texts[i].setFont(ctx.fontBold);
        } else {
            texts[i].setFillColor(sf::Color::White);
            texts[i].setFont(ctx.fontRegular);
        }
    }
}

void MenuScreen::draw() {
    for (const auto t : texts) {
        ctx.window.draw(t);
    }
}
