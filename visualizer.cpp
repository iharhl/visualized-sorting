#include "visualizer.h"

namespace SortEngine 
{

Visualizer::Visualizer(Coord windowSize, const char* windowTitle, const int vectorSize)
	: windowSize(windowSize), vectorSize(vectorSize)
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		throw std::runtime_error("Could not initialize SDL");
	}

	initWindow(windowSize, windowTitle);
	initRenderer();
}

Visualizer::~Visualizer()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void Visualizer::initWindow(Coord windowSize, const char* windowTitle)
{
	window = SDL_CreateWindow(
		windowTitle,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowSize.X,
		windowSize.Y,
		SDL_WINDOW_SHOWN
	);

	if (window == nullptr)
	{
		throw std::runtime_error("Could not initialize SDL window");
	}
}

void Visualizer::initRenderer()
{
	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
	);

	// old -> fix
	SDL_RenderSetScale(renderer, windowSize.X / vectorSize,  windowSize.Y / 100);

	if (renderer == nullptr)
	{
		throw std::runtime_error("Could not initialize SDL renderer");
	}
}

void Visualizer::run()
{
	// Sets render draw color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	if (numbers.empty())
	{
		throw std::runtime_error("Vector is empty. Make sure to call either loadFile() or generateRandom()");
	}

	while (running)
	{
		handleEvent();
		BubbleSortStep();
		draw();
	}
}

void Visualizer::handleEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			running = false;
			printf("User quit input.");
			break;

		default:
			break;
		}
	}
}

void Visualizer::draw()
{
	SDL_RenderClear(renderer);
	drawState();
	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

void Visualizer::drawState()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// SDL_Rect column;

	// old way -> check
    int index = 0;
    for (int i : numbers)
    {
        if (index == red)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // else if (index == blue)
        //     SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, index, 99, index, i);
        index += 1;
    }

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Visualizer::BubbleSortStep()
{
	static unsigned i = 0;
	// static unsigned j = 0;
	static int size = numbers.size();

	// end of simulation
	if (i==numbers.size())
	{
		return;
	}

	red = i;
	// blue = j;

	for (int j = 0; j < size-i-1; ++j)
	{
		++iterations;
		if(numbers[j] > numbers[j+1])
		{
			++swaps;
			std::swap(numbers[j], numbers[j+1]);
		}
	}
	++i;
}


void Visualizer::generateRandomVector()
{
	// Intialize data
    //
    std::random_device rd;
    std::uniform_int_distribution d(1,99);

	// Populate vector
    //
    for (int i = 0; i < vectorSize; ++i)
    {
        numbers.push_back(d(rd));
    }

}

}