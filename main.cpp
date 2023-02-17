#include "visualizer.h"

int main(int argc, char *argv[])
{
    // SIZE should not be bigger than width of visualization!
    constexpr size_t SIZE = 1200;

    SortEngine::Visualizer visualization({1200, 800}, "Sorting Visualization", SIZE);
    visualization.generateRandomVector();
    visualization.run();

    return 0;
}