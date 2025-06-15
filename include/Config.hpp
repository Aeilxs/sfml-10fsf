#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <iostream>

using u8 = char;
using f32 = float;
using f64 = double;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

namespace Config {
constexpr u32 WINDOW_WIDTH = 1280;
constexpr u32 WINDOW_HEIGHT = 720;
constexpr sf::Vector2u WINDOW_SIZE = {WINDOW_WIDTH, WINDOW_HEIGHT};

constexpr const char* WINDOW_TITLE = "10 Fast Fingers";

constexpr const char* WORDS_FILE_PATH = "assets/words/english.txt";
constexpr const char* SAVES_FILE_PATH = "assets/saves.csv";

constexpr f32 GAME_DURATION_SECONDS = 60.0f;
constexpr u32 TARGET_FPS = 144;

}  // namespace Config
