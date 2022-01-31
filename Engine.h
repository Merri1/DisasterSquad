#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "GameGraph.h"
#include "Pathfinding.h"
#include "TextureHolder.h"
#include "Responder.h"
#include "Disaster.h"
#include "Wildfire.h"
#include "Shop.h"
#include "RenewableSource.h"
#include "WindTurbine.h"
#include "SolarPanel.h"
#include "RecyclingCentre.h"

#include <random>
#include <list>

class Engine
{
public:
    Engine();
    void init();
    void run();
    void render();
    void draw();
    void update();
    void checkSelected();
    void eventManager(Event& e);
    void collisonDetection();
    int coordinateToTile(Vector2f position);
    // Functions here
    


protected:
    const int FRAMERATE = 60;
    const int TILESIZE = 16;
    const int MAX_POLLUTION = 1000;
    const Vector2i RESOLUTION = Vector2i(1024, 576);
    int m_levelArray[36][64];
    vector<int> m_pathToDestination;
    enum class State { PAUSED, PLAYING, MAIN_MENU, GAME_OVER, LEVEL_UP };
    
    State m_gameState;
    bool m_mainMenu;
    bool m_difficultySelectionMenu;
    bool m_aboutMenu;
    bool m_howToMenu;
    float m_difficultyMultiplier;
    float m_elapsedTime;
    float m_pollutionCurrent;
    float m_pollutionRate;
    float m_goldTotal;
    float m_goldRate;
    float m_wildfireTotal;
    int camZoom;

    int m_powerTotal;

    //Game game;
    Texture m_backgroundTexture;
    Responder* m_responder1;
    Responder* m_responder2;
    Responder* m_responder3;
    Responder* m_responder4;

    RenewableSource* m_solar1;
    RenewableSource* m_solar2;
    RenewableSource* m_solar3;
    RenewableSource* m_solar4;

    RenewableSource* m_turbine1;
    RenewableSource* m_turbine2;
    RenewableSource* m_turbine3;

    RenewableSource* m_recycle1;
    RenewableSource* m_recycle2;

    Disaster* m_disaster1;
    Disaster* m_disaster2;
    Disaster* m_disaster3;
    Disaster* m_disaster4;

    Shop* m_ResponderBuy;
    Shop* m_WindTurbineBuy;
    Shop* m_SolarPanelBuy;
    Shop* m_RecyclingCentreBuy;
    Shop* m_shop1;

    //VertexArray virtualGrid;
    //GridManager grid;
    GameGraph graph;
    Pathfinding pathfind;
    std::list<Disaster*> lpDisasters;
    std::list<Responder*> lpResponders;
    std::list<Shop*> lpShop;
    std::list<RenewableSource*> lpRenewableSource;

    //std::list<Shop*> lpShop;
    RenderWindow m_window;
    View m_mainView;
    View m_guiView;
    View m_mainMenuView;
    View m_gameOverView;
    
    Sprite m_menuBackground;
    Sprite m_playMenuButton;
    Sprite m_howtoMenuButton;
    Sprite m_aboutMenuButton;
    Sprite m_exitMenuButton;
    Sprite m_easyDifficultyButton;
    Sprite m_mediumDifficultyButton;
    Sprite m_hardDifficultyButton;
    Sprite m_background;
    Sprite m_spriteCrosshair;
    
    Vector2f m_mousePositionMenu;
    Vector2f m_mousePositionMain;
    Vector2f m_mousePositionGUI;
    
    Sprite m_spriteMainCollisionBox;
    Sprite m_spriteGUICollisionBox;
    Sprite m_spritePollutionBar;
    Sprite m_spritePollutionTitle;
    Sprite m_spritePollutionLevel;
    Sprite m_spriteUIBar;
    Sprite m_spriteMenuBar;
    Sprite m_spriteWildfireCounter;
    
    TextureHolder m_textureHolder;
    Font ka1Font;
    Font m_vcrFont;
    Text m_titleTipText;
    Text m_titleTipShadowText;
    Text m_playMenuText;
    Text m_howtoMenuText;
    Text m_aboutMenuText;
    Text m_exitMenuText;
    Text m_easyDifficultyText;
    Text m_mediumDifficultyText;
    Text m_hardDifficultyText;
    Text m_backButtonText;
    Text m_displayIncome;
    Text m_displayPollution;
    Text m_displayPollutionRate;
   

    bool okayNewResponder;
    bool okayNewResponder2;
    bool okayNewResponder3; 
    bool okayNewTurbine;

};
#endif
