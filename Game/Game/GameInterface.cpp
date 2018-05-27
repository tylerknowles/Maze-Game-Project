#include "GameInterface.h"
#include "Scores.h"



void GameInterface::Start()
{
	Scores ScoresObj;

	numSprites = ScoresObj.CalculateNumLines("positions.txt"); // calculate the number of lines in the positions file to figure out how many cheese's there will be
	InitiateCollisonTestVectors();
	LoadSpriteTextures();
	SetPositions();
	CreateTitleText();
	RunMenu();

}


void GameInterface::InitiateCollisonTestVectors()
{
	for (int i = 0; i < numSprites; i++)
	{
		hasCollided.push_back(false); // sets all the has collided bools to false
	}
	for (int i = 0; i < numSprites; i++)
	{
		testCollided.push_back(true); // sets all the test collided bools to false
	}
}

SDL_Texture* GameInterface::LoadTexture(char* imageFile, SDL_Renderer *renderer)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *surface = IMG_Load(imageFile); // loads in the image as a surface
	if (surface == NULL)
		cout << "Error: " << SDL_GetError() << endl; // print error if surface wasn't loaded
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface); // convert surface to texture
		if (texture == NULL)
			cout << "Error: " << SDL_GetError() << endl; // print error if the texture wasn't created
	}

	SDL_FreeSurface(surface); // free up the space occupied by the surface
	return texture;
}

void GameInterface::LoadSpriteTextures()
{
	for (int i = 0; i < numSprites; i++)
	{
		spritesVector.push_back(LoadTexture("cheese.png", renderer)); // load in all the cheese's
		//image sourced from: http://clipartall.com/img/clipart-13886.html
	}
	for (int i = 0; i < numMaze; i++)
	{
		mazeVector.push_back(LoadTexture("maze.png", renderer)); // load in all the maze parts
	}
}

void GameInterface::SetPositions()
{
	playerPosition.x = 15; // set the player's starting positions
	playerPosition.y = 70;
	playerPosition.w = 51;
	playerPosition.h = 40;

	int tempx;
	int tempy;
	ifstream file("positions.txt");
	for (int j = 0; j < numSprites; j++)
	{
		file >> tempx;
		file >> tempy;
		spritePositions.push_back({ tempx, tempy, 40, 24 }); // set the positions of the cheese's based on what is written in the positions file
	}
	file.close();


	int tempmazex;
	int tempmazey;
	ifstream mazefile("mazepositions.txt");
	for (int i = 0; i < numHorMaze; i++)
	{
		mazefile >> tempmazex;
		mazefile >> tempmazey;
		mazePositions.push_back({ tempmazex, tempmazey, 120, 20 }); // set the positions of the horizontal maze parts based on what is written in the maze positions file
	}
	for (int i = 0; i < numVertMaze; i++)
	{
		mazefile >> tempmazex;
		mazefile >> tempmazey;
		mazePositions.push_back({ tempmazex, tempmazey, 20, 150 }); // set the positions of the vertical maze parts based on what is written in the maze positions file
	}
	mazefile.close();
}

void GameInterface::CreateTitleText()
{
	textSurface = TTF_RenderText_Solid(font, "Grab the cheese", color); // create the text
	text = SDL_CreateTextureFromSurface(renderer, textSurface); // convert the text surface into a texture
	textRect.x = 300; // set the text's position
	textRect.y = 15;
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_FreeSurface(textSurface);


}

void GameInterface::RunMenu()
{
	bool Menu = true;
	SDL_Event menu; // create an SDL event called menu

	SDL_RenderCopy(renderer, MenuImage, NULL, NULL); // render the menu image to the screen
	SDL_RenderPresent(renderer); // make the renderer present
	Scores ScoresObj; // access the scores class
	while (Menu)
	{

		while (SDL_PollEvent(&menu) != 0)
		{
			if (menu.type == SDL_QUIT)
			{
				DestroyAndFreeMemory(); // if the player clicks the cross, close the game
			}

			else if (menu.type == SDL_KEYDOWN)
			{
				if (menu.key.keysym.sym == SDLK_s)
				{
					ScoresObj.PrintScores(); // if the player presses S, print the scores
				}
				else if (menu.key.keysym.sym == SDLK_SPACE)
				{
					Menu = false; // if the player press SPACE, end the menu screen
				}
			}
		}
	}
	SDL_RenderClear(renderer); // clear the renderer
	Gane(); // start the game
}

void GameInterface::Gane()
{
	SDL_Event movement; // create an SDL event called movement
	bool GameRunning = true;
	while (GameRunning)
	{
		while (SDL_PollEvent(&movement) != 0)
		{
			if (movement.type == SDL_QUIT)
				DestroyAndFreeMemory(); // if the player clicks the cross, close the game
			else if (movement.type == SDL_KEYDOWN)
			{
				switch (movement.key.keysym.sym) {
				case SDLK_RIGHT: case SDLK_d: // if the player presses right or D
					if (playerPosition.x + playerPosition.w >= SCREEN_WIDTH - 10) {} // if the player is within the border
					else
					{
						PlayerImage = RightPlayerImage;
						playerPosition.x += moveSpeed; // move the player to the right
						if (TestMazeCollisions() == false)
						{
							playerPosition.x -= moveSpeed; // rebound if hit a maze
						}
						break;
					}
				case SDLK_LEFT: case SDLK_a: // if the player presses left or A
					if (playerPosition.x <= 10 | TestMazeCollisions() == false) {} // if the player is within the border
					else
					{
						PlayerImage = LeftPlayerImage;
						playerPosition.x -= moveSpeed; // move the player to the left
						if (TestMazeCollisions() == false)
						{
							playerPosition.x += moveSpeed; // rebound if hit a maze
						}
						break;
					}
				case SDLK_DOWN: case SDLK_s: // if the player presses down or S
					if (playerPosition.y + playerPosition.h >= SCREEN_HEIGHT - 55 | TestMazeCollisions() == false) {} // if the player is within the border
					else
					{
						playerPosition.y += moveSpeed; // move the player down
						if (TestMazeCollisions() == false)
						{
							playerPosition.y -= moveSpeed; // rebound if hit a maze
						}
						break;
					}
				case SDLK_UP: case SDLK_w: // if the player presses up or W
					if (playerPosition.y <= 65 | TestMazeCollisions() == false) {} // if the player is within the border
					else
					{
						playerPosition.y -= moveSpeed; // move the player up
						if (TestMazeCollisions() == false)
						{
							playerPosition.y += moveSpeed; // rebound if hit a maze
						}
						break;
					}
				}
			}
		}
		UpdateScreen();
		int numCollided = 0;
		for (int i = 0; i < numSprites; i++)
		{
			if (hasCollided[i] == true)
			{
				numCollided += 1; // store how many cheese's have been collected
			}

		}
		if (numCollided == numSprites)
		{
			GameRunning = false; // end the game if all cheese's collected
		}
	}
	EndScreen();
}


void GameInterface::UpdateScreen()

{

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, GameBackgroundImage, NULL, NULL); // display the background image


	for (int i = 0; i < numMaze; i++)
	{
		SDL_RenderCopy(renderer, mazeVector[i], NULL, &mazePositions[i]); // display the maze parts
	}



	SDL_RenderCopy(renderer, PlayerImage, NULL, &playerPosition); // display the player
	for (int i = 0; i < numSprites; i++)
	{
		if (hasCollided[i] == false) {
			SDL_RenderCopy(renderer, spritesVector[i], NULL, &spritePositions[i]); // display the cheese's if they haven't been collected
		}
	}
	SDL_RenderCopy(renderer, text, NULL, &textRect); // display the title text
	SDL_RenderPresent(renderer);
	for (int i = 0; i < numSprites; i++)
	{
		testCollided[i] = TestCollision(playerPosition, spritePositions[i]); // check if the player has collected any cheese's
		if (testCollided[i] == false) {
			hasCollided[i] = true;
		}
	}

}

bool GameInterface::TestCollision(SDL_Rect tex1, SDL_Rect tex2)
{
	if (((tex1.x >= tex2.x && tex1.x <= tex2.x + tex2.w) || ((tex1.x + tex1.w <= tex2.x + tex2.w) && (tex1.x + tex1.w >= tex2.x))) &&
		(((tex1.y <= tex2.y + tex2.h) && (tex1.y >= tex2.y)) || ((tex1.y + tex1.h >= tex2.y) && (tex1.y + tex1.h <= tex2.y + tex2.h)))) // check all the possibilities of 2 textures touching
	{
		return false;
	}
	else {
		return true;
	}
}

bool GameInterface::TestMazeCollisions()
{
	bool tempMazeCollide;
	bool anyCollision = true;
	for (int i = 0; i < numMaze; i++)
	{
		tempMazeCollide = TestCollision(playerPosition, mazePositions[i]); // check if the player is touching the maze
		if (tempMazeCollide == false)
		{
			anyCollision = false;
		}
	}
	return anyCollision;
}

void GameInterface::EndScreen()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, EndScreenImage, NULL, NULL); // display the end screen image
	SDL_RenderPresent(renderer);
	Scores ScoresObject;
	ScoresObject.WriteScores();
	DestroyAndFreeMemory();
}

void GameInterface::DestroyAndFreeMemory() // free up memory occupied by pointers. destroy textures and surfaces. quit SDL, image and ttf
{
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyTexture(PlayerImage);
	PlayerImage = nullptr;
	SDL_DestroyTexture(RightPlayerImage);
	RightPlayerImage = nullptr;
	SDL_DestroyTexture(LeftPlayerImage);
	LeftPlayerImage = nullptr;
	SDL_DestroyTexture(MenuImage);
	MenuImage = nullptr;
	SDL_DestroyTexture(GameBackgroundImage);
	GameBackgroundImage = nullptr;
	SDL_DestroyTexture(EndScreenImage);
	EndScreenImage = nullptr;
	font = nullptr;
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	SDL_DestroyTexture(text);
	text = nullptr;
	for (int i = 0; i < numSprites; i++)
	{
		SDL_DestroyTexture(spritesVector[i]);
		spritesVector[i] = nullptr;
	}
	for (int i = 0; i < numMaze; i++)
	{
		SDL_DestroyTexture(mazeVector[i]);
		mazeVector[i] = nullptr;
	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}