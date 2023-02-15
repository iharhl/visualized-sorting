#include "visualizer.h"

int main(int argc, char *argv[])
{
    SortEngine::Visualizer visualization({ 600, 600 }, "Test");
    visualization.generateRandomVector();
    visualization.run();

    return 0;
}