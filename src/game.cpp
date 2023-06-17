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
    this->initTextures();

    this->textureDisplaySize = 42;
    // NOT RESIZABLE YET
    this->resizeBoard();
    //count = idx = 0;
    this->initText();

    this->board = new ChessBoard();
    this->currBoard = this->board->getGameBoard();
    this->moveFrom = {-1, -1};
    this->promotion = false;
    this->prevFrom = {-1, -1};

}

Game::~Game(){
    delete this->board;
}

void Game::handleMouseClick(){
    if(!this->board->gameIsRunning()){
        this->board->resetBoard();
        this->currBoard = this->board->getGameBoard();
    }
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
        if(this->board->move(this->moveFrom, this->moveTo, targetPiece)){
            this->currBoard = this->board->getGameBoard();
        }
        this->moveFrom = {-1, -1};
        this->validTargets = {};
        return;
    }
    int row, col;
    row = mousePos.y / this->gridSize;
    col = mousePos.x / this->gridSize;
    if(this->board->isSelectable({row, col})){
        if(row == this->moveFrom.first && col == this->moveFrom.second){
            this->moveFrom = {-1, -1};
            this->validTargets = {};
            return;
        }
        this->validTargets = this->board->getValidMovements(row, col);
        this->moveFrom = {row, col};
        return;
    }
    if(this->moveFrom.first != -1){
        int currIdx = row * 8 + col;
        bool isPawn = this->currBoard[this->moveFrom.first * 8 + 
                                    this->moveFrom.second] % 10 == PAWN;
        bool reachedEnd = (row == 0 || row == 7);
        if(isPawn && reachedEnd){
            bool isValidTarget = false;
            for(int validTar : this->validTargets){
                if(validTar == currIdx){
                    isValidTarget = true;
                    break;
                }
            }
            if(!isValidTarget){
                this->moveFrom = {-1, -1};
                this->validTargets = {};
                return;
            }
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
//        this->validTargets = this->board->getValidMovements(row, col);
//        this->moveFrom = {row, col};
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
    if(!this->board->gameIsRunning()){
        sf::RectangleShape rectOverlay;
        rectOverlay.setSize(this->windowSize);
        rectOverlay.setFillColor(sf::Color(128, 128, 128, 192));
        this->window.draw(rectOverlay);
        this->window.draw(this->gameOverText);
        this->window.draw(this->restartText);
        return;
    }
    if(this->moveFrom.first != -1){
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
        sf::RectangleShape lightRect(rectSize);
        darkRect.setFillColor(sf::Color(128, 128, 128, 192));
        lightRect.setFillColor(sf::Color(128, 128, 128, 128));
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
    this->windowSize = {this->gridSize * 8, this->gridSize * 8};
}

void Game::initTextures(){
    std::string srcDir = std::__fs::filesystem::path(__FILE__).parent_path();
    srcDir += "/../";

    this->backgroundTexture.loadFromFile(srcDir + "imgs/chessboard.png");
    this->backgroundTexture.setRepeated(true);
    this->background.setTexture(this->backgroundTexture);
//    sf::Color overLayColor(150, 150, 150, 200);
//    this->background.setColor(overLayColor);

    this->pawnTexture.loadFromFile(srcDir + "imgs/pawn1.png");
    this->rookTexture.loadFromFile(srcDir + "imgs/rook1.png");
    this->knightTexture.loadFromFile(srcDir + "imgs/knight1.png");
    this->bishopTexture.loadFromFile(srcDir + "imgs/bishop1.png");
    this->queenTexture.loadFromFile(srcDir + "imgs/queen1.png");
    this->kingTexture.loadFromFile(srcDir + "imgs/king1.png");

    this->wpawnTexture.loadFromFile(srcDir + "imgs/pawn.png");
    this->wrookTexture.loadFromFile(srcDir + "imgs/rook.png");
    this->wknightTexture.loadFromFile(srcDir + "imgs/knight.png");
    this->wbishopTexture.loadFromFile(srcDir + "imgs/bishop.png");
    this->wqueenTexture.loadFromFile(srcDir + "imgs/queen.png");
    this->wkingTexture.loadFromFile(srcDir + "imgs/king.png");


    this->textureLists = {
        backgroundTexture, 

        pawnTexture, rookTexture, knightTexture, 
        bishopTexture, queenTexture, kingTexture,

        wpawnTexture, wrookTexture, wknightTexture, 
        wbishopTexture, wqueenTexture, wkingTexture,
    };

    if(!this->font.loadFromFile(srcDir + "Silkscreen/slkscre.ttf")){
        std::cout << "Failed to load font" << std::endl;
    }
}

void Game::initText(){
    this->gameOverText.setFont(this->font);
    this->gameOverText.setString("Game\nOver");
    this->gameOverText.setCharacterSize(86);
    this->gameOverText.setPosition( this->gridSize * 2 + 10,
                                    this->gridSize * 2 + 10);
    this->gameOverText.setFillColor(sf::Color::Black);
    this->gameOverText.setStyle(sf::Text::Bold);

    this->restartText.setFont(this->font);
    this->restartText.setString("Left Click to Restart");
    this->restartText.setCharacterSize(20);
    this->restartText.setPosition(this->gridSize * 2 + 3, 
                                    this->gridSize * 5 + 10);
    this->restartText.setFillColor(sf::Color::Black);
}


