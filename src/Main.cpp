#include <iostream>
#include "Core/BeanManager.h"
#include "Core/Game.h"

/**
 * Load engine before start it.
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {

    BeanManager* beanManager = new BeanManager();
    beanManager->initialize();
    // beanManager->runTest();

    Game* game = new Game(beanManager);
    game->initialize();
    game->start();
    game->clean();

    return 0;
}