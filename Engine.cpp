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
	m_cursorStyle = 0;
	// Create a new window using resolution and framerate const values from Engine.h
	m_window.create(VideoMode(RESOLUTION.x, RESOLUTION.y), "Disaster Squad");
	m_window.setFramerateLimit(FRAMERATE);
	m_mainView = View(sf::FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y));
	m_mainView.zoom(0.5f);
	m_guiView = View(FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y)); // All UI elements, HUD.
	m_mainMenuView = View(FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y));
	m_gameOverView = View(FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y));
	m_gameVictoryView = View(FloatRect(0, 0, RESOLUTION.x, RESOLUTION.y));

	//Player Score
	m_score = 100;


	// Call render function to initialise sprite textures and positions
	render();

	graph.generateGraphFromFile(m_levelArray, RESOLUTION.x / TILESIZE, RESOLUTION.y / TILESIZE, 1);
	
	// Initialize timers.
	m_totalGameTime = 0;
	m_elapsedTime = 0;
	m_spriteTime = 0;
	m_clickDelay = 0;
	m_clickDelayFlag = false;

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

	// Initialise Renewable sources objects.
	// Wind turbines (MAX 3).
	m_turbine1 = new RenewableSource("turbine");
	m_turbine2 = new RenewableSource("turbine");
	m_turbine3 = new RenewableSource("turbine");

	// Solar panels (MAX 3).
	m_solar1 = new RenewableSource("solar");
	m_solar2 = new RenewableSource("solar");
	m_solar3 = new RenewableSource("solar");

	// Recycling centres (MAX 2).
	m_recycling1 = new RenewableSource("recycling");
	m_recycling2 = new RenewableSource("recycling");

	// Add disaster objects to list of disaster pointers
	lpDisasters.push_back(m_disaster1);
	lpDisasters.push_back(m_disaster2);
	lpDisasters.push_back(m_disaster3);
	lpDisasters.push_back(m_disaster4);

	lpDisasters.push_back(m_disaster5);
	lpDisasters.push_back(m_disaster6);
	lpDisasters.push_back(m_disaster7);
	lpDisasters.push_back(m_disaster8);

	//Pollution - Pollution starts at 1000 and goes up by 1 every second in game at a rate of 0.05.
	m_pollutionCurrent = 100;
	m_pollutionRate = 0.03;
	
	//Gold - Passive income - 1 gold gets added to the players total every 10 seconds
	m_goldTotal = 10;
	m_goldRate = .1;

	// Extra booleans for game states.
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
	m_sound.gameMusic();

	while(m_window.isOpen())
	{		
		//cout << "TIME" << m_elapsedTime << endl;
		Time dt = gameClock.restart();
		m_elapsedTime += dt.asMilliseconds();
		m_totalGameTime += m_elapsedTime;

		// Count up milliseconds for time so sprites can update at a reasonable rate.
		m_spriteTime += dt.asMilliseconds();
		if (m_spriteTime >= 500)
		{
			m_spriteTime = 0;
		}

		// Count up milliseconds for time so there is a delay between clicks.
		m_clickDelay += dt.asMilliseconds();
		if (m_clickDelay <= 250)
		{
			m_clickDelayFlag = false;
		}
		else if (m_clickDelay > 250)
		{
			m_clickDelayFlag = true;
		}

		Event event;
		
		// Draw each object to the screen
		draw();

		// Handle events
		eventManager(event);
		checkSelected();
		updateCursor();
		collisionDetection();

		// Reset the window after evry frame update
		m_window.clear();

		//Every second that passes in game the pollution rate and gold amount gets increased
		if(m_elapsedTime > 1000) 
		{
			m_pollutionCurrent += m_pollutionRate * m_difficultyMultiplier;
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
		else if (m_howToMenu)
		{
			m_window.draw(m_howToPlayText);
			m_window.draw(m_exitMenuButton);
			m_window.draw(m_backButtonText);
		}
		else if (m_aboutMenu)
		{
			m_window.draw(m_aboutGameText);
			m_window.draw(m_exitMenuButton);
			m_window.draw(m_backButtonText);
		}

		m_window.display();
	}
	
	if (m_gameState == State::PLAYING)
	{
		m_window.setMouseCursorVisible(false);
		m_window.setView(m_mainView);
		
		m_spriteCursor.setPosition(m_window.mapPixelToCoords(Mouse::getPosition(m_window), m_guiView));

		m_window.draw(m_background);

		// For loop to iterate through disaster
		for (list<Disaster*>::const_iterator iter = lpDisasters.begin(); iter != lpDisasters.end(); ++iter)
		{
			// Check if disaster is not spawned yet
			if (!(*iter)->getSpawnStatus())
			{
				if (rand() % 3000/m_difficultyMultiplier < 1)
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
				if ((*iter)->getHealth() < 200)
				{
					m_levelArray[(int)(*iter)->getPosition().y / 16][(int)(*iter)->getPosition().x / 16] = 0;
					(*iter)->destroyDisaster();
					m_goldTotal = m_goldTotal + 5;
					m_score = m_score + 10;
					cout << m_score << endl;
				}
				else if ((*iter)->isAlive())
				{
					// Else if the disaster is already spawned draw it on map each frame update
					//if disaster health is greater than 0 keep drawing the disaster
					m_window.draw((*iter)->getSprite(m_spriteTime));
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

		m_window.draw(m_responder2->getSprite());

		// Iterate through all active and draw them.
		list<RenewableSource*>::const_iterator cycleRenewable;
		for (cycleRenewable = lpRenewableSource.begin(); cycleRenewable != lpRenewableSource.end(); cycleRenewable++) {

			m_window.draw((*cycleRenewable)->getSprite());
			(*cycleRenewable)->update(m_elapsedTime, m_spriteTime);
		}


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
		
		m_window.draw(m_spriteCursor);

		// Declare new Font.
		Font ka1Font;
		if (!ka1Font.loadFromFile("graphics/fonts/ka1.ttf"))
		{
			cout << "Error finding custom font.\n";
		}

		// Declare Calibri Light font.
		Font calibriLight;
		if (!calibriLight.loadFromFile("graphics/fonts/calibriLight.ttf"))
		{
			cout << "Error finding custom font Calibri Light";
		}

		if (m_mousePositionGUI.y < (RESOLUTION.y / 13) && m_ResponderBuy->isSelected() == false && m_SolarPanelBuy->isSelected() == false && m_WindTurbineBuy->isSelected() == false && m_RecyclingCentreBuy->isSelected() == false) {
			m_cursorStyle = 1;
		}
		else if (m_mousePositionGUI.y > (RESOLUTION.y / 13) && m_ResponderBuy->isSelected() == false && m_SolarPanelBuy->isSelected() == false && m_WindTurbineBuy->isSelected() == false && m_RecyclingCentreBuy->isSelected() == false) {
			m_cursorStyle = 0;
		}

		// Tooltips by hovering over buttons and icons.
		// Hover over responder buy button.
		if (m_ResponderBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI))
		{
			m_displayTooltip.setFont(calibriLight);
			m_displayTooltip.setCharacterSize(14);
			m_displayTooltip.setFillColor(Color::Black);
			m_displayTooltip.setPosition(110, 52);
			stringstream ssResponder;
			ssResponder << "Purchase a new Responder.\nResponders can fight disasters.\nCost: " << int(8 * m_difficultyMultiplier) << "        Max: 4";
			m_displayTooltip.setString(ssResponder.str());

			m_window.draw(m_spriteUiTooltip);
			m_window.draw(m_displayTooltip);
		}
		// Hover over wind turbine buy button.
		if (m_WindTurbineBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI))
		{
			m_displayTooltip.setFont(calibriLight);
			m_displayTooltip.setCharacterSize(14);
			m_displayTooltip.setFillColor(Color::Black);
			m_displayTooltip.setPosition(110, 52);
			stringstream ssTurbine;
			ssTurbine << "Construct a wind turbine.\nTurbines have a low eco impact.\nCost: " << int(8 * m_difficultyMultiplier) << "        Max: 3";
			m_displayTooltip.setString(ssTurbine.str());

			m_window.draw(m_spriteUiTooltip);
			m_window.draw(m_displayTooltip);
		}
		// Hover over solar panel buy button.
		if (m_SolarPanelBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI))
		{
			m_displayTooltip.setFont(calibriLight);
			m_displayTooltip.setCharacterSize(14);
			m_displayTooltip.setFillColor(Color::Black);
			m_displayTooltip.setPosition(110, 52);
			stringstream ssSolar;
			ssSolar << "Construct a solar panel array.\nArrays have a medium eco impact.\nCost: " << int(10 * m_difficultyMultiplier) << "        Max: 3";
			m_displayTooltip.setString(ssSolar.str());

			m_window.draw(m_spriteUiTooltip);
			m_window.draw(m_displayTooltip);
		}
		// Hover over recycling centre buy button.
		if (m_RecyclingCentreBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI))
		{
			m_displayTooltip.setFont(calibriLight);
			m_displayTooltip.setCharacterSize(14);
			m_displayTooltip.setFillColor(Color::Black);
			m_displayTooltip.setPosition(110, 52);
			stringstream ssRecycling;
			ssRecycling << "Construct a recycling centre.\nCentres have a high eco impact.\nCost: " << int(12 * m_difficultyMultiplier) << "        Max: 2";
			m_displayTooltip.setString(ssRecycling.str());

			m_window.draw(m_spriteUiTooltip);
			m_window.draw(m_displayTooltip);
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
		m_displayPollution.setPosition(670, 12);
		m_displayPollution.setString("Pollution");

		//// Using text to display pollution rate for testing purposes only, remove from final game.
		//m_displayPollutionRate.setFont(ka1Font);
		//m_displayPollutionRate.setCharacterSize(16);
		//m_displayPollutionRate.setFillColor(Color::White);
		//m_displayPollutionRate.setPosition(950, 12);
		//stringstream ss2;
		//ss2 << (double)m_pollutionRate * m_difficultyMultiplier;
		//m_displayPollutionRate.setString(ss2.str());

		m_window.draw(m_displayIncome);
		m_window.draw(m_displayPollution);
		m_window.draw(m_displayPollutionRate);
		m_window.display();

		// FOR TESTING, REMOVE LATER.
		// cout << m_pollutionCurrent << endl;

		// Iterate through alive responders and update them.
		list<Responder*>::const_iterator cycleResponders;
		for (cycleResponders = lpResponders.begin(); cycleResponders != lpResponders.end(); cycleResponders++)
		{
			(*cycleResponders)->update(m_elapsedTime, m_spriteTime);

			// If a responder is on a tile, change its value to 2.
			if (m_levelArray[int((*cycleResponders)->getPosition().y / TILESIZE)][int((*cycleResponders)->getPosition().x / TILESIZE)] == 0 && (*cycleResponders)->getIsMoving() == false)
			{
				(m_levelArray[int((*cycleResponders)->getPosition().y / TILESIZE)][int((*cycleResponders)->getPosition().x / TILESIZE)] = 2);
			}
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
			m_gameState = State::VICTORY;
			m_gameWin = true;
			resetLists();
		}
		else if (m_pollutionCurrent >= MAX_POLLUTION)
		{
			m_gameState = State::GAME_OVER;
			m_gameWin = false;
			resetLists();
		}
	}
	
	// Defeat state! Player has lost the game.
	if (m_gameState == State::GAME_OVER)
	{
		//std::cout << "Game Over" << endl;
		m_gameOverText.setString("Unfortunately you've let pollution run out of control.\nNow the world is doomed.\nBetter luck next time.\n\nYour score was: " + std::to_string(m_score));
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

	// Victory state! Player has won the game.
	if (m_gameState == State::VICTORY)
	{
		m_gameVictoryText.setString("Thanks to your efforts, pollution levels have \nfallen to an acceptable level in this region! \nThanks for playing! \n\nYour score was: " + std::to_string(m_score));
		m_window.clear();
		m_window.setMouseCursorVisible(true);
		m_window.setView(m_gameVictoryView);
		m_window.draw(m_menuBackground);
		m_window.draw(m_titleTipShadowText);
		m_window.draw(m_titleTipText);
		m_window.draw(m_gameVictoryText);

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
			// Anytime the player mouse left clicks, reset click delay.
			m_clickDelay = 0;

			// If in game over screen...
			if (m_gameState == State::GAME_OVER)
			{
				if (m_exitMenuButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
				{
					m_sound.click();
					init();
					run();
				}
			}
			// If in victory screen...
			else if (m_gameState == State::VICTORY)
			{
				if (m_exitMenuButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
				{
					m_sound.click();
					init();
					run();
				}
			}
			// If in main menu...
			else if (m_gameState == State::MAIN_MENU)
			{
				if (m_mainMenu)
				{
					// If about play game clicked, switch to difficulty menu.
					if (m_playMenuButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
					{
						m_sound.click();
						m_difficultySelectionMenu = true;
						m_mainMenu = false;
					}
					// If about how to play clicked, switch to how to play menu.
					if (m_howtoMenuButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
					{
						m_sound.click();
						m_howToMenu = true;
						m_mainMenu = false;
						// Show game rules
					}
					// If about game clicked, switch to about menu.
					if (m_aboutMenuButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
					{
						m_aboutMenu = true;
						m_mainMenu = false;
						m_sound.click();
					}
					// If exit clicked, close application.
					if (m_exitMenuButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
					{
						m_sound.click();
						m_window.close();
					}
				}
				// If in difficulty menu, set up buttons appropriately.
				else if (m_difficultySelectionMenu)
				{
					// Choose easy difficulty.
					if (m_easyDifficultyButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
					{
						m_sound.click();
						m_difficultyMultiplier = 1;
						m_gameState = State::PLAYING;
					}
					// Choose medium difficulty.
					if (m_mediumDifficultyButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
					{
						m_sound.click();
						m_difficultyMultiplier = 1.5;
						m_gameState = State::PLAYING;
					}
					// Choose hard difficulty.
					if (m_hardDifficultyButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
					{
						m_sound.click();
						m_difficultyMultiplier = 2;
						m_gameState = State::PLAYING;
					}
					// Return to main menu.
					if (m_exitMenuButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
					{
						m_sound.click();
						m_difficultySelectionMenu = false;
						m_mainMenu = true;
					}
				}
				// If in how to play menu, display text and buttons.
				else if (m_howToMenu)
				{
					if (m_exitMenuButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
					{
						m_sound.click();
						m_howToMenu = false;
						m_mainMenu = true;
					}
				}
				// If in about menu, display text and buttons.
				else if (m_aboutMenu)
				{
					if (m_exitMenuButton.getGlobalBounds().contains(m_mousePositionMenu) && m_clickDelayFlag)
					{
						m_sound.click();
						m_aboutMenu = false;
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
						if (m_levelArray[int(m_mousePositionMain.y / TILESIZE)][int(m_mousePositionMain.x / TILESIZE)] == 0 && m_clickDelayFlag)
						{
							// Set current position back to 0. 
							m_levelArray[int((*cycleResponders)->getPosition().y / TILESIZE)][int((*cycleResponders)->getPosition().x / TILESIZE)] = 0;

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
				if (m_ResponderBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI) && m_clickDelayFlag)
				{
					// Check if you have the cash.
					if (m_goldTotal >= (8 * m_difficultyMultiplier) && m_SolarPanelBuy->isSelected() == false && m_WindTurbineBuy->isSelected() == false && m_RecyclingCentreBuy->isSelected() == false)
					{
						// Cycle through to check if any responders are obstructing the spawn.
						list<Responder*>::const_iterator cycleResponders3;
						for (cycleResponders3 = lpResponders.begin(); cycleResponders3 != lpResponders.end(); cycleResponders3++)
						{
							// If responder already there, no spawn.
							if ((*cycleResponders3)->getPositionX() != 408 && (*cycleResponders3)->getPositionY() != 314)
							{
								m_sound.shopClick();
								m_ResponderBuy->select(true);
							}
						}
					}
					else 
					{
						m_sound.errorClick();
					}
				}

				// Check if buy solar panel button clicked.
				if (m_SolarPanelBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI) && m_clickDelayFlag)
				{
					// Check if you have the cash.
					if (m_goldTotal >= (10 * m_difficultyMultiplier) && m_solarTotal <= 2 && m_ResponderBuy->isSelected() == false && m_WindTurbineBuy->isSelected() == false && m_RecyclingCentreBuy->isSelected() == false)
					{
						m_sound.shopClick();
						m_SolarPanelBuy->select(true);
						m_cursorStyle = 3;
					}
					else
					{
						m_sound.errorClick();
					}
				}

				// Check if another click is made while wind turbine selected.
				if (m_SolarPanelBuy->isSelected() && m_levelArray[int(m_mousePositionMain.y / TILESIZE)][int(m_mousePositionMain.x / TILESIZE)] == 0 && m_clickDelayFlag)
				{
					// Check number of active solar panels.
					if (m_solarTotal == 0)
					{
						m_solar1->spawn(m_mousePositionMain.x, m_mousePositionMain.y);
						lpRenewableSource.push_back(m_solar1);
						m_solar1->isPlaced();
					}
					else if (m_solarTotal == 1)
					{
						m_solar2->spawn(m_mousePositionMain.x, m_mousePositionMain.y);
						lpRenewableSource.push_back(m_solar2);
						m_solar2->isPlaced();
					}
					else if (m_solarTotal == 2)
					{
						m_solar3->spawn(m_mousePositionMain.x, m_mousePositionMain.y);
						lpRenewableSource.push_back(m_solar3);
						m_solar3->isPlaced();
					}
					m_pollutionRate -= 0.02;
					m_goldTotal -= (10 * m_difficultyMultiplier);
					m_SolarPanelBuy->select(false);
					m_cursorStyle = 0;
					m_solarTotal++;
					m_sound.solarSound();
					cout << "A new solar panel has been created!\n";
				}

				// Check if buy wind turbine button clicked.
				if (m_WindTurbineBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI) && m_clickDelayFlag)
				{
					// Check if you have the cash.
					if (m_goldTotal >= (8 * m_difficultyMultiplier) && m_turbineTotal <= 2 && m_ResponderBuy->isSelected() == false && m_SolarPanelBuy->isSelected() == false && m_RecyclingCentreBuy->isSelected() == false)
					{
						m_sound.shopClick();
						m_WindTurbineBuy->select(true);
						m_cursorStyle = 2;
					}
					else
					{
						m_sound.errorClick();
					}
				}

				// Check if another click is made while wind turbine selected.
				if (m_WindTurbineBuy->isSelected() && m_levelArray[int(m_mousePositionMain.y / TILESIZE)][int(m_mousePositionMain.x / TILESIZE)] == 0 && m_clickDelayFlag)
				{
					// Check number of active turbines.
					if (m_turbineTotal == 0) 
					{
						m_turbine1->spawn(m_mousePositionMain.x, m_mousePositionMain.y);
						lpRenewableSource.push_back(m_turbine1);
						m_turbine1->isPlaced();
					}
					else if (m_turbineTotal == 1)
					{
						m_turbine2->spawn(m_mousePositionMain.x, m_mousePositionMain.y);
						lpRenewableSource.push_back(m_turbine2);
						m_turbine2->isPlaced();
					}
					else if (m_turbineTotal == 2)
					{
						m_turbine3->spawn(m_mousePositionMain.x, m_mousePositionMain.y);
						lpRenewableSource.push_back(m_turbine3);
						m_turbine3->isPlaced();
					}
					m_pollutionRate -= 0.01;
					m_goldTotal -= (8 * m_difficultyMultiplier);
					m_WindTurbineBuy->select(false); 
					m_cursorStyle = 0;
					m_turbineTotal++;
					m_sound.turbineSound();
					cout << "A new wind turbine has been created!\n";
				}

				// Check if buy recycling centre button clicked.
				if (m_RecyclingCentreBuy->m_Sprite.getGlobalBounds().contains(m_mousePositionGUI) && m_clickDelayFlag)
				{
					if (m_goldTotal >= (12 * m_difficultyMultiplier) && m_recyclingTotal <= 1 && m_ResponderBuy->isSelected() == false && m_WindTurbineBuy->isSelected() == false && m_SolarPanelBuy->isSelected() == false)
					{
						m_sound.shopClick();
						m_RecyclingCentreBuy->select(true);
						m_cursorStyle = 4;
					}
					else
					{
						m_sound.errorClick();
					}
				}

				// Check if another click is made while recycling centre selected.
				if (m_RecyclingCentreBuy->isSelected() && m_levelArray[int(m_mousePositionMain.y / TILESIZE)][int(m_mousePositionMain.x / TILESIZE)] == 0 && m_clickDelayFlag)
				{
					// Check number of active recycling centres. 
					if (m_recyclingTotal == 0) 
					{
						m_recycling1->spawn(m_mousePositionMain.x, m_mousePositionMain.y);
						lpRenewableSource.push_back(m_recycling1);
						m_recycling1->isPlaced();
					}
					else if (m_recyclingTotal == 1) 
					{
						m_recycling2->spawn(m_mousePositionMain.x, m_mousePositionMain.y);
						lpRenewableSource.push_back(m_recycling2);
						m_recycling2->isPlaced();
					}
					m_pollutionRate -= 0.05;
					m_RecyclingCentreBuy->select(false);
					m_goldTotal -= (12 * m_difficultyMultiplier);
					m_cursorStyle = 0;
					m_recyclingTotal++;
					m_sound.recyclingSound();
					cout << "A new recycling centre has been created!\n";
				}

				// Click menu icon to return to main menu.
				if (m_spriteMenuBar.getGlobalBounds().contains(m_mousePositionGUI))
				{
					m_sound.click();
						init();
						run();
				}
			}
		}

		// For handling mouse dragging across the screen to move camera.
		if (Mouse::isButtonPressed(Mouse::Right)) 
		{
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
				m_sound.click();
				init();
				run();
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

		if (lpResponders.size() >= 4) {
			// Do nothing, add error sound.
		}
		else if (lpResponders.size() < 4) {

			if (lpResponders.size() == 1) {
				m_responder2 = new Responder;
				lpResponders.push_back(m_responder2);
				okayNewResponder = true;
				m_goldTotal -= (8 * m_difficultyMultiplier);
				cout << "A new responder has joined the fight!\n";
				m_ResponderBuy->select(false);
			}
			else if (lpResponders.size() == 2) {
				m_responder3 = new Responder;
				lpResponders.push_back(m_responder3);
				okayNewResponder2 = true;
				m_goldTotal -= (8 * m_difficultyMultiplier);
				cout << "A new responder has joined the fight!\n";
				m_ResponderBuy->select(false);
			}
			else if (lpResponders.size() == 3) {
				m_responder4 = new Responder;
				lpResponders.push_back(m_responder4);
				okayNewResponder3 = true;
				m_goldTotal -= (8 * m_difficultyMultiplier);
				cout << "A new responder has joined the fight!\n";
				m_ResponderBuy->select(false);
			}
		}
		// VERY IMPORTANT: Deselect button after spawn.
	}
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
	m_gameOverText.setString("Unfortunately you've let pollution run out of control.\nNow the world is doomed.\nBetter luck next time.\nYour score was: ");
	m_gameOverText.setOrigin((m_gameOverText.getGlobalBounds().width / 2), (m_gameOverText.getGlobalBounds().height / 2));
	m_gameOverText.setPosition((RESOLUTION.x / 2), 250);

	m_gameVictoryText.setFont(m_vcrFont);
	m_gameVictoryText.setCharacterSize(28);
	m_gameVictoryText.setFillColor(Color::White);
	m_gameVictoryText.setString("Thanks to your efforts, pollution levels have \nfallen to an acceptable level in this region!\nThanks for playing!\nYour score was : ");
	m_gameVictoryText.setOrigin((m_gameVictoryText.getGlobalBounds().width / 2), (m_gameVictoryText.getGlobalBounds().height / 2));
	m_gameVictoryText.setPosition((RESOLUTION.x / 2), 250);

	m_howToPlayText.setFont(m_vcrFont);
	m_howToPlayText.setCharacterSize(28);
	m_howToPlayText.setFillColor(Color::White);
	m_howToPlayText.setString("Command your responder to fight disasters.\nResponders must be adjacent to disasters to fight.\nUse funding earned to buy new responders\nand purchase renewable buildings.\n\nTake care that the pollution bar does not reach\nfull purple! Use left-mouse clicks to command / buy, and\nright-mouse to drag. Zoom using scroll wheel.");
	m_howToPlayText.setOrigin((m_howToPlayText.getGlobalBounds().width / 2), (m_howToPlayText.getGlobalBounds().height / 2));
	m_howToPlayText.setPosition((RESOLUTION.x / 2), 250);

	m_aboutGameText.setFont(m_vcrFont);
	m_aboutGameText.setCharacterSize(28);
	m_aboutGameText.setFillColor(Color::White);
	m_aboutGameText.setString("Disaster Squad was made to highlight the United Nation's\n Goal 13 for Taking urgent action to combat climate\n change and its impacts.\n Fight against rising pollution, global warming induced\ndisasters, and pave the way forward with green energy!\n\nTeam: Merri Mogridge, Dominik Godlewski, & Conor Reilly!");
	m_aboutGameText.setOrigin((m_aboutGameText.getGlobalBounds().width / 2), (m_aboutGameText.getGlobalBounds().height / 2));
	m_aboutGameText.setPosition((RESOLUTION.x / 2), 250);

	// Set textures, origins and positions for various game sprites 
	m_background.setTexture(m_textureHolder.GetTexture("graphics/Grasslandsmap.png"));
	m_background.setOrigin(0, 0);
	m_background.setPosition(0, 0);

	m_spriteUIBar.setTexture(m_textureHolder.GetTexture("graphics/ui_bar.png"));
	m_spriteUIBar.setOrigin(0, 0);

	m_spriteMenuBar.setTexture(m_textureHolder.GetTexture("graphics/menu_icon.png"));
	m_spriteMenuBar.setOrigin(-6, -2);

	m_spritePollutionBar.setTexture(m_textureHolder.GetTexture("graphics/pollution_bar2.png"));
	m_spritePollutionBar.setPosition(820, 8);

	m_spritePollutionLevel.setTexture(m_textureHolder.GetTexture("graphics/bar_measure.png"));
	m_spritePollutionLevel.setPosition(850, 5);

	m_spriteUiTooltip.setTexture(m_textureHolder.GetTexture("graphics/ui_tooltip.png"));
	m_spriteUiTooltip.setOrigin(0, 0);
	m_spriteUiTooltip.setPosition(100, 48);

}//Complain about git hub in write up!

void Engine::updateCursor() // Update cursor to reflect current UI positions and options.
{
	// If / else to choose between cursor styles.
	if (m_cursorStyle == 0)
	{
		// Crosshair for main view.
		m_spriteCursor.setTexture(m_textureHolder.GetTexture("graphics/cursor_spritesheet.png"));
		m_spriteCursor.setTextureRect(IntRect{ 0, 0, 40, 40 });
		m_spriteCursor.setOrigin(20, 20);
	}

	// Mouse cursor for GUI view.
	if (m_cursorStyle == 1)
	{
		m_spriteCursor.setTexture(m_textureHolder.GetTexture("graphics/cursor_spritesheet.png"));
		m_spriteCursor.setTextureRect(IntRect{ 48, 0, 32, 40 });
		m_spriteCursor.setOrigin(16, 20);
	}

	// Cursor to wind turbine placement.
	if (m_cursorStyle == 2)
	{
		if (m_levelArray[int(m_mousePositionMain.y / TILESIZE)][int(m_mousePositionMain.x / TILESIZE)] == 0) 
		{
			m_spriteCursor.setTexture(m_textureHolder.GetTexture("graphics/cursor_spritesheet.png"));
			m_spriteCursor.setTextureRect(IntRect{ 96, 8, 16, 32 });
			m_spriteCursor.setOrigin(8, 16);
		}
		else {
			m_spriteCursor.setTexture(m_textureHolder.GetTexture("graphics/cursor_spritesheet.png"));
			m_spriteCursor.setTextureRect(IntRect{ 128, 8, 16, 32 });
			m_spriteCursor.setOrigin(8, 16);
		}
	}

	// Cursor to solar panel placement.
	if (m_cursorStyle == 3) {
		if (m_levelArray[int(m_mousePositionMain.y / TILESIZE)][int(m_mousePositionMain.x / TILESIZE)] == 0)
		{
			m_spriteCursor.setTexture(m_textureHolder.GetTexture("graphics/cursor_spritesheet.png"));
			m_spriteCursor.setTextureRect(IntRect{ 160, 16, 26, 24 });
			m_spriteCursor.setOrigin(13, 12);
		}
		else {
			m_spriteCursor.setTexture(m_textureHolder.GetTexture("graphics/cursor_spritesheet.png"));
			m_spriteCursor.setTextureRect(IntRect{ 192, 16, 26, 24 });
			m_spriteCursor.setOrigin(13, 12);
		}
	}

	// Cursor to recycling centre placement.
	if (m_cursorStyle == 4)
	{
		if (m_levelArray[int(m_mousePositionMain.y / TILESIZE)][int(m_mousePositionMain.x / TILESIZE)] == 0)
		{
			m_spriteCursor.setTexture(m_textureHolder.GetTexture("graphics/cursor_spritesheet.png"));
			m_spriteCursor.setTextureRect(IntRect{ 224, 18, 22, 22 });
			m_spriteCursor.setOrigin(11, 11);
		}
		else {
			m_spriteCursor.setTexture(m_textureHolder.GetTexture("graphics/cursor_spritesheet.png"));
			m_spriteCursor.setTextureRect(IntRect{ 256, 18, 22, 22 });
			m_spriteCursor.setOrigin(11, 11);
		}
	}
} // End of update cursor.

void Engine::collisionDetection() //Check if Responder is in a certain range of Disaster object
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

void Engine::resetLists()
{
	for (list<Disaster*>::const_iterator iter = lpDisasters.begin(); iter != lpDisasters.end(); ++iter)
	{
		// Check if disaster is not spawned yet
		if ((*iter)->getSpawnStatus())
		{
			(*iter)->destroyDisaster();
		}
	}

	lpDisasters.clear();
	lpResponders.clear();
	lpRenewableSource.clear();
}

int Engine::coordinateToTile(Vector2f position)
{
	return (int(position.y / TILESIZE) * (RESOLUTION.x / TILESIZE) + int(position.x / TILESIZE));
}