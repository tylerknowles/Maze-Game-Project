#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;
const int numMaze = 15;
const int numVertMaze = 8;
const int numHorMaze = 7;
class GameInterface
{
private:


	SDL_Window *window = SDL_CreateWindow("Grab the Cheese", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN); //creates the SDL window
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //creates the SDL renderer

	SDL_Texture *PlayerImage = LoadTexture("mouseright.png", renderer); //creates a texture to store the image for the player
	//image sourced from https://clipartfest.com/download/70bd84e7592075681b459d566456dcdc2616bfa3.html
	SDL_Texture *RightPlayerImage = LoadTexture("mouseright.png", renderer); //creates a texture to store the image for the player facing right
	SDL_Texture *LeftPlayerImage = LoadTexture("mouseleft.png", renderer); //creates a texture to store the image for the player facing left
	SDL_Texture *MenuImage = LoadTexture("text.png", renderer); //loads the menu image in as a texture
	SDL_Texture *GameBackgroundImage = LoadTexture("background.png", renderer); //loads the game background in as a texture
	SDL_Texture *EndScreenImage = LoadTexture("endscreen.png", renderer); //loads the end screen image in as a texture

	TTF_Font *font = TTF_OpenFont("font.otf", 40); //loads in the font to be used in the game
	//font sourced from https://www.fontsquirrel.com/fonts/bebas-neue?q%5Bterm%5D=bebas&q%5Bsearch_check%5D=Y
	SDL_Color color = { 225, 225, 0, 255 }; //sets the font colour
	SDL_Surface *textSurface;
	SDL_Texture *text;
	SDL_Rect textRect;//creates a rect to set the text's position and size

	int imgFlags = IMG_INIT_PNG;//enables png images to be used
	int moveSpeed = 3;//how fast the player will move
	vector<SDL_Texture*> spritesVector;//creates a vector to store the sprites
	int numSprites;
	vector<SDL_Rect> spritePositions;//creates a vector to store the sprite's positions

	vector<SDL_Texture*> mazeVector;//creates a vector to store the maze parts
	vector<SDL_Rect> mazePositions;//creates a vector to store the maze part's positions




	SDL_Rect playerPosition;//creates a rect to set the player's position



	vector<bool> hasCollided;//creates a vector to store whether the each cheese has ever been touched by the player
	vector<bool> testCollided;//creates a vector to store whether each cheese is currently touching the player

public:

	void Start();

	void InitiateCollisonTestVectors();

	SDL_Texture* LoadTexture(char* file, SDL_Renderer *renderer);

	void LoadSpriteTextures();

	void SetPositions();

	void CreateTitleText();

	void RunMenu();

	void Gane();

	void UpdateScreen();

	bool TestCollision(SDL_Rect tex1, SDL_Rect tex2);

	bool TestMazeCollisions();

	void EndScreen();

	void DestroyAndFreeMemory();
};

