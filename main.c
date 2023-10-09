/*
 * main.c
 *
 *  Created on: 8 Oct 2023
 *      Author: been
 *
 *      This is the broken version of the animation but it is not the original
 *      the original verison is long gone and i recreated the error i was getting but without the infinite while loop which caused a crash which was annoying
 *      for screens smaller than 1440p you must change the screen dimentions, size is the size of the app and res is the resolution at which the animation is being rendered
 *      having the resolution be larger than the size will likely cause errors but i havent tested it
 *      having the resolution be really small will make the cube (SDL_Rect object named ball) appear larger if it is not adjusted
 */


#include <stdio.h>
#include <SDL2/SDL.h>

int sizeX = 1080;
int sizeY = 1440;
int resX = 1080;
int resY = 1440;

int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Failed to initialise SDL.\nQuitting in 5 seconds...\n"); SDL_Delay(5); return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sizeX, sizeY, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init SDL_Window", SDL_GetError(), NULL); return -2; }

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init SDL_Renderer", SDL_GetError(), NULL); SDL_Quit(); return -3; }

	SDL_Surface* bmp_test = SDL_LoadBMP("img/ananas.bmp");
	if (bmp_test == NULL)
	{ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init SDL_Surface", SDL_GetError(), NULL); SDL_Quit(); return -4; }

	SDL_Texture* texture_test = SDL_CreateTextureFromSurface(renderer, bmp_test);
	if (texture_test == NULL)
	{ SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init SDL_Texture", SDL_GetError(), NULL); SDL_Quit(); return -5; }


	SDL_RenderSetScale(renderer, sizeX/resX, sizeY/resY);

	SDL_RenderCopy(renderer, texture_test, NULL, NULL);

	SDL_RenderPresent(renderer);



	int quit = 0;
	int size = 108;
	SDL_Rect ball = {1080/2 - size/2, 1080/2 - size/2, size, size};

	unsigned char r = 0;
	unsigned char g = 255;
	unsigned char b = 255;
	unsigned char move = 1;
	unsigned char cSpeed = 3;
	double speed = 5;
	char dy = -1;
	char dx = 1;
	while (!quit)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				break;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit++;
					break;
				}
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					printf("----------------- mouse1 -----------------------------------------\n");

				}
			}
	 	}

		//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		//SDL_RenderClear(renderer);

		switch (move)
		{
		case 1:
			if (g > cSpeed)
				{g -= cSpeed; r += cSpeed;}
			else
				move = 2;
			break;
		case 2:
			if (b > cSpeed)
				{b -= cSpeed; g += cSpeed;}
			else
				move = 3;
			break;
		case 3:
			if (r > cSpeed)
				{r -= cSpeed; b += cSpeed;}
			else
				move = 1;
			break;
		}


		ball.x += (int)dx*speed;
		ball.y += (int)dy*speed;

		if (ball.x + ball.w >= resX || ball.x <= 0)
		{
			speed = speed * 1.05;
			dx = 0 - dx;
		}
		if	(ball.y + ball.h >= resY || ball.y <= 0)
		{
			speed = speed * 1.05;
			dy = 0 - dy;
		}

		if (speed >= resX || speed >= resY)
			speed = 100;

		int crash = 0;
		while (ball.x + ball.w >= resX || ball.x <= 0)
		{
			ball.x += (int)(dx*speed);
			crash++;
			if (crash >10000)
				return -100;
		}
		while (ball.y + ball.h >= resY || ball.y <= 0)
		{
			ball.y += (int)dy*speed;
			crash++;
			if (crash >10000)
				return -100;
		}
		SDL_Rect ballout = {ball.x-2, ball.y-2, ball.w+4, ball.h+4};
		SDL_SetRenderDrawColor(renderer, 75, 75, 75, 255);
		SDL_RenderFillRect(renderer, &ballout);

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderFillRect(renderer, &ball);

		SDL_RenderPresent(renderer);


	}


	printf("closing program\n");
	SDL_Quit();
	return 0;
}
