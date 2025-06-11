#include <SFML/Graphics.hpp>
#include <iostream>

#include "App.hpp"
#include "config.hpp"

int main() {
    App app;
    auto window = sf::RenderWindow(sf::VideoMode(Config::WINDOW_SIZE), Config::WINDOW_TITLE);
    window.setFramerateLimit(Config::TARGET_FPS);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
