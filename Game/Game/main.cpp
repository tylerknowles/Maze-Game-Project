#include "GameInterface.h"
#include "Scores.h"



int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	if (TTF_Init() < 0)
		cout << "Error:" << TTF_GetError() << endl; //print error if SDL Video doesn't load

	GameInterface InterfaceObj;

	InterfaceObj.Start();

	return 0;
}