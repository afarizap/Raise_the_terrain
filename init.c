#include "demo.h"

float matrix[8][8];

int init_instance(SDL_Instance *instance)
{
	/* Initialie SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n",
			SDL_GetError());
		return (1);
	}
	/*Create a new Window instance */
	instance->window = SDL_CreateWindow("SDL2 \\o/", SDL_WINDOWPOS_CENTERED,
					    SDL_WINDOWPOS_CENTERED,
					    1260, 720, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/*Create a new Renderer instance Linked to the Window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
						SDL_RENDERER_ACCELERATED |
						SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}
void draw_stuff(SDL_Instance instance)
{
	float x1 = 0, x2 = 0, y1 = 0,  y2 = 0, i = 0.7;
	int a = 0, b = 0;
	float w1, w2, w3, w4;

	SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);
	while (x1 < 800)
	{
		b = 0;
		for(y1 = 0, y2 = 100; y1 < 700 ;)
		{
			w1 = i * (x1 - y1);
			w2 = ((1 - i) * (x1 + y1)) - matrix[b][a];
			w3 = i * (x2 - y2);
			w4 = ((1 - i) * (x2 + y2)) - matrix[b + 1][a];
			SDL_RenderDrawLine(instance.renderer
					   , w1 + 500, w2 + 200
					   , w3 + 500, w4 + 200);
			y1 = y2;
			y2 += 100;
			b++;
		}
		x1 += 100;
		x2 = x1;
		a++;
	}
	x1 = 0, x2 = 0, y1 = 0, y2 = 0, a = 0, b = 0;
	while ( y1 < 800)
	{
		a = 0;
		for(x1 = 0, x2 = 100; x1 < 700;)
		{
			w1 = i * (x1 - y1);
			w2 = ((1 - i) * (x1 + y1)) - matrix[b][a];
			w3 = i * (x2 - y2);
			w4 = ((1 - i) * (x2 + y2)) - matrix[b][a + 1];
			SDL_RenderDrawLine(instance.renderer
					   , w1 + 500, w2 + 200
					   , w3 + 500, w4 + 200);
			x1 = x2;
			x2 += 100;
			a++;
		}
		y1 += 100;
		y2 = y1;
		b++;
	}
}
int poll_events()
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			key = event.key;
			/* If 'ESCAPE' is pressed */
			if (key.keysym.scancode == 0x29)
				return (1);
			break;
		}
	}
	return (0);
}
void terrain(char *argv[])
{
	FILE *fp;
	char data[170], *token, *rest = data;
	int i, j, node;

	fp = fopen(argv[1],"r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	else
	{
		for(i = 0;fgets(data, 170, fp) != NULL; i++, rest = data)
		{
			for(j = 0; (token = strtok_r(rest, " ", &rest)); j++)
			{
				node = atoi(token);
				matrix[i][j] = node;
			}
		}
	}
       	fclose(fp);
}
int main(int argc, char *argv[])
{
	SDL_Instance instance;
	(void) argc;

	if (init_instance(&instance) != 0)
		return (1);
	/*
	 * C will always be awesome
	 * This is an infinite loop
	 */
	terrain(argv);
	while ("C is awesome")
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 255, 255);
		SDL_RenderClear(instance.renderer);
		if (poll_events() == 1)
			break;
		/**
		 * Draw some stuff here
		 */
		draw_stuff(instance);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
