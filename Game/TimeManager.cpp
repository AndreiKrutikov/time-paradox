#include "TimeManager.h"
#include "Acts.h"
#include "Player.h"
#include "Components\Movable.h"

using namespace Engine;

Game::TimeManager::TimeManager(EntityComponentSystem::Entity e, Player& player) : timeSpeed(1), e(e), outatime(false), disappeared (false), player(player) {
  e.addComponent<Engine::Interactible>(this);
  e.activate();
  firstUnexecutedAct = timeline.begin();
  checkPoint();
  auto ptr2 = new SpawnAct;
  ptr2->timestamp = getGameTime();
  ptr2->entity = player.e;
  ptr2->position = player.e.getComponent<Movable>().position;
  player.e.addComponent<Interactible>(&player);
  player.e.activate();
  firstUnexecutedAct = timeline.insert(firstUnexecutedAct, std::move(std::unique_ptr<Act>(ptr2)));
  firstUnexecutedAct++;
}

void Game::TimeManager::checkPoint() {
  realtimeOrigin = std::chrono::high_resolution_clock::now();
}

#include <iostream>

void Game::TimeManager::onKeyEvent(sf::Event::KeyEvent ev, bool pressed) {
  if (pressed) {
    if (ev.code == sf::Keyboard::Space) {
      if (timeSpeed != 0) {
        outatime = true;
        gameTimeOrigin = getGameTime();
        checkPoint();
        timeSpeed = 0;
      } else {
        if (disappeared) {
          auto ptr2 = new SpawnAct;
          ptr2->timestamp = getGameTime();
          ptr2->entity = player.e;
          ptr2->position = player.e.getComponent<Movable>().position;
          player.e.addComponent<Interactible>(&player);
          player.e.activate();
          firstUnexecutedAct = timeline.insert(firstUnexecutedAct, std::move(std::unique_ptr<Act>(ptr2)));
          firstUnexecutedAct++;
          disappeared = false;
        }

        outatime = false;
        checkPoint();
        timeSpeed = 1;
      }
    }

    if (ev.code == sf::Keyboard::Subtract || ev.code == sf::Keyboard::Dash) {
      if (outatime) {
        if (!disappeared) {//create clone
          auto ptr = new DisappearAct;
          ptr->entity = player.createClone();
          ptr->timestamp = getGameTime();
          firstUnexecutedAct = timeline.insert(firstUnexecutedAct, std::move(std::unique_ptr<Act>(ptr)));
          disappeared = true;
        }

        gameTimeOrigin = getGameTime();
        checkPoint();
        timeSpeed--;
      }
    }

    if (ev.code == sf::Keyboard::Add || ev.code == sf::Keyboard::Equal) {
      if (outatime) {
        if (!disappeared) {
          auto ptr = new DisappearAct;
          ptr->entity = player.createClone();
          ptr->timestamp = getGameTime();
          firstUnexecutedAct = timeline.insert(firstUnexecutedAct, std::move(std::unique_ptr<Act>(ptr)));
          disappeared = true;
        }

        gameTimeOrigin = getGameTime();
        checkPoint();
        timeSpeed++;
      }
    }
  }
}

std::chrono::time_point<std::chrono::high_resolution_clock> Game::TimeManager::getGameTime() {
  return gameTimeOrigin + (std::chrono::high_resolution_clock::now() - realtimeOrigin) * timeSpeed;
}

int64_t Game::TimeManager::getTimeMultiplier() const {
  return timeSpeed;
}

void Game::TimeManager::addAndExecuteAct(std::unique_ptr<Act> act) {
  if (!outatime) {
    if (act->execute()) {
      act->timestamp = getGameTime();
      firstUnexecutedAct = timeline.insert(firstUnexecutedAct, std::move(act));
      firstUnexecutedAct++;
    }
  }
}

bool Game::TimeManager::update() {
  auto currentTime = getGameTime();
  if (timeSpeed > 0) {
    while (firstUnexecutedAct != timeline.end() && firstUnexecutedAct->get()->timestamp <= currentTime) {
      bool success = firstUnexecutedAct->get()->execute();
      if (!success) return false; //TimeParadox
      firstUnexecutedAct++;
    }
  }
  
  if (timeSpeed < 0) {
    for (;;) {
      if (firstUnexecutedAct == timeline.begin()) break;
      firstUnexecutedAct--;
      if (firstUnexecutedAct->get()->timestamp >= currentTime) {
        firstUnexecutedAct->get()->unexecute();
      } else {
        firstUnexecutedAct++;
        break;
      }
    }
  }

  return true;
}
