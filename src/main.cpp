
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Responder.h"
#include "TextureHolder.h"
#include "Disaster.h"
#include "Engine.h"

using namespace sf;

int main()
{
	Engine engine;

	engine.init();
	engine.run();
}