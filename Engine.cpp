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
	Texture test = TextureHolder::GetTexture("graphics/tile.png");
	//resolution.x = VideoMode::getDesktopMode().width;
	//resolution.y = VideoMode::getDesktopMode().height;
	
	resolution.x = 1024;
	resolution.y = 576;

	grid.initGrid(virtualGrid, resolution.x, resolution.y);

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Disaster Squad", Style::Resize);

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
	window.setFramerateLimit(60);
	View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	window.setMouseCursorVisible(true);
	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	//Heat bar
	Sprite sprite_heat_bar;
	Texture texture_heat_bar = TextureHolder::GetTexture("graphics/heat_bar.png");
	sprite_heat_bar.setTexture(texture_heat_bar);
	sprite_heat_bar.setPosition(100,20);

	//Heat Title
	Sprite sprite_heat_title;
	Texture texture_heat_title = TextureHolder::GetTexture("graphics/heat_title.png");
	sprite_heat_title.setTexture(texture_heat_title);
	sprite_heat_title.setPosition(30, 30);

	//Pollution Bar
	Sprite sprite_pollution_bar;
	Texture texture_pollution_bar = TextureHolder::GetTexture("graphics/pollution_bar.png");
	sprite_pollution_bar.setTexture(texture_pollution_bar);
	sprite_pollution_bar.setPosition(870, 20);

	//Pollutuion Title
	Sprite sprite_pollution_title;
	Texture texture_pollution_title = TextureHolder::GetTexture("graphics/pollution_title.png");
	sprite_pollution_title.setTexture(texture_pollution_title);
	sprite_pollution_title.setPosition(720, 30);

	//BAR MEASURE THINGY
	Sprite sprite_bar;
	Texture texture_bar = TextureHolder::GetTexture("graphics/bar_measure.png");
	sprite_bar.setTexture(texture_bar);
	sprite_bar.setPosition(140, 17);

	Sprite sprite_bar2;
	Texture texture_bar2 = TextureHolder::GetTexture("graphics/bar_measure.png");
	sprite_bar2.setTexture(texture_bar2);
	sprite_bar2.setPosition(950, 17);




	



	window.draw(background);
	
	
	Clock cloc;
	Time elapsedtime;
	Sprite r = Responder.getSprite();

	while(window.isOpen())
	{

		
		Time dt = clock.restart();
		elapsedtime += dt;
		Event event;
		window.setView(mainView);
		spriteCrosshair.setPosition(window.mapPixelToCoords(Mouse::getPosition(window), mainView));
 

		r.setPosition(window.mapPixelToCoords(Responder.m_position, mainView));
		window.draw(background);
		window.draw(r);
		window.draw(virtualGrid, &test);
		window.draw(spriteCrosshair);
		window.draw(sprite_heat_bar);
		window.draw(sprite_heat_title);
		window.draw(sprite_pollution_bar);
		window.draw(sprite_pollution_title);
		window.draw(sprite_bar);
		window.draw(sprite_bar2);



		

		window.display();

		while(window.pollEvent(event))
		{
			MousePosition = window.mapPixelToCoords(Mouse::getPosition(window), mainView);

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{	
				if(Responder.isSelected()) 
				{
					Responder.moveTo(MousePosition.x, MousePosition.y);
				}		
				
				cout << MousePosition.x << "  Mouse X\n"<< MousePosition.y<<"  Mouse Y\n";
				//if ((sf::Mouse::getPosition().x <= Responder.getPositionX()+100 && sf::Mouse::getPosition().x >= Responder.getPositionX() -50 ) && (sf::Mouse::getPosition().y <= Responder.getPositionY() +50 && sf::Mouse::getPosition().y >= Responder.getPositionY()-50))
				//if(Responder.getPositionX()<= Mouse::getPosition().x +50 && Responder.getPositionX()>= Mouse::getPosition().x && Responder.getPositionY()<=Mouse::getPosition().y+50 && Responder.getPositionY()>=Mouse::getPosition().y-50)
				if(Responder.getPositionX() <= MousePosition.x + 10 && Responder.getPositionX() >= MousePosition.x - 10 && Responder.getPositionY() <= MousePosition.y + 10 && Responder.getPositionY() >= MousePosition.y - 10)
				{
					cout << "Responder has been selected \n";

					Responder.Select(true);
					//Undate reponder Sprite to selected sprite.IE red outline
				}
			}	
		}
		Responder.update(elapsedtime);
		window.clear();
	}
}




































//Complain about git hub in write up!
