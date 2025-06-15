#include "GameScreen.hpp"

GameScreen::GameScreen(Context& ctx) : Screen(ctx) {}

void GameScreen::handleEvent(const sf::Event& event) {
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>()) {
        if (kp->scancode == sf::Keyboard::Scancode::Escape) {
            ctx.state = State::Menu;
        }
    }
}

void GameScreen::update(f32 dt) {}

void GameScreen::draw() {
    sf::Text temp(ctx.fontRegular, "Game Screen !", 50);
    ctx.window.draw(temp);
}