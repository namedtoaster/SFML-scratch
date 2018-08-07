//
//  Game.cpp
//  SFML-test
//
//  Created by Dave Campbell on 7/8/18.
//  Copyright © 2018 Dave Campbell. All rights reserved.
//

#include "Game.hpp"
//#include "Constants.h"

Game::Game() : _window(sf::VideoMode(WIDTH, HEIGHT), "SFML test"), _map("data") {
    _state = PLAY;
    _isJumping = false;
    _init();
}

Game::~Game() {
    for (int i = 0; i < _sprites.size(); i++)
        delete _sprites[i];
}

void Game::run() {
    //_backgroundMusic.play();
    while (_window.isOpen()) {
        _processEvents();
        _player.updatePosition();
        _draw();
    }
}

void Game::_init() {
    // Window initialization
    _window.setFramerateLimit(60);
    _window.setVerticalSyncEnabled(true);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile("icon.png")) {
        return EXIT_FAILURE;
    }
    _window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // Load the background
    if (!_bgTexture.loadFromFile("cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    _background.setTexture(_bgTexture);
    
    sf::IntRect temp = _background.getTextureRect();
    _bgWidth = temp.width;
    _bgHeight = temp.height;
    
    // Load the text
    _font.loadFromFile("chintzy.ttf");
    _text.setString("Hello world");
    _text.setFont(_font);
    _text.setCharacterSize(30);
    _text.setStyle(sf::Text::Bold);
    _text.setFillColor(sf::Color::Yellow);
    
    // Initialize the view to always be in the center of the screen, regardless of the size of the window. This will be called when resizing the window as well
    _updateViewPos();
    
    
    
    // Run the game
    run();
}

void Game::_processEvents() {
    // Process events
    sf::Event event;
    
    // The reason that key press events aren't in the while loop (with the exception of the Escape key) is because this won't give smooth input for player movement
    while (_window.pollEvent(event)) {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
        // Escape pressed: exit
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            _window.close();
        }
    }
    
    // Movement
    
    // Move right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && _player.getPosition().x < _bgWidth - _player.getSize().x / 2)
    {
        // Update the player position
        _player.moveRight();
        
        // 1. If the player is beyond one half of the screen width
        if (_player.getPosition().x > _view.getCenter().x) {
            // 2. If the player is not beyond half a screen width distance from the right side of the map
            if (_player.getPosition().x < _bgWidth - _window.getSize().x / 2) {
                _view.move(MOVE_D, 0.0f);
            }
        }
    }
    // Move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && _player.getPosition().x > PLAYER_START_X)
    {
        // Update the player position
        _player.moveLeft();
        
        // Update the view
        
        // 1. If the player is not beyond the far left side of the map
        if (_player.getPosition().x > PLAYER_START_X) {
            // 2. If the player is at the left side of the screen
            if (_player.getPosition().x < _view.getCenter().x - _window.getSize().x / 2 + PLAYER_START_X) {
                // 3. If the player within half the screen width of the far right of the map
                if (_player.getPosition().x < _bgWidth - _window.getSize().x / 2)
                    _view.move(-MOVE_D, 0.0f);
            }
        }
    }
    
    // Jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !_player.isJumping()) {
        _player.jump();
    }
    
    // Window resize
    if (event.type == sf::Event::Resized) {
        /// Update background position
        _updateViewPos();
        
        // TODO: Prevent the window from being shurnk smaller than the height of the map and a set width
    }
}

void Game::_updateViewPos() {
    std::cout << "window height - image height: " << _window.getSize().y - _bgHeight << std::endl;
    _view.reset(sf::FloatRect(0,0, 1000,1000));//_window.getSize().x, _window.getSize().y));
    _view.setViewport(sf::FloatRect(0, 0.3, 1.0,1.0));
    
    // Make sure the player is in view when resizing the window
    if (_player.getPosition().x > _window.getSize().x)
        _view.setCenter(_player.getPosition().x, _view.getCenter().y);
    // If the player is past the point which would cause the view to be shifted too far left when the window is shrunk, center up the view on the middle of the window
    if (_player.getPosition().x > _bgWidth - _window.getSize().x / 2)
        _view.setCenter(_bgWidth - _window.getSize().x / 2, _view.getCenter().y);
    
    // Update the text positions
    _updateTextPos();
}

void Game::_updateTextPos() {
    // Should be able to get the text to be positioned at the top of the graphic
    _text.setPosition(10.0f, 0.0f);
}

void Game::_draw() {
    // Clear the window and draw solid color (defaults to black)
    _window.clear(sf::Color(255,255,255,255));///*defaults to black*/);
    
    // Draw the background image
    _drawBackground();
    _drawBGTest();
    
    // TODO: Create different functions for drawing the character, drawing enemies, drawing the onscreen text, and more. For now, everything is in one function
    _drawPlayer();
    
    // Set the default view back for non-moving drawables
    _window.setView(_window.getDefaultView());
    
    // Draw non-moving drawables (text)
    _drawText();

    // Display all items that have been drawn
    _window.display();
}

void Game::_addSprite(const char * file) {
    //Sprite* temp = new Sprite(file);
    //_sprites.push_back(temp);
}

void Game::_drawSprites() {
    /*for (int i = 0; i < _sprites.size(); i++) {
        _window.draw(_sprites[i]->getSprite());
    }*/
}

void Game::_drawPlayer() {
    _window.draw(_player.getSprite());
}

void Game::_drawText() {
    _window.draw(_text);
}

void Game::_drawBackground() {
    // Set the view which moving items will be viewed from
    _window.setView(_view);
    // Draw the background
    _window.draw(_background);
}

void Game::_drawBGTest() {
    for (int i = 0; i < _map.getNumSprites(); i++) {
        _window.draw(_map.getSprite(i));
    }
}
