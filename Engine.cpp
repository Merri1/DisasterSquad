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
	m_gameState = State::MAIN_MENU;
	pathfind = Pathfinding();
	// Create a new window using resolution and framerate const values from Engine.h
	m_window.create(VideoMode(RESOLUTION.x, RESOLUTION.y), "Disaster Squad");
	m_window.setFramerateLimit(FRAMERATE);
	m_mainView = View(sf::FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y));
	m_mainView.zoom(0.5f);
	m_guiView = View(FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y)); // All UI elements, HUD.
	m_mainMenuView = View(FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y));
	m_gameOverView = View(FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y));

	// Call render function to initialise sprite textures and positions
	render();

	graph.generateGraphFromFile(m_levelArray, RESOLUTION.x / TILESIZE, RESOLUTION.y / TILESIZE, 1);
	
	m_elapsedTime = 0;
	// Initialise Responder and Disaster objects
	m_responder1 = new Responder();
	m_responder2 = new Responder();
	lpResponders.push_back(m_responder2);
	lpResponders.push_back(m_responder1);

	m_disaster1 = new Wildfire();
	m_disaster2 = new Wildfire();
	m_disaster3 = new Wildfire();
	m_disaster4 = new Wildfire();

	m_disaster5 = new Tornado();
	m_disaster6 = new Tornado();
	m_disaster7 = new Tornado();
	m_disaster8 = new Tornado();

	// Initialize shops.
	m_ResponderBuy = new Shop(100, 2);
	m_WindTurbineBuy = new Shop(150, 2);
	m_SolarPanelBuy = new Shop(200, 2);
	m_RecyclingCentreBuy = new Shop(250, 2);

	//Add shops to list
	lpShop.push_back(m_ResponderBuy);
	lpShop.push_back(m_WindTurbineBuy);
	lpShop.push_back(m_SolarPanelBuy);
	lpShop.push_back(m_RecyclingCentreBuy);

	// Initialise Renewable sources objetcs
	m_turbine1 = new WindTurbine();
	m_turbine2 = new WindTurbine();
	m_turbine3 = new WindTurbine();

	// Add disaster objects to list of disaster pointers
	lpDisasters.push_back(m_disaster1);
	lpDisasters.push_back(m_disaster2);
	lpDisasters.push_back(m_disaster3);
	lpDisasters.push_back(m_disaster4);

	lpDisasters.push_back(m_disaster5);
	lpDisasters.push_back(m_disaster6);
	lpDisasters.push_back(m_disaster7);
	lpDisasters.push_back(m_disaster8);

	//Pollution - Pollution starts at 1000 and goes up by 1 every second in game at a rate of 0.01
	m_pollutionCurrent = 101;
	m_pollutionRate = 0.5; // Natural pollution rate.

	//Gold - Passive income - 1 gold gets added to the players total every 10 seconds
	m_goldTotal = 0;
	m_goldRate = .1;

	m_gameWin = false;
	m_mainMenu = true;
	m_difficultySelectionMenu = false;
	m_aboutMenu = false;
	m_howToMenu = false;
}

// Seperate run() function out into smaller functions
// Some stuff can go into init, some stuff can stay in run, drawing can be moved to draw() function etc.
void Engine::run()
{
	Clock gameClock;

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

		// Reset the window after evry frame update
		m_window.clear();

		//Every second that passes in game the pollution rate and gold amount gets increased
		if(m_elapsedTime > 1000) 
		{
			m_pollutionCurrent += (m_pollutionRate * m_difficultyMultiplier);
			//cout<<"Pollution total is:" << m_pollutionTotal << endl;

			m_goldTotal += m_goldRate; ///m_difficultyMultiplier;
			m_elapsedTime = 0;
			//cout << "Gold Total: " << m_goldTotal << endl;
		 }
	}
}

void Engine::draw()
{
	if (m_gameState == State::MAIN_MENU)
	{
		m_window.setMouseCursorVisible(true);
		
		m_window.setView(m_mainMenuView);
		m_window.draw(m_menuBackground);
		m_window.draw(m_titleTipShadowText);
		m_window.draw(m_titleTipText);

		if (m_mainMenu)
		{
			m_window.draw(m_playMenuButton);
			m_window.draw(m_howtoMenuButton);
			m_window.draw(m_aboutMenuButton);
			m_window.draw(m_exitMenuButton);
			m_window.draw(m_playMenuText);
			m_window.draw(m_howtoMenuText);
			m_window.draw(m_aboutMenuText);
			m_window.draw(m_exitMenuText);
		}
		else if (m_difficultySelectionMenu)
		{
			m_window.draw(m_easyDifficultyButton);
			m_window.draw(m_mediumDifficultyButton);
			m_window.draw(m_hardDifficultyButton);
			m_window.draw(m_easyDifficultyText);
			m_window.draw(m_hardDifficultyText);
			m_window.draw(m_mediumDifficultyText);
			m_window.draw(m_exitMenuButton);
			m_window.draw(m_backButtonText);
		}
		else if (m_aboutMenu)
		{

		}
		else if (m_howToMenu)
		{

		}

		m_window.display();
	}
	
	if (m_gameState == State::PLAYING)
	{
		m_window.setMouseCursorVisible(false);
		m_window.setView(m_mainView);
		
		m_spriteCrosshair.setPosition(m_window.mapPixelToCoords(Mouse::getPosition(m_window), m_guiView));

		m_window.draw(m_background);

		// For loop to iterate through disaster
		for (list<Disaster*>::const_iterator iter = lpDisasters.begin(); iter != lpDisasters.end(); ++iter)
		{
			// Check if disaster is not spawned yet
			if (!(*iter)->getSpawnStatus())
			{
				if (rand() % 3000/m_difficultyMultiplier == 0)
				{
					// Random 1 in 1000 chance for it to spawn
					std::cout << "Disaster spawned\n";
					(*iter)->spawn(m_levelArray);

					// Reseed random generator
					srand(time(NULL));

					// Exit for loop so only one disaster is spawned per frame update
					break;
				}
			}
			else
			{
				if ((*iter)->isAlive())
				{
					// Else if the disaster is already spawned draw it on map each frame update
					//if disaster health is greater than 0 keep drawing the disaster
					m_window.draw((*iter)->getSprite());
				}
			}
		}

		m_window.draw(m_spriteMainCollisionBox);
		m_window.draw(m_responder1->getSprite());

		if (okayNewResponder == true)
		{
			m_window.draw(m_responder2->getSprite());
		}
		if (okayNewResponder2 == true)
		{
			m_window.draw(m_responder3->getSprite());
		}
		if (okayNewResponder3 == true)
		{
			m_window.draw(m_responder4->getSprite());
		}

		if (okayNewTurbine == true) 
		{
			m_window.draw(m_turbine1->getSprite());
		}

		m_window.draw(m_responder2->getSprite());

		// Switch to second GUI view for UI elements. Seperate to allow for scaling UI.
		m_window.setView(m_guiView);
		m_window.draw(m_spriteGUICollisionBox);
		m_window.draw(m_spriteUIBar);
		m_window.draw(m_spriteMenuBar);

		m_ResponderBuy->setSprite(0);
		m_window.draw(m_ResponderBuy->getSprite());

		m_WindTurbineBuy->setSprite(1);
		m_window.draw(m_WindTurbineBuy->getSprite());

		m_SolarPanelBuy->setSprite(2);
		m_window.draw(m_SolarPanelBuy->getSprite());

		m_RecyclingCentreBuy->setSprite(3);
		m_window.draw(m_RecyclingCentreBuy->getSprite());

		m_window.draw(m_spritePollutionBar);
		m_window.draw(m_spritePollutionTitle);
		m_window.draw(m_spritePollutionLevel);
		m_window.draw(m_spriteWildfireCounter);

		m_window.draw(m_spriteCrosshair);

		// Declare new Font.
		Font ka1Font;
		if (!ka1Font.loadFromFile("graphics/fonts/ka1.ttf"))
		{
			cout << "Error finding custom font.\n";
		}

		// Define income text.
		m_displayIncome.setFont(ka1Font);
		m_displayIncome.setCharacterSize(20);
		m_displayIncome.setFillColor(Color::Black);
		m_displayIncome.setPosition(320, 12);
		stringstream ss;
		ss << "Gold: " << (int)m_goldTotal;
		m_displayIncome.setString(ss.str());

		// Define pollution text.
		m_displayPollution.setFont(ka1Font);
		m_displayPollution.setCharacterSize(20);
		m_displayPollution.setFillColor(Color::Black);
		m_displayPollution.setPosition(660, 12);
		m_displayPollution.setString("Pollution");

		// Using text to display pollution rate for testing purposes only, remove from final game.
		m_displayPollutionRate.setFont(ka1Font);
		m_displayPollutionRate.setCharacterSize(16);
		m_displayPollutionRate.setFillColor(Color::White);
		m_displayPollutionRate.setPosition(950, 12);
		stringstream ss2;
		ss2 << (double)m_pollutionRate;
		m_displayPollutionRate.setString(ss2.str());

		m_window.draw(m_displayIncome);
		m_window.draw(m_displayPollution);
		m_window.draw(m_displayPollutionRate);
		m_window.display();

		// Iterate through alive responders and update them.
		list<Responder*>::const_iterator cycleResponders;
		for (cycleResponders = lpResponders.begin(); cycleResponders != lpResponders.end(); cycleResponders++)
		{
			(*cycleResponders)->update(m_elapsedTime);
		}

		// Update position of pollution level based on the pollution rate.
		if (m_pollutionRate == 0)
		{
			m_spritePollutionLevel.move(0, 0);
		}
		else if (m_pollutionRate > 0 && m_spritePollutionLevel.getPosition().x < 1002)
		{
			m_spritePollutionLevel.move(m_pollutionRate, 0);
		}
		else if (m_pollutionRate < 0 && m_spritePollutionLevel.getPosition().x > 825)
		{
			m_spritePollutionLevel.move(m_pollutionRate, 0);
		}

		if (m_pollutionCurrent <= MIN_POLLUTION)
		{
			m_gameState = State::GAME_OVER;
			m_gameWin = true;
		}
		else if ((int)m_pollutionCurrent >= MAX_POLLUTION)
		{
			m_gameState = State::GAME_OVER;
			m_gameWin = false;
		}
	}
	
	if (m_gameState == State::GAME_OVER)
	{
		std::cout << "Game Over" << endl;
		m_window.clear();
		m_window.setMouseCursorVisible(true);
		m_window.setView(m_gameOverView);
		m_window.draw(m_menuBackground);
		m_window.draw(m_titleTipShadowText);
		m_window.draw(m_titleTipText);
		m_window.draw(m_gameOverText);

		m_window.draw(m_exitMenuButton);
		m_window.draw(m_backButtonText);
		m_window.display();
	}
}

void Engine::eventManager(Event& e)
{
	while (m_window.pollEvent(e))
	{
		m_mousePositionMain = m_window.mapPixelToCoords(Mouse::getPosition(m_window), m_mainView);
		m_mousePositionGUI = m_window.mapPixelToCoords(Mouse::getPosition(m_window), m_guiView);
		m_mousePositionMenu = m_window.mapPixelToCoords(Mouse::getPosition(m_window), m_mainMenuView);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (m_gameState == State::GAME_OVER)
			{
				if (m_exitMenuButton.getGlobalBounds().contains(m_mousePositionMenu))
				{
					init();
				}
			}
			else if (m_gameState == State::MAIN_MENU)
			{
				if (m_mainMenu)
				{
					if (m_playMenuButton.getGlobalBounds().contains(m_mousePositionMenu))
					{
						m_difficultySelectionMenu = true;
						m_mainMenu = false;
					}

					if (m_howtoMenuButton.getGlobalBounds().contains(m_mousePositionMenu))
					{
						// Show game rules
					}

					if (m_exitMenuButton.getGlobalBounds().contains(m_mousePositionMenu))
					{
						m_window.close();
					}
				}
				else if(m_difficultySelectionMenu)
				{
					if (m_easyDifficultyButton.getGlobalBounds().contains(m_mousePositionMenu))
					{
						m_difficultyMultiplier = 1;
						m_gameState = State::PLAYING;
					}

					if (m_mediumDifficultyButton.getGlobalBounds().contains(m_mousePositionMenu))
					{
						m_difficultyMultiplier = 1.5;
						m_gameState = State::PLAYING;
					}

					if (m_hardDifficultyButton.getGlobalBounds().contains(m_mousePositionMenu))
					{
						m_difficultyMultiplier = 2;
						m_gameState = State::PLAYING;
					}

					if (m_exitMenuButton.getGlobalBounds().contains(m_mousePositionMenu))
					{
						m_difficultySelectionMenu = false;
						m_mainMenu = true;
					}
				}
			}
			else if (m_gameState == State::PLAYING)
			{
				m_pathToDestination.clear();

				// If responder is already selected move them to coords of mouse click
				// Iterate through alive responders and check if selected. If so, move them to mouse coordinates.
				list<Responder*>::const_iterator cycleResponders;
				for (cycleResponders = lpResponders.begin(); cycleResponders != lpResponders.end(); cycleResponders++)
				{
					if ((*cycleResponders)->isSelected())
					{
						if (m_levelArray[int(m_mousePositionMain.y / TILESIZE)][int(m_mousePositionMain.x / TILESIZE)] == 0)
						{
							cout << "Yes you can move here mate" << endl;
							cout << "Generating a path for you mate" << endl;

							m_pathToDestination = pathfind.BFS(graph, coordinateToTile((*cycleResponders)->getPosition()), coordinateToTile(m_mousePositionMain));
							(*cycleResponders)->moveTo(m_pathToDestination);
							//(*cycleResponders)->moveTo(m_mousePositionMain.x, m_mousePositionMain.y);
						}
						else
						{
							cout << "Nah you cannot move here mate" << endl;
						}
					}
				}

				// Check if mouse click was within then same coords as a responder
				list<Responder*>::const_iterator cycleResponders2;
				for (cycleResponders2 = lpResponders.begin(); cycleResponders2 != lpResponders.end(); cycleResponders2++)
				{
					if ((*cycleResponders2)->getSprite().getGlobalBounds().contains(m_mousePositionMain))
					{

						// Set responder selected to true when clicked
						(*cycleResponders2)->select(true);
					}
					else
					{
						(*cycleResponders2)->select(false);
					}
				}

				// Check if buy Responder button clicked.
				if (m_ResponderBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI) && m_goldTotal >= (5 * m_difficultyMultiplier))
				{
					// Cycle through to check if any responders are obstructing the spawn.
					list<Responder*>::const_iterator cycleResponders3;
					for (cycleResponders3 = lpResponders.begin(); cycleResponders3 != lpResponders.end(); cycleResponders3++)
					{
						// If responder already there, no spawn.
						if ((*cycleResponders3)->getPositionX() != 408 && (*cycleResponders3)->getPositionY() != 314)
						{
							m_ResponderBuy->select(true);
						}
					}
				}

				// Check if buy wind turbine button clicked.
				if (m_WindTurbineBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI) && m_goldTotal >= (1 * m_difficultyMultiplier))
				{
					/*int x = m_mousePositionMain.x;
					int y = m_mousePositionMain.y;
					cout << y << " y   x " << x << endl;
					int clickedTile = (y / TILESIZE) * (RESOLUTION.x / TILESIZE) + (x / TILESIZE);
					cout << clickedTile << " clickedtile " << endl;*/

					/*if (m_levelArray[y / TILESIZE][x / TILESIZE] == 0) {*/
					m_WindTurbineBuy->select(true);
					m_turbine1->spawn("turbine", 100, 10, 5, 30, 400, 330);
					/*}*/
				}

				// Check if buy solar panel button clicked.
				if (m_SolarPanelBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI) && m_goldTotal >= (1 * m_difficultyMultiplier))
				{
				}

				// Check if buy recycling centre button clicked.
				if (m_RecyclingCentreBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI) && m_goldTotal >= (1 * m_difficultyMultiplier))
				{
				}
			}
		}

		// For handling mouse dragging across the screen to move camera.
		if (Mouse::isButtonPressed(Mouse::Right)) {
			m_mainView.setCenter(m_mousePositionMain);
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
		if (e.type == sf::Event::MouseWheelScrolled)
		{
			// Scroll up (zoom in).
			if (e.mouseWheelScroll.delta > 0 && camZoom < 5)
			{
				m_mainView.zoom(0.8f);

				// Move camera to mouse cursor position per zoom.
				m_mainView.setCenter(m_mousePositionMain);
				camZoom++;
			}
			// Scroll down (zoom out).
			else if (e.mouseWheelScroll.delta < 0 && camZoom > 0)
			{
				m_mainView.zoom(1.2f);
				camZoom--;
			}
			// Zoom out too far, reset screen size (this avoids issue where float value for zoom is fecked up after multiple zooms).
			else if (e.mouseWheelScroll.delta < 0 && camZoom == 0)
			{
				m_mainView.reset(FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y));
			}
		}
	}
}

void Engine::checkSelected() 
{
	// Check if responder shop button is selected.
	if (m_ResponderBuy->isSelected()) {
	
			if (lpResponders.size() > 4) {
				// Do nothing, add error sound.
			}
			else if (lpResponders.size() <= 3) {

				if (lpResponders.size() == 1) {
					m_responder2 = new Responder;
					lpResponders.push_back(m_responder2);
					okayNewResponder = true;
					m_goldTotal -= (5 * m_difficultyMultiplier);
					cout << "A new responder has joined the fight!\n";
					m_ResponderBuy->select(false);
				}
				else if (lpResponders.size() == 2) {
					m_responder3 = new Responder;
					lpResponders.push_back(m_responder3);
					okayNewResponder2 = true;
					m_goldTotal -= (5 * m_difficultyMultiplier);
					cout << "A new responder has joined the fight!\n";
					m_ResponderBuy->select(false);
				}
				else if (lpResponders.size() == 3) {
					m_responder4 = new Responder;
					lpResponders.push_back(m_responder4);
					okayNewResponder3 = true;
					m_goldTotal -= (5 * m_difficultyMultiplier);
					cout << "A new responder has joined the fight!\n";
					m_ResponderBuy->select(false);
				}
			}
		// VERY IMPORTANT: Deselect button after spawn.
	}

	// Check if wind turbine button is selected.
	if (m_WindTurbineBuy->isSelected()) {
		
		lpRenewableSource.push_back(m_turbine1);
		okayNewTurbine = true;
		m_goldTotal -= (1 * m_difficultyMultiplier);
		cout << "A new wind turbine has been created!\n";
		m_WindTurbineBuy->select(false);
	}

	// Check if solar panel button is selected.

	// Check if recycling centre button is selected.
}

void Engine::render()
{
	// Set textures and position for main menu
	m_menuBackground.setTexture(m_textureHolder.GetTexture("graphics/main_menu/menu_background.png"));
	m_menuBackground.setOrigin(0, 0);
	m_menuBackground.setPosition(0, 0);
	m_menuBackground.setScale(0.25, 0.25);

	m_playMenuButton.setTexture(m_textureHolder.GetTexture("graphics/main_menu/button.png"));
	m_playMenuButton.setOrigin(0, 0);
	m_playMenuButton.setPosition(387, 212);

	m_howtoMenuButton.setTexture(m_textureHolder.GetTexture("graphics/main_menu/button.png"));
	m_howtoMenuButton.setOrigin(0, 0);
	m_howtoMenuButton.setPosition(387, 280);

	m_aboutMenuButton.setTexture(m_textureHolder.GetTexture("graphics/main_menu/button.png"));
	m_aboutMenuButton.setOrigin(0, 0);
	m_aboutMenuButton.setPosition(387, 348);

	m_exitMenuButton.setTexture(m_textureHolder.GetTexture("graphics/main_menu/button.png"));
	m_exitMenuButton.setOrigin(0, 0);
	m_exitMenuButton.setPosition(387, 416);

	m_easyDifficultyButton.setTexture(m_textureHolder.GetTexture("graphics/main_menu/button.png"));
	m_easyDifficultyButton.setOrigin(0, 0);
	m_easyDifficultyButton.setPosition(387, 212);

	m_mediumDifficultyButton.setTexture(m_textureHolder.GetTexture("graphics/main_menu/button.png"));
	m_mediumDifficultyButton.setOrigin(0, 0);
	m_mediumDifficultyButton.setPosition(387, 280);

	m_hardDifficultyButton.setTexture(m_textureHolder.GetTexture("graphics/main_menu/button.png"));
	m_hardDifficultyButton.setOrigin(0, 0);
	m_hardDifficultyButton.setPosition(387, 348);

	m_vcrFont.loadFromFile("graphics/fonts/vcr.ttf");
	m_titleTipText.setFont(m_vcrFont);
	m_titleTipText.setCharacterSize(18);
	m_titleTipText.setFillColor(Color::Yellow);
	m_titleTipText.setPosition(750, 140);
	m_titleTipText.setString("GET IT WHILE IT'S HOT");
	m_titleTipText.setStyle(Text::Bold);
	m_titleTipText.setRotation(-15);

	m_titleTipShadowText.setFont(m_vcrFont);
	m_titleTipShadowText.setCharacterSize(18);
	m_titleTipShadowText.setFillColor(Color::Black);
	m_titleTipShadowText.setPosition(749, 142);
	m_titleTipShadowText.setString("GET IT WHILE IT'S HOT");
	m_titleTipShadowText.setStyle(Text::Bold);
	m_titleTipShadowText.setRotation(-15);

	m_playMenuText.setFont(m_vcrFont);
	m_playMenuText.setCharacterSize(28);
	m_playMenuText.setFillColor(Color::White);
	m_playMenuText.setPosition(441, 217);
	m_playMenuText.setString("PLAY GAME");

	m_howtoMenuText.setFont(m_vcrFont);
	m_howtoMenuText.setCharacterSize(28);
	m_howtoMenuText.setFillColor(Color::White);
	m_howtoMenuText.setPosition(425, 285);
	m_howtoMenuText.setString("HOW TO PLAY");

	m_aboutMenuText.setFont(m_vcrFont);
	m_aboutMenuText.setCharacterSize(28);
	m_aboutMenuText.setFillColor(Color::White);
	m_aboutMenuText.setPosition(433, 353);
	m_aboutMenuText.setString("ABOUT GAME");

	m_exitMenuText.setFont(m_vcrFont);
	m_exitMenuText.setCharacterSize(28);
	m_exitMenuText.setFillColor(Color::White);
	m_exitMenuText.setPosition(441, 421);
	m_exitMenuText.setString("EXIT GAME");

	m_easyDifficultyText.setFont(m_vcrFont);
	m_easyDifficultyText.setCharacterSize(28);
	m_easyDifficultyText.setFillColor(Color::White);
	m_easyDifficultyText.setPosition(481, 217);
	m_easyDifficultyText.setString("EASY");

	m_mediumDifficultyText.setFont(m_vcrFont);
	m_mediumDifficultyText.setCharacterSize(28);
	m_mediumDifficultyText.setFillColor(Color::White);
	m_mediumDifficultyText.setPosition(465, 285);
	m_mediumDifficultyText.setString("MEDIUM");

	m_hardDifficultyText.setFont(m_vcrFont);
	m_hardDifficultyText.setCharacterSize(28);
	m_hardDifficultyText.setFillColor(Color::White);
	m_hardDifficultyText.setPosition(481, 353);
	m_hardDifficultyText.setString("HARD");

	m_backButtonText.setFont(m_vcrFont);
	m_backButtonText.setCharacterSize(28);
	m_backButtonText.setFillColor(Color::White);
	m_backButtonText.setPosition(441, 421);
	m_backButtonText.setString("MAIN MENU");

	m_gameOverText.setFont(m_vcrFont);
	m_gameOverText.setCharacterSize(28);
	m_gameOverText.setFillColor(Color::White);
	m_gameOverText.setString("Unfortunately you've let pollution run out of control.\nNow the world is doomed.\nBetter luck next time.\nYour score was: 420");
	m_gameOverText.setOrigin((m_gameOverText.getGlobalBounds().width / 2), (m_gameOverText.getGlobalBounds().height / 2));
	m_gameOverText.setPosition((RESOLUTION.x / 2), 250);

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

	m_spritePollutionBar.setTexture(m_textureHolder.GetTexture("graphics/pollution_bar2.png"));
	m_spritePollutionBar.setPosition(820, 8);

	m_spritePollutionLevel.setTexture(m_textureHolder.GetTexture("graphics/bar_measure.png"));
	m_spritePollutionLevel.setPosition(850, 5);

	m_spriteWildfireCounter.setTexture(m_textureHolder.GetTexture("graphics/wildfire_counter_icon.png"));
	m_spriteWildfireCounter.setPosition(450,4);
}
//Complain about git hub in write up!



void Engine::collisonDetection() //Check if Responder is in a certain range of Disaster object
{
	list<Responder*>::iterator iter2;
	list<Disaster*>::iterator iter;
	iter = lpDisasters.begin();
	iter2 = lpResponders.begin();
	

	for (iter2 = lpResponders.begin(); iter2 != lpResponders.end(); iter2++)
	{
		//cout << "Responder x = " << responder->getPositionX() << " and y = " << responder->getPositionY();
		for (iter = lpDisasters.begin(); iter != lpDisasters.end(); iter++)
		{
			
			if((*iter)->isAlive())
			{
				
				if ((*iter2)->getPositionX() <= (*iter)->getPosition().x + 20
					&& (*iter2)->getPositionX() >= (*iter)->getPosition().x - 20
					&& (*iter2)->getPositionY() <= (*iter)->getPosition().y + 20
					&& (*iter2)->getPositionY() >= (*iter)->getPosition().y - 20)
				{
					(*iter)->updateHealth(1);
				}
			}
		}

	}
}

int Engine::coordinateToTile(Vector2f position)
{
	return (int(position.y / TILESIZE) * (RESOLUTION.x / TILESIZE) + int(position.x / TILESIZE));
}



