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
    this->moveFrom = {-1, -1};
    this->promotion = false;
}

Game::~Game(){
    delete this->board;
}

void Game::handleMouseClick(){
    sf::Vector2i mousePos = sf::Mouse::getPosition(this->window);
    if(this->promotion){
        this->promotion = false;
        char targetPiece;
        if(mousePos.x <= 2 * this->gridSize){
            targetPiece = ROOK;
        }
        else if(mousePos.x <= 4 * this->gridSize){
            targetPiece = KNIGHT;
        }
        else if(mousePos.x <= 6 * this->gridSize){
            targetPiece = BISHOP;
        }
        else{
            targetPiece = QUEEN;
        }
        this->board->move(this->moveFrom, this->moveTo, targetPiece);
        this->currBoard = this->board->getGameBoard();
        this->moveFrom = {-1, -1};
        this->validTargets = {};
        return;
    }
    int row, col;
    row = mousePos.y / this->gridSize;
    col = mousePos.x / this->gridSize;
    if(this->moveFrom.first != -1){
        if((row == 0 || row == 7) && 
            (this->currBoard[this->moveFrom.first * 8 + 
             this->moveFrom.second] % 10 == PAWN)){
            this->promotion = true;
            this->moveTo = {row, col};
            return;
        }
        bool success = this->board->move(this->moveFrom, {row, col});
        if(success){
            this->currBoard = this->board->getGameBoard();
        }
        this->validTargets.clear();
        this->moveFrom = {-1, -1};
    }
    else{
        this->validTargets = this->board->getValidMovements(row, col);
        if(this->validTargets.size() != 0){
            this->moveFrom = {row, col};
        }
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
        sprite.setPosition(xPos + 5, yPos + 5);
        this->window.draw(sprite);
    }
}

void Game::displayOverlay(){
    if(this->validTargets.size() != 0){
        sf::CircleShape circle(this->gridSize / 2);
        circle.setFillColor(sf::Color(128, 128, 128, 192));
        circle.setPosition(
                this->moveFrom.second * this->gridSize,
                this->moveFrom.first * this->gridSize);
        this->window.draw(circle);

        circle.setRadius(this->gridSize / 4);
        for(int idx : this->validTargets){
            circle.setPosition( 
                    (idx % 8) * this->gridSize + this->gridSize / 4,
                    (int)(idx / 8) * this->gridSize +  this->gridSize / 4);            
            this->window.draw(circle);
        }
    }
    if(this->promotion){
        int mouseX = sf::Mouse::getPosition(this->window).x;
        sf::Vector2f rectSize = {this->gridSize * 2, this->gridSize * 8};
        sf::RectangleShape darkRect(rectSize);
        darkRect.setFillColor(sf::Color(128, 128, 128, 128));
        sf::RectangleShape lightRect(rectSize);
        lightRect.setFillColor(sf::Color(128, 128, 128, 192));
        for(int i = 0; i < 4; i++){
            if(mouseX <= this->gridSize * 2 * (i + 1) &&
                    mouseX > this->gridSize * 2 * i){
                lightRect.setPosition(this->gridSize * 2 * i, 0);
                this->window.draw(lightRect);
            }
            else{
                darkRect.setPosition(this->gridSize * 2 * i, 0);
                this->window.draw(darkRect);
            }
        }
        sf::Sprite s(this->textureLists[2]);

        s.setScale(this->pieceScale * 2, this->pieceScale * 2);
        s.setPosition(0, this->gridSize * 3 + 10);
        this->window.draw(s);

        s.setTexture(this->textureLists[3]);
        s.setPosition(this->gridSize * 2 + 10, this->gridSize * 3 + 10);
        this->window.draw(s);
        
        s.setTexture(this->textureLists[4]);
        s.setPosition(this->gridSize * 4 + 10, this->gridSize * 3 + 10);
        this->window.draw(s);

        s.setTexture(this->textureLists[5]);
        s.setPosition(this->gridSize * 6 + 10, this->gridSize * 3 + 10);
        this->window.draw(s);
    }
}

void Game::display(){
    this->window.clear(sf::Color(100, 100, 100));
    this->window.draw(this->background);
    this->drawPieces();
    this->displayOverlay();
    this->window.display();
}

bool Game::isRunning(){
    return this->running;
}

void Game::resizeBoard(){
    sf::Vector2u windowSize = this->window.getSize();
    float min = std::min(windowSize.x, windowSize.y);

    this->gridSize = min / 8;

    this->pieceScale = (this->gridSize - 10) / this->textureDisplaySize;

    sf::Vector2u textureSize = this->backgroundTexture.getSize();
    this->background.setTextureRect(sf::IntRect(0, 0, textureSize.x * 4, textureSize.y * 4));
    this->background.setScale(min / (textureSize.x * 4 - 2), min / (textureSize.x * 4 - 4));
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



