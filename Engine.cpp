#include "Engine.h"
#include <iostream>
#include<list>
using namespace std;
using namespace sf;

Engine::Engine()
{
    // Handles sfml functionality
    // Resolutions, memory loading etc.
	srand(time(NULL));
}

void Engine::init()
{
	// Create a new window using resolution and framerate const values from Engine.h
	m_window.create(VideoMode(RESOLUTION.x, RESOLUTION.y), "Disaster Squad");
	m_window.setFramerateLimit(FRAMERATE);
	m_mainView = View(sf::FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y));
	m_guiView = View(FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y)); // All UI elements, HUD.
	
	// Call render function to initialise sprite textures and positions
	render();

	m_window.setMouseCursorVisible(false);

	// Initialise Responder and Disaster objects
	responder = new Responder();
	m_disaster1 = new Wildfire();
	m_disaster2 = new Wildfire();
	m_disaster3 = new Wildfire();
	m_disaster4 = new Wildfire();

	//Shop initialised
	m_WindTurbineBuy = new Shop();

	//Add shop to list
	lpShop.push_back(m_WindTurbineBuy);

	// Add disaster objects to list of disaster pointers
	lpDisasters.push_back(m_disaster1);
	lpDisasters.push_back(m_disaster2);
	lpDisasters.push_back(m_disaster3);
	lpDisasters.push_back(m_disaster4);

	//Pollution - Pollution starts at 1000 and goes up by 1 every second in game at a rate of 0.01
	m_pollutionTotal = 1000.0;
	m_pollutionRate = .01;

	//Gold - Passive income - 1 gold gets added to the players total every second
	m_goldTotal = 0;
	m_goldRate = .01;
}

// Seperate run() function out into smaller functions
// Some stuff can go into init, some stuff can stay in run, drawing can be moved to draw() function etc.
void Engine::run()
{
	Clock gameClock;
	m_elapsedTime = 0;

	while(m_window.isOpen())
	{		
		//cout << "TIME" << m_elapsedTime << endl;

		Time dt = gameClock.restart();
		m_elapsedTime += dt.asMilliseconds();
		Event event;
		
		// Draw each object to the screen
		draw();

		// Handle events
		eventManager(event);
		
		// Reset the window after evry frame update
		m_window.clear();

		//Every second that passes in game the pollution rate and gold amount gets increased
		 if(m_elapsedTime > 100) {

			m_pollutionTotal = m_pollutionRate + m_pollutionTotal;
			//cout<<"Pollution total is:" << m_pollutionTotal << endl;

			m_goldTotal = m_goldRate + m_goldTotal;
			//cout << "Gold Total: " << m_goldTotal << endl;
		 }

		 

		 
			 
		
		
	}
}

void Engine::draw()
{
	m_window.setView(m_mainView);
	m_spriteCrosshair.setPosition(m_window.mapPixelToCoords(Mouse::getPosition(m_window), m_guiView));

	m_window.draw(m_background);

	// For loop to iterate through disaster
	for (list<Disaster*>::const_iterator iter = lpDisasters.begin(); iter != lpDisasters.end(); ++iter)
	{
		// Check if disaster is not spawned yet
		if (!(*iter)->getSpawnStatus())
		{
			if (rand() % 1000 == 0)
			{
				// Random 1 in 1000 chance for it to spawn
				std::cout << "Disaster spawned\n";
				(*iter)->spawn();

				// Reseed random generator
				srand(time(NULL));

				// Exit for loop so only one disaster is spawned per frame update
				break;
			}
		}
		else
		{
			// Else if the disaster is already spawned draw it on map each frame update
			m_window.draw((*iter)->getSprite());
		}
	}

	
	m_window.draw(responder->getSprite());
	

	// Switch to second GUI view for UI elements. Seperate to allow for scaling UI.
	m_window.setView(m_guiView);

	m_window.draw(m_spriteUIBar);
	m_window.draw(m_spriteMenuBar);
	m_window.draw(m_WindTurbineBuy->getSprite());
	m_window.draw(m_spriteHeatBar);
	m_window.draw(m_spriteHeatTitle);
	m_window.draw(m_spritePollutionBar);
	m_window.draw(m_spritePollutionTitle);
	m_window.draw(m_spritePollutionLevel);
	m_window.draw(m_spriteHeatLevel);
	m_window.draw(m_spriteMoney);
	m_window.draw(m_spriteResponderBuyButton);
	m_window.draw(m_spriteCrosshair);

	// Declare new Font.
	Font ka1Font;
	if (!ka1Font.loadFromFile("graphics/fonts/ka1.ttf")) {
		cout << "Error finding custom font.\n";
	}

	// Define income text.
	m_displayIncome.setFont(ka1Font);
	m_displayIncome.setCharacterSize(20);
	m_displayIncome.setFillColor(Color::Black);
	m_displayIncome.setPosition(280, 12);
	m_displayIncome.setString(to_string(m_goldTotal));
	m_window.draw(m_displayIncome);

	// Define heat text.
	m_displayHeat.setFont(ka1Font);
	m_displayHeat.setCharacterSize(20);
	m_displayHeat.setFillColor(Color::Black);
	m_displayHeat.setPosition(470, 12);
	m_displayHeat.setString("Heat");

	// Define pollution text.
	m_displayPollution.setFont(ka1Font);
	m_displayPollution.setCharacterSize(20);
	m_displayPollution.setFillColor(Color::Black);
	m_displayPollution.setPosition(710, 12);
	m_displayPollution.setString("Pollution");

	m_window.draw(m_displayIncome);
	m_window.draw(m_displayHeat);
	m_window.draw(m_displayPollution);
	m_window.display();
	responder->update(m_elapsedTime);
}

void Engine::eventManager(Event& e)
{
	while (m_window.pollEvent(e))
	{
		m_mousePosition = m_window.mapPixelToCoords(Mouse::getPosition(m_window), m_mainView);
		// 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

			// If responder is already selected move them to coords of mouse click
			if (responder->isSelected())
			{
				responder->moveTo(m_mousePosition.x, m_mousePosition.y);
			}

			// Check if mouse click was within then same coords as a responder
			//if ((sf::Mouse::getPosition().x <= Responder.getPositionX()+100 && sf::Mouse::getPosition().x >= Responder.getPositionX() -50 ) && (sf::Mouse::getPosition().y <= Responder.getPositionY() +50 && sf::Mouse::getPosition().y >= Responder.getPositionY()-50))
			//if (Responder.getPositionX() <= Mouse::getPosition().x + 50 && Responder.getPositionX() >= Mouse::getPosition().x && Responder.getPositionY() <= Mouse::getPosition().y + 50 && Responder.getPositionY() >= Mouse::getPosition().y - 50)
			if (responder->getPositionX() <= m_mousePosition.x + 10
				&& responder->getPositionX() >= m_mousePosition.x - 10
				&& responder->getPositionY() <= m_mousePosition.y + 10
				&& responder->getPositionY() >= m_mousePosition.y - 10)
			{
				// Set responder selected to true when clicked
				responder->select(true);
			}

			// Check if mouse click was within then same coords as a shop1
			if (m_WindTurbineBuy->isSelected())
			{
				//Can't do anything for now until UI is implemented - DOING UI TODAY
				m_WindTurbineBuy->spawn(m_mousePosition.x, m_mousePosition.y);
				cout << "Spawn turbine " << m_mousePosition.x << " , " << m_mousePosition.y << endl;	
			}

			if (m_WindTurbineBuy->getPositionX() <= m_mousePosition.x + 10
				&& m_WindTurbineBuy->getPositionX() >= m_mousePosition.x - 10
				&& m_WindTurbineBuy->getPositionY() <= m_mousePosition.y + 10
				&& m_WindTurbineBuy->getPositionY() >= m_mousePosition.y - 10)
			{
				// Set shop1 selected to true when clicked
				m_WindTurbineBuy->select(true);
				cout << "Wind turbine buy button is selected";
			}
		}

		// For handling mouse dragging across the screen to move camera.
		if (Mouse::isButtonPressed(Mouse::Right)) {

			m_mainView.setCenter((Vector2f(m_window.mapPixelToCoords(Mouse::getPosition())), Vector2f(m_window.mapPixelToCoords(Mouse::getPosition()))));
		}

		// Close window if titlebar X is clicked
		if (e.type == sf::Event::Closed)
		{
			m_window.close();
		}

		// Close window if Escape key is pressed
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}
		}

		// Scroll in camera if mouse wheel scrolled. Up = +, down = -.
		if (e.type == sf::Event::MouseWheelScrolled) {

			// Scroll up (zoom in).
			if (e.mouseWheelScroll.delta > 0 && camZoom < 5) {
				m_mainView.zoom(0.8f);

				// Move camera to mouse cursor position per zoom.
				m_mainView.move(((Vector2f(m_window.mapPixelToCoords((Mouse::getPosition())) - Vector2f(m_mainView.getCenter()))).x) * 0.9f,
					((Vector2f(m_window.mapPixelToCoords((Mouse::getPosition())) - Vector2f(m_mainView.getCenter()))).y) * 0.9f);
				camZoom++;
			}
			// Scroll down (zoom out).
			else if (e.mouseWheelScroll.delta < 0 && camZoom > 0) {
				m_mainView.zoom(1.2f);
				camZoom--;
			}
			// Zoom out too far, reset screen size (this avoids issue where float value for zoom is fecked up after multiple zooms).
			else if (e.mouseWheelScroll.delta < 0 && camZoom == 0) {

				m_mainView.reset(FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y));
			}
		}
	}
}

void Engine::render()
{
	// Set textures, origins and positions for various game sprites 
	m_background.setTexture(m_textureHolder.GetTexture("graphics/Grasslandsmap.png"));
	m_background.setOrigin(0, 0);
	m_background.setPosition(0, 0);

	m_spriteCrosshair.setTexture(m_textureHolder.GetTexture("graphics/crosshair.png"));
	m_spriteCrosshair.setOrigin(25, 25);

	m_spriteUIBar.setTexture(m_textureHolder.GetTexture("graphics/ui_bar.png"));
	m_spriteUIBar.setOrigin(0, 0);

	m_spriteMenuBar.setTexture(m_textureHolder.GetTexture("graphics/menu_icon.png"));
	m_spriteMenuBar.setOrigin(-6, -2);

	m_spriteResponderBuyButton.setTexture(m_textureHolder.GetTexture("graphics/responder_buy_icon.png"));
	m_spriteResponderBuyButton.setOrigin(-100, -2);

	//m_spriteWindTurbineBuyButton.setTexture(m_textureHolder.GetTexture("graphics/wind_turbine_buy_button.png"));
	//m_spriteWindTurbineBuyButton.setOrigin(-160, -2);

	m_spriteHeatBar.setTexture(m_textureHolder.GetTexture("graphics/heat_bar.png"));
	m_spriteHeatBar.setPosition(550, 8);

	m_spritePollutionBar.setTexture(m_textureHolder.GetTexture("graphics/pollution_bar.png"));
	m_spritePollutionBar.setPosition(870, 8);

	m_spriteMoney.setTexture(m_textureHolder.GetTexture("graphics/money_icon.png"));
	m_spriteMoney.setPosition(240, 8);

	m_spritePollutionLevel.setTexture(m_textureHolder.GetTexture("graphics/bar_measure.png"));
	m_spritePollutionLevel.setPosition(950, 5);

	m_spriteHeatLevel.setTexture(m_textureHolder.GetTexture("graphics/bar_measure.png"));
	m_spriteHeatLevel.setPosition(600, 5);
}
//Complain about git hub in write up!
