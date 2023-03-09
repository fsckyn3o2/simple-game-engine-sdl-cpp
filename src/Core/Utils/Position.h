#ifndef SIMPLE_GAME_ENGINE_POSITION_H
#define SIMPLE_GAME_ENGINE_POSITION_H

#include <iostream>
#include <algorithm>
#include <SDL2/SDL.h>

class PositionMapper;

class Pos {
public:
    int x;
    int y;

    Pos(int _x, int _y) : x(_x), y(_y) { }

    [[nodiscard]] Pos offset(int oX, int oY) const {
        return Pos{x + oX, y + oY};
    }

    bool operator==(Pos* other) const { return x == other->x && y == other->y; }
    bool operator==(Pos other) const { return x == other.x && y == other.y; }

    bool operator!=(Pos* other) const { return (x != other->x) || (y != other->y); }
    bool operator<(Pos* other) const { return (x < other->x) && (y < other->y); }
    bool operator<=(Pos* other) const { return (x <= other->x) && (y <= other->y); }
    bool operator>=(Pos* other) const { return (x >= other->x) || (y >= other->y); }
    bool operator>(Pos* other) const { return (x > other->x) || (y > other->y); }

    bool operator!=(Pos other) const { return (x != other.x) || (y != other.y); }
    bool operator<(Pos other) const { return (x < other.x) && (y < other.y); }
    bool operator<=(Pos other) const { return (x <= other.x) && (y <= other.y); }
    bool operator>=(Pos other) const { return (x >= other.x) || (y >= other.y); }
    bool operator>(Pos other) const { return (x > other.x) || (y > other.y); }

    Pos* operator+() const { return new Pos(abs(x), abs(y)); }
    Pos* operator+(Pos* other) const { return new Pos(x+other->x, y+other->y); }
    Pos operator+(Pos other) const { return Pos{x+other.x, y+other.y}; }

    Pos* operator-() const { return new Pos(-x, -y); }
    Pos* operator-(Pos* other) const { return new Pos(x-other->x, y-other->y); }
    Pos operator-(Pos other) const { return Pos{x-other.x, y-other.y}; }

    Pos operator*(int factor) const { return Pos{ x*factor, y*factor}; }
    Pos operator*(Pos other) const { return Pos{ x*other.x, y*other.y}; }
};

class Position : public Pos {
public:
    Pos origin;
    Position(): Pos(0,0), origin(0,0) { }
    Position(int _x, int _y): Pos(_x, _y), origin(Pos{ 0, 0}) { }
    Position(int _x, int _y, int _oX, int _oY) : Pos(_x, _y), origin(Pos{ _oX, _oY }) { }

    int xAbs() { return origin.x + x; }
    int yAbs() { return origin.y + y; }

    Pos absolute() { return Pos{ xAbs(), yAbs() }; }

    bool operator==(Position* other) { return xAbs() == other->xAbs() && yAbs() == other->yAbs(); }
    bool operator!=(Position* other) { return xAbs() != other->xAbs() || yAbs() != other->yAbs(); }
    bool operator<(Position* other) { return xAbs() < other->xAbs() && yAbs() < other->yAbs(); }
    bool operator<=(Position* other) { return xAbs() <= other->xAbs() && yAbs() <= other->yAbs(); }
    bool operator>=(Position* other) { return xAbs() >= other->xAbs() || yAbs() >= other->yAbs(); }
    bool operator>(Position* other) { return xAbs() >= other->xAbs() || yAbs() >= other->yAbs(); }

    Position* operator+(Pos* other) { return new Position(x+other->x, y+other->y, origin.x, origin.y); }
    Position* operator-(Pos* other) { return new Position(x-other->x, y-other->y, origin.x, origin.y); }
    Position operator+(Pos other) { return Position{x+other.x, y+other.y, origin.x, origin.y}; }
    Position operator-(Pos other) { return Position{x-other.x, y-other.y, origin.x, origin.y}; }

    Position operator+(Position* other) {
        if (other->origin == origin) {
            return Position{x+other->x, y+other->y, origin.x, origin.y};
        } else {
            // Select origin of this (origin > other->origin then ), (origin < other origin then ).
            Pos offset = absolute() - other->origin;
            return Position{ x+offset.x, y+offset.y, origin.x, origin.y};
        }
    }

    Position operator+(Position other) {
        if (other.origin == origin) {
            return Position{x+other.x, y+other.y, origin.x, origin.y};
        } else {
            // Select origin of this (origin > other->origin then ), (origin < other origin then ).
            Pos offset = absolute() - other.origin;
            return Position{ x+offset.x, y+offset.y, origin.x, origin.y};
        }
    }

    Position operator-(Position* other) {
        if (other->origin == origin) {
            return Position{x-other->x, y-other->y, origin.x, origin.y};
        } else {
            // Select origin of this (origin > other->origin then ), (origin < other origin then ).
            Pos offset = absolute() - other->origin;
            return Position{ x-offset.x, y-offset.y, origin.x, origin.y};
        }
    }
    Position operator-(Position other) {
        if (other.origin == origin) {
            return Position{x-other.x, y-other.y, origin.x, origin.y};
        } else {
            // Select origin of this (origin > other->origin then ), (origin < other origin then ).
            Pos offset = absolute() - other.origin;
            return Position{ x-offset.x, y-offset.y, origin.x, origin.y};
        }
    }
};

class WorkerPosition {
public:
    Position FROM; Pos OFFSET; Position LAST;
    Position current;
    int currentIndex = 0;
    const unsigned int size;

    /**
     * FROM start position
     * OFFSET addition or subtraction from start position to LAST
     * LAST end of list of position between FROM to LAST and stepped by OFFSET :
     *      LAST has same origin of FROM
     * @param _from
     * @param _offset
     * @param _size
     */
    WorkerPosition(Position _from, Pos _offset, unsigned int _size): FROM(_from), OFFSET(_offset), size(_size),
        LAST(Position{ (int) (OFFSET.x * _size), (int) (OFFSET.y * _size), _from.origin.x, _from.origin.y }) { }

    bool hasNext() const { return currentIndex < size && currentIndex >= 0 || currentIndex == -1; }

    void next() { currentIndex++; current = current + OFFSET; }
    void previous() { currentIndex--; current = current - OFFSET; }

    Position cbegin() const { return FROM; }
    Position cend() const { return LAST; }
    Position get(int index) { return index >= 0 && index < size ? (FROM + (OFFSET*index)) : LAST; }

    void resetToEnd() { currentIndex = size; current = LAST; };
    void resetToBegin() { currentIndex = -1; current = FROM - OFFSET; };

};

class Rect {
public:
    const int x, y;
    const int w, h;

    SDL_Rect const* sdl = nullptr;

    Rect(int _x, int _y, int _w, int _h): x(_x), y(_y), w(_w), h(_h) { }

    Pos* position() {
        return new Pos(x, y);
    }

    Pos* size() {
        return new Pos(w, h);
    }

    SDL_Rect const* refreshSdlValue() {
        delete sdl;
        sdl =  new SDL_Rect {  x,  y,  w,  h };
        return sdl;
    }

    /**
     * Return rectangle with an absolute position from this rectangle and relative offset in parameter.
     * @param _pos
     * @param _size
     * @return new rectangle
     */
    Rect* relativeZone(Pos* _pos, Pos* _size = nullptr) {
        return new Rect{x+_pos->x, y+_pos->y, (_size == nullptr ? w : _size->x), (_size == nullptr ? h : _size->y)};
    }

    /**
     * Multiply width and height by a factor.
     * @param factor
     * @return new rectangle
     */
    Rect* scale(float factor) const {
        return new Rect(x, y, w*factor, h*factor);
    }

    /**
     * Generate new rectangle INSIDE this with padding value with absolute centered position.
     * @param size
     * @return nullptr if _padding is greater than height or width
     */
    Rect* padding(unsigned int _padding) {
        unsigned int padding = _padding*2;
        if (padding > w || padding > h) padding = 0;
        return center(new Rect(x, y, w-padding, h-padding));
    }

    /**
     * Generate new rectangle INSIDE this with padding value with RELATIVE centered position.
     * @param size
     * @return nullptr if _padding is greater than height or width
     */
    Rect* relativePadding(unsigned int _padding) {
        unsigned int padding = _padding*2;
        if (padding > w || padding > h) padding = 0;
        Rect *res = center(new Rect(x, y, w-padding, h-padding));
        return res->relativeZone(new Pos(-x, -y), nullptr);
    }

    Rect* paddingLeftRight(int _padding) {
        unsigned int padding = _padding*2;
        if (padding > w) padding = 0;
        return center(new Rect(x, y, w-padding, h));
    }

    Rect* paddingTopBottom(int _padding) {
        unsigned int padding = _padding*2;
        if (padding > h) padding = 0;
        return center(new Rect(x, y, w, h-padding));
    }

    Rect* centerScale(float factor) {
        return center(scale(factor));
    }

    Rect* center(Rect* rect) {
        return relativeZone(new Pos((w - rect->w)/2, (h - rect->h)/2), rect->size());
    }

};

class PositionMapper {
public:
    static Rect const* sdl2rect(SDL_Rect *rect) {
        return new Rect(rect->x, rect->y, rect->w, rect->h);
    }
};


static Pos const POS_ZERO = Pos{0, 0};


#endif //SIMPLE_GAME_ENGINE_POSITION_H
