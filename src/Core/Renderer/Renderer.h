#ifndef SIMPLEGAMEENGINE_RENDERER_H
#define SIMPLEGAMEENGINE_RENDERER_H

class Renderer {
public:
    Renderer() = default;
    virtual void init() = 0;
    virtual void render() = 0;
    // TODO Add a constant to store screen resolution used by renderer(s)
};


#endif //SIMPLEGAMEENGINE_RENDERER_H
