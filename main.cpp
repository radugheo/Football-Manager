#include "headers/GameEngine.h"

int main() {
    auto& engine = GameEngine::getGameEngine();
    engine.run();
    return 0;
}
