#include "Game.h"

Game::Game* gameInstance = nullptr;

Game::Game* Game::Game::getGameInstance() {
  return gameInstance;
}

