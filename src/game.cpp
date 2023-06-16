#include "game.h"
#include <filesystem>

Game::Game(){
    this->window.create(
            sf::VideoMode(600, 600), 
            "Chess", 
            sf::Style::Titlebar | sf::Style::Close //| sf::Style::Resize
            );
    this->running = true;

    this->window.setFramerateLimit(15);
    initTextures();

    this->textureDisplaySize = 42;
    // NOT RESIZABLE YET
    resizeBoard();
    //count = idx = 0;

    this->board = new ChessBoard();
    this->currBoard = this->board->getGameBoard();
    this->selectedPiece = {-1, -1};
}

Game::~Game(){
    delete this->board;
}

void Game::handleMouseClick(){
    std::cout << "Handle Mouse Click" << std::endl;
    sf::Vector2i mousePos = sf::Mouse::getPosition(this->window);
    int row, col;
    row = mousePos.y / this->gridSize;
    col = mousePos.x / this->gridSize;
    if(this->selectedPiece.first != -1){
        bool success = this->board->move(this->selectedPiece, {row, col});
        if(success){
            this->currBoard = this->board->getGameBoard();
        }
        else{
            std::cout << "From: " << selectedPiece.first << ", " << selectedPiece.second << ", to: " << row << ", " << col << std::endl;
        }
        this->selectedPiece = {-1, -1};
    }
    else{
        this->selectedPiece = {row, col};
    }
}

void Game::update(){
    while(this->window.pollEvent(this->event)){
        switch(this->event.type){
            case sf::Event::Closed:
                {
                    this->running = false;
                    break;
                }
            case sf::Event::Resized:
                {
                    this->resizeBoard();
                    break;
                }
            case sf::Event::MouseButtonPressed:
                {
                    this->handleMouseClick();
                }
            default:
                break;
        }
    }
}

void Game::drawPieces(){
    sf::Sprite sprite;
    float xPos, yPos;
    sprite.scale(this->pieceScale, this->pieceScale);
    int i;
    for(int idx = 0; idx < this->currBoard.size(); idx++){
        i = this->currBoard[idx];
        if(i == 0) continue;
        if(i > 10){
            sprite.setTexture(this->textureLists[i % 10 + 6]);
        }
        else{
            sprite.setTexture(this->textureLists[i % 10]);
        }
        
        xPos = this->gridSize * (idx % 8);
        yPos = this->gridSize * (int)(idx / 8);
        sprite.setPosition(xPos, yPos);
        this->window.draw(sprite);
    }
    if(this->selectedPiece.first != -1){
        sf::CircleShape circle(this->gridSize / 2);
        circle.setFillColor(sf::Color(128, 128, 128, 128));
        circle.setPosition(this->selectedPiece.second * this->gridSize, this->selectedPiece.first * this->gridSize);
        this->window.draw(circle);
    }
}

void Game::display(){
    this->window.clear(sf::Color(100, 100, 100));
    this->window.draw(this->background);
    this->drawPieces();
    this->window.display();
}

bool Game::isRunning(){
    return this->running;
}

void Game::resizeBoard(){
    sf::Vector2u windowSize = this->window.getSize();
    float min = std::min(windowSize.x, windowSize.y);

    this->gridSize = min / 8;

    this->pieceScale = this->gridSize / this->textureDisplaySize;

    sf::Vector2u textureSize = this->backgroundTexture.getSize();
    this->background.setTextureRect(sf::IntRect(0, 0, textureSize.x * 4 - 1 , textureSize.y * 4 + 5));
    this->background.setScale(min / (textureSize.x * 4), min / (textureSize.x * 4));
}

void Game::initTextures(){
    std::string imgDir = std::__fs::filesystem::path(__FILE__).parent_path();
    imgDir += "/../imgs/";

    this->backgroundTexture.loadFromFile(imgDir + "chessboard.png");
    this->backgroundTexture.setRepeated(true);
    this->background.setTexture(this->backgroundTexture);
//    sf::Color overLayColor(150, 150, 150, 200);
//    this->background.setColor(overLayColor);

    this->pawnTexture.loadFromFile(imgDir + "pawn1.png");
    this->rookTexture.loadFromFile(imgDir + "rook1.png");
    this->knightTexture.loadFromFile(imgDir + "knight1.png");
    this->bishopTexture.loadFromFile(imgDir + "bishop1.png");
    this->queenTexture.loadFromFile(imgDir + "queen1.png");
    this->kingTexture.loadFromFile(imgDir + "king1.png");

    this->wpawnTexture.loadFromFile(imgDir + "pawn.png");
    this->wrookTexture.loadFromFile(imgDir + "rook.png");
    this->wknightTexture.loadFromFile(imgDir + "knight.png");
    this->wbishopTexture.loadFromFile(imgDir + "bishop.png");
    this->wqueenTexture.loadFromFile(imgDir + "queen.png");
    this->wkingTexture.loadFromFile(imgDir + "king.png");


    this->textureLists = {
        backgroundTexture, 

        pawnTexture, rookTexture, knightTexture, 
        bishopTexture, queenTexture, kingTexture,

        wpawnTexture, wrookTexture, wknightTexture, 
        wbishopTexture, wqueenTexture, wkingTexture,
    };
}



