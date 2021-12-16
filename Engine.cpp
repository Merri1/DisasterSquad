#include "Engine.h"
#include <iostream>
#include<list>
#include<sstream>

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
	pathfind = Pathfinding();
	// Create a new window using resolution and framerate const values from Engine.h
	m_window.create(VideoMode(RESOLUTION.x, RESOLUTION.y), "Disaster Squad");
	m_window.setFramerateLimit(FRAMERATE);
	m_mainView = View(sf::FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y));
	m_guiView = View(FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y)); // All UI elements, HUD.
	
	// Call render function to initialise sprite textures and positions
	render();

	m_window.setMouseCursorVisible(false);

	graph.generateGraphFromFile(RESOLUTION.x/TILESIZE, RESOLUTION.y/TILESIZE, 1);
	vector<int> path = pathfind.BFS(graph, 60, 63);
	for (int n : path)
	{
		cout << n << "-";
	}

	// Initialise Responder and Disaster objects
	m_responder1 = new Responder();
	responder = new Responder();
	lpResponders.push_back(responder);

	m_disaster1 = new Wildfire();
	m_disaster2 = new Wildfire();
	m_disaster3 = new Wildfire();
	m_disaster4 = new Wildfire();

	//Shop initialised
	m_ResponderBuy = new Shop(100, 2);
	m_WindTurbineBuy = new Shop(150, 2);

	//Add responders (add only one to begin with).
	lpResponders.push_back(m_responder1);

	//Add shops to list
	lpShop.push_back(m_ResponderBuy);
	lpShop.push_back(m_WindTurbineBuy);
	//Shop object initialised
	//m_shop1 = new Shop();

	//Initialise Renewable sources objetcs
	m_renewableSource1 = new WindTurbine();

	//Add source to list
	lpRenew.push_back(m_renewableSource1);

	//Add shop to list
	//lpShop.push_back(m_shop1);

	// Add disaster objects to list of disaster pointers
	lpDisasters.push_back(m_disaster1);
	lpDisasters.push_back(m_disaster2);
	lpDisasters.push_back(m_disaster3);
	lpDisasters.push_back(m_disaster4);

	//Pollution - Pollution starts at 1000 and goes up by 1 every second in game at a rate of 0.01
	m_pollutionTotal = 100.0;
	m_pollutionRate = .001;

	//Gold - Passive income - 1 gold gets added to the players total every second
	m_goldTotal = 0;
	m_goldRate = .01;

	// Power - Can only be increase / decreased by producing new buildings.
	m_powerTotal = 0;
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
		checkSelected();

		collisonDetection();
		//clean();

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

	m_window.draw(m_spriteMainCollisionBox);
	m_window.draw(m_responder1->getSprite());
	if (okayNewResponder == true) {
		m_window.draw(m_responder2->getSprite());
	}
	//m_window.draw(m_shop1->getSprite());
	m_window.draw(m_renewableSource1->getSprite());
	m_window.draw(responder->getSprite());
	m_window.draw(m_spriteCrosshair);

	// Switch to second GUI view for UI elements. Seperate to allow for scaling UI.
	m_window.setView(m_guiView);
	m_window.draw(m_spriteGUICollisionBox);
	m_window.draw(m_spriteUIBar);
	m_window.draw(m_spriteMenuBar);

	//m_ResponderBuy->setSprite(0);
	//m_window.draw(m_ResponderBuy->getSprite());

	//m_WindTurbineBuy->setSprite(1);
	//m_window.draw(m_WindTurbineBuy->getSprite());

	m_window.draw(m_spritePower);
	m_window.draw(m_spriteHeatBar);
	m_window.draw(m_spriteHeatTitle);
	m_window.draw(m_spritePollutionBar);
	m_window.draw(m_spritePollutionTitle);
	m_window.draw(m_spritePollutionLevel);
	m_window.draw(m_spriteHeatLevel);
	m_window.draw(m_spriteCrosshair);

	// Declare new Font.
	Font ka1Font;
	if (!ka1Font.loadFromFile("graphics/fonts/ka1.ttf")) 
	{
		cout << "Error finding custom font.\n";
	}

	// Define power text.
	m_displayPower.setFont(ka1Font);
	m_displayPower.setCharacterSize(20);
	m_displayPower.setFillColor(Color::Black);
	m_displayPower.setPosition(260, 12);
	m_displayPower.setString(to_string(m_powerTotal));
	m_window.draw(m_displayPower);

	// Define income text.
	m_displayIncome.setFont(ka1Font);
	m_displayIncome.setCharacterSize(20);
	m_displayIncome.setFillColor(Color::Black);
	m_displayIncome.setPosition(320, 12);
	stringstream ss;
	ss << "G: " << m_goldTotal;
	m_displayIncome.setString(ss.str());
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

	m_window.draw(m_displayPower);
	m_window.draw(m_displayIncome);
	m_window.draw(m_displayHeat);
	m_window.draw(m_displayPollution);
	m_window.display();

	// Iterate through alive responders and update them.
	list<Responder*>::const_iterator cycleResponders;
	for (cycleResponders = lpResponders.begin(); cycleResponders != lpResponders.end(); cycleResponders++) {
		(*cycleResponders)->update(m_elapsedTime);
	}
}

void Engine::eventManager(Event& e)
{
	while (m_window.pollEvent(e))
	{
		m_mousePositionMain = m_window.mapPixelToCoords(Mouse::getPosition(m_window), m_mainView);
		m_mousePositionGUI = m_window.mapPixelToCoords(Mouse::getPosition(m_window), m_guiView);
		 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// If responder is already selected move them to coords of mouse click
			// Iterate through alive responders and check if selected. If so, move them to mouse coordinates.
			list<Responder*>::const_iterator cycleResponders;
			for (cycleResponders = lpResponders.begin(); cycleResponders != lpResponders.end(); cycleResponders++) {
				if ((*cycleResponders)->isSelected())
				{
					(*cycleResponders)->moveTo(m_mousePositionMain.x, m_mousePositionMain.y);
				}
			}

			// Check if mouse click was within then same coords as a responder
			list<Responder*>::const_iterator cycleResponders2;
			for (cycleResponders2 = lpResponders.begin(); cycleResponders2 != lpResponders.end(); cycleResponders2++) {
				if ((*cycleResponders2)->getPositionX() <= m_mousePositionMain.x + 10
					&& (*cycleResponders2)->getPositionX() >= m_mousePositionMain.x - 10
					&& (*cycleResponders2)->getPositionY() <= m_mousePositionMain.y + 10
					&& (*cycleResponders2)->getPositionY() >= m_mousePositionMain.y - 10)
				{
					// Set responder selected to true when clicked
					(*cycleResponders2)->select(true);
				}
			}
			// Check if Responder buy button has been clicked.
			if (m_ResponderBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI) && m_goldTotal >= 5) {
				m_ResponderBuy->select(true);

				// Check if mouse click was within then same coords as turbine
				/*
				if (m_renewableSource1->isSelected())
				{
					m_renewableSource1->spawn(m_mousePosition.x, m_mousePosition.y);
					cout << "Spawn turbine " << m_mousePosition.x << " , " << m_mousePosition.y << endl;

					m_renewableSource1->getSpritepos(m_mousePosition.x, m_mousePosition.y);
					m_renewableSource1-> select(false);

				}
				*/

				// Check if wind turbine buy button has been clicked.
				if (m_WindTurbineBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI) && m_goldTotal >= 5) {
					m_WindTurbineBuy->select(true);
					cout << "Wind turbine buy button is selected!\n";


					if (m_renewableSource1->getPositionX() <= m_mousePositionMain.x + 10
						&& m_renewableSource1->getPositionX() >= m_mousePositionMain.x - 10
						&& m_renewableSource1->getPositionY() <= m_mousePositionMain.y + 10
						&& m_renewableSource1->getPositionY() >= m_mousePositionMain.y - 10)
					{
						// Set m_renewableSource1 selected to true when clicked
						m_renewableSource1->select(true);
						cout << "m_renewableSource1 is selected";
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

				// Check for Keypress.
				if (e.type == sf::Event::KeyPressed)
				{
					// Close window if Escape key is pressed
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
	}
}

void Engine::checkSelected() 
{

	// Check if responder shop button is selected.
	if (m_ResponderBuy->isSelected()) {
		cout << "A new responder has joined the fight!\n";
		m_responder2 = new Responder;
		lpResponders.push_back(m_responder2);
		okayNewResponder = true;
		m_goldTotal -= 5;
		// VERY IMPORTANT: Deselect button after spawn.
		m_ResponderBuy->select(false);
	}

	// Check if wind turbine button is selected.
	if (m_WindTurbineBuy->isSelected()) {
		cout << "A new wind turbine has been created!\n";
		m_goldTotal -= 5;
		m_WindTurbineBuy->select(false);
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

	m_spritePower.setTexture(m_textureHolder.GetTexture("graphics/power_icon.png"));
	m_spritePower.setPosition(220, 2);

	m_spriteHeatBar.setTexture(m_textureHolder.GetTexture("graphics/heat_bar.png"));
	m_spriteHeatBar.setPosition(550, 8);

	m_spritePollutionBar.setTexture(m_textureHolder.GetTexture("graphics/pollution_bar.png"));
	m_spritePollutionBar.setPosition(870, 8);

	m_spritePollutionLevel.setTexture(m_textureHolder.GetTexture("graphics/bar_measure.png"));
	m_spritePollutionLevel.setPosition(950, 5);

	m_spriteHeatLevel.setTexture(m_textureHolder.GetTexture("graphics/bar_measure.png"));
	m_spriteHeatLevel.setPosition(600, 5);
}
//Complain about git hub in write up!



void Engine::collisonDetection() //Check if Responder is in a certain range of Disaster object
{
	list<Disaster*>::iterator iter1;
	iter1 = lpDisasters.begin();
	

	for (iter1 = lpDisasters.begin(); iter1 != lpDisasters.end();iter1++)
	{
		//cout << "Responder x = " << responder->getPositionX() << " and y = " << responder->getPositionY();

		if (responder->getPositionX() <= (*iter1)->getPosition().x + 10
			&& responder->getPositionX() >= (*iter1)->getPosition().x - 10
			&& responder->getPositionY() <= (*iter1)->getPosition().y + 10
			&& responder->getPositionY() >= (*iter1)->getPosition().y - 10)
		{
			
				//cout << "Its working";
				Battle();
			
		 }
		 

	}
}


void Engine::Battle()
{
	cout << "Battle Start\n";
	list<Disaster*>::iterator iter;
	iter = lpDisasters.begin();

	cout << "Disaster Health = " << (*iter)->getHealth() << "\n";

	int m_damageAmount = responder->getAttack(); 
	(*iter)->updateHealth(m_damageAmount);

	if ((*iter)->getHealth() <= 0)
	{
		cout << "Disaster Dead";
		//clean();
		
	}

	
	
}


void Engine::clean()
{
	list<Disaster*>::iterator iter;
	for (iter = lpDisasters.begin(); iter != lpDisasters.end(); ++iter)
	{
		if (!(*iter)->isAlive())
		{
			lpDisasters.erase(iter--);
			cout << "Disaster Removed";

		}

	}


}
