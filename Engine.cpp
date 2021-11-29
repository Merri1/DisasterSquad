#include "Engine.h"
#include <iostream>
using namespace std;
using namespace sf;


Engine::Engine()
{
    // Handles sfml functionality
    // Resolutions, memory loading etc.
}

void Engine::run()
{


	TextureHolder holder;
	
	Vector2f resolution;
	resolution.x = 1024;
	resolution.y = 576;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Disaster Squad");

	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Here is our clock for timing everything
	Clock clock;
	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Responder Responder;

	// The boundaries of the arena
	IntRect area;

	// Create the background
	// Load the texture for our background vertex array
	Texture textureBackground = TextureHolder::GetTexture(
		"graphics/Grasslandsmap.png");
	Sprite background(textureBackground);

	Vector2f MousePosition;
	window.setMouseCursorVisible(true);
	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	window.draw(background);
	window.draw(Responder.getSprite());


	window.display();
	Clock cloc;
	Time elapsedtime;

	while(window.isOpen())
	{
		MousePosition = window.mapPixelToCoords(Mouse::getPosition(window), mainView);
		Time dt = clock.restart();
		elapsedtime += dt;
		Event event;
		spriteCrosshair.setPosition(window.mapPixelToCoords(Mouse::getPosition(), mainView));
		window.draw(Responder.getSprite());
		window.draw(spriteCrosshair);

		while (window.pollEvent(event))
		{


			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{			
				cout << MousePosition.x << "\n"<< MousePosition.y<<"\n";
				//if ((sf::Mouse::getPosition().x <= Responder.getPositionX()+100 && sf::Mouse::getPosition().x >= Responder.getPositionX() -50 ) && (sf::Mouse::getPosition().y <= Responder.getPositionY() +50 && sf::Mouse::getPosition().y >= Responder.getPositionY()-50))
				//if(Responder.getPositionX()<= Mouse::getPosition().x +50 && Responder.getPositionX()>= Mouse::getPosition().x && Responder.getPositionY()<=Mouse::getPosition().y+50 && Responder.getPositionY()>=Mouse::getPosition().y-50)
				if (Responder.getPositionX() <= MousePosition.x + 50 && Responder.getPositionX() >= MousePosition.x && Responder.getPositionY() <= MousePosition.y + 50 && Responder.getPositionY() >= MousePosition.y - 50)

				{
					cout << "Responder has been selected \n";

					Responder.Select(true);
					//Undate reponder Sprite to selected sprite.IE red outline

				}
				if (Responder.isSelected()) {
					Responder.moveTo(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
					cout << "Responder is moving";
				}
				
			}
			Responder.update(elapsedtime);
	
		}
		

	}




}