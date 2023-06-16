#include "board.h"
#include <iostream>
#include <SFML/Graphics.hpp>


class Game{

public:
    Game();
    ~Game();

    void update();
    void display();

    bool isRunning();
    void resizeBoard();



private:
    sf::RenderWindow window;
    sf::Event event;
    std::vector<sf::Texture> textureLists;
    std::vector<sf::Sprite> spriteLists;

    sf::Texture backgroundTexture;
    sf::Texture pawnTexture;
    sf::Texture rookTexture;
    sf::Texture knightTexture;
    sf::Texture bishopTexture;
    sf::Texture queenTexture;
    sf::Texture kingTexture;
    sf::Texture wpawnTexture;
    sf::Texture wrookTexture;
    sf::Texture wknightTexture;
    sf::Texture wbishopTexture;
    sf::Texture wqueenTexture;
    sf::Texture wkingTexture;

    sf::Sprite background;
    bool running;
    float gridSize;
    float pieceScale;
    int textureDisplaySize;

    ChessBoard *board;
    std::vector<char> currBoard;

    //int count, idx;
    void initTextures();
    void drawPieces();
};
