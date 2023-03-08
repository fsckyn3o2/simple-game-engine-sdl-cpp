#ifndef SIMPLEGAMEENGINE_NAMETABLERENDERER_H
#define SIMPLEGAMEENGINE_NAMETABLERENDERER_H

class BeanManager;
class NameTable;
#include <Core/Renderer/Renderer.h>
#include <SDL2/SDL.h>

class NameTableRenderer: public Renderer {
private:
    BeanManager* beanManager;
    NameTable* nameTable;
    SDL_Texture* texture;
public:
    NameTableRenderer(BeanManager* _beanManager, NameTable* _nameTable): Renderer(), beanManager(_beanManager), nameTable(_nameTable) { };
    void init() override;
    void render() override;
};

#endif //SIMPLEGAMEENGINE_NAMETABLERENDERER_H
