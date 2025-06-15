#pragma once
#include "Config.hpp"
#include <SFML/Graphics.hpp>
#include <random>

enum class State { Menu, Playing, GameOver, Scores };

struct Context {
    sf::RenderWindow window;

    sf::Font fontBold;
    sf::Font fontItalic;
    sf::Font fontRegular;

    State state = State::Menu;
    std::mt19937 rng;

    Context()
        : window(sf::VideoMode(Config::WINDOW_SIZE), Config::WINDOW_TITLE),
          fontBold(sf::Font("assets/fonts/UbuntuMonoNerdFont-Bold.ttf")),
          fontRegular(sf::Font("assets/fonts/UbuntuMonoNerdFont-Regular.ttf")),
          fontItalic(sf::Font("assets/fonts/UbuntuMonoNerdFont-Italic.ttf")),
          rng(std::random_device{}()) {
        window.setFramerateLimit(Config::TARGET_FPS);
    }
};
