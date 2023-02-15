#include "visualizer.h"

namespace SortEngine 
{

Visualizer::Visualizer(Coord windowSize, const char* windowTitle)
	: windowSize(windowSize)
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
	SDL_RenderSetScale(renderer, windowSize.X / 100,  windowSize.Y / 100);

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
		if (!std::is_sorted(numbers.begin(), numbers.end()))
		{
			sortStep();
		}
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
}

void Visualizer::drawState()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// SDL_Rect column;

	// old way -> check
    int index = 0;
    for (int i : numbers)
    {
        if (index == currentI)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (index == currentJ)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, index, 99, index, i);
        index += 1;
    }

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Visualizer::sortStep()
{
	static unsigned i = 0;
	static unsigned j = 0;

	if (j < numbers.size())
	{
		if(numbers[j] < numbers[i])
		{
			std::swap(numbers[j],numbers[i]);
		}
		j += 1;
	} else if (i < numbers.size())
	{
		j = 0;
		i += 1;

		// fix below
		if(numbers[j] < numbers[i])
		{
			std::swap(numbers[j],numbers[i]);
		}
		j += 1;
	}
	currentI = i;
	currentJ = j;
}


void Visualizer::generateRandomVector()
{
	// Intialize data
    //
    std::random_device rd;
    std::uniform_int_distribution d(1,99);

	// Populate vector
    //
    for (int i = 0; i < 100; ++i)
    {
        numbers.push_back(d(rd));
    }

}

}