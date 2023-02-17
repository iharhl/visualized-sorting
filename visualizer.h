#ifndef VISUALIZER_H
#define VISUALIZER_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include "types.h"

namespace SortEngine
{

class Visualizer
{

    public:

        Visualizer(Coord windowSize, const char* windowTitle, const int vectorSize);
        ~Visualizer();
        
        void run();
        void generateRandomVector();

    private:

        void initWindow(Coord windowSize, const char* windowTitle);
        void initRenderer();

        const Coord windowSize;
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        void handleEvent();
        void draw();
        void drawState();
        void BubbleSortStep();

        const int vectorSize;
        std::vector<int> numbers = { };
		int columnWidth = 0;
		int maxValue = 0;
		bool running = true;

        // for future
        int red = 0;
        // int blue = 0;
        int iterations = 0;
        int swaps = 0;
};


}

#endif