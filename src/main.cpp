#include "App.hpp"
#include "Context.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    Context ctx;
    App app(ctx);
    app.run();

    return 0;
}
