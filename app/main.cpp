
#include <Engine/Engine.h>
#include <Engine/Configuration.h>

int main() {
    Engine engine(config::windowWidth, config::windowHeight);
    return engine.run();
}
