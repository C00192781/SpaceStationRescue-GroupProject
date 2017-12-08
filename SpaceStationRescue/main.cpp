/// <summary>
/// Empty Project for SFML[2.4.2]
/// 
/// 
/// @author Peter Lowe
/// @date May 21017
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 


#include "Game.h"


/// <summary>
/// main enrtry point
/// </summary>
/// <returns>zero</returns>
int main()
{
	Game* game = new Game();
	game->run();


	system("PAUSE");
	return 0;
}