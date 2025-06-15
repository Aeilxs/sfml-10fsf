#pragma once

#include "Screen.hpp"

enum class MenuOptions : u8 {
    Start,
    Scores,
    Quit,

    Count
};

class MenuScreen : public Screen {
   public:
    explicit MenuScreen(Context& ctx);
    ~MenuScreen() override = default;

    void handleEvent(const sf::Event& event) override;
    void update(f32 dt) override;
    void draw() override;

   private:
    static constexpr std::array<MenuOptions, static_cast<u8>(MenuOptions::Count)> optionOrder = {
        MenuOptions::Start,   //
        MenuOptions::Scores,  //
        MenuOptions::Quit     //
    };

    static const char* optionToString(MenuOptions opt) {
        switch (opt) {
                // clang-format off
            case MenuOptions::Start:  return "Start"  ;
            case MenuOptions::Scores: return "Scores" ;
            case MenuOptions::Quit:   return "Quit"   ;
            default: return "Unknown";
                // clang-format on
        }
    }

    std::vector<sf::Text> texts;
    u8 index = 0;
};
