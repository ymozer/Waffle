#include "WaffleEngine.hpp"
#include "App.hpp"
#include "Timer.hpp"

#include <iostream>

int main() {
    App app;
    Timer timer;
    timer.start();
    app.Run();
    timer.stop();
    std::cout << "Elapsed time: " << timer.elapsedMilliseconds() << "ms\n";
    return 0;
}
