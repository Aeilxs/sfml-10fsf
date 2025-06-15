#include "ScoresScreen.hpp"

ScoresScreen::ScoresScreen(Context& ctx) : Screen(ctx) {}

void ScoresScreen::handleEvent(const sf::Event& event) {
    if (const auto* kp = event.getIf<sf::Event::KeyPressed>()) {
        if (kp->scancode == sf::Keyboard::Scancode::Escape) {
            ctx.state = State::Menu;
        }
    }
}

void ScoresScreen::update(f32 dt) {}
void ScoresScreen::draw() {
    sf::Text temp(ctx.fontRegular, "Scores Screen !", 50);
    ctx.window.draw(temp);
}