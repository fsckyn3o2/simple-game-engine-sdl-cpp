#ifndef SIMPLEGAMEENGINE_WAITEVENT_H
#define SIMPLEGAMEENGINE_WAITEVENT_H

#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_events.h>

class WaitEvent {
public:
    typedef struct Param {
        Sint32 code = 0;
        int times = 0; // -1 == indefinitely
    } Param;

    static Uint32 TimerCallback(unsigned int interval, void *param) {

        Param& _param = *(static_cast<Param *>(param));
        interval = _param.times == -1 || --_param.times > 0 ? interval : 0;

        SDL_Event event;
        event.type = SDL_USEREVENT + _param.code;
        event.user.data1 = param;

        SDL_PushEvent(&event);
        return interval;
    }

    static void sleep(unsigned int interval, Param *eventParam) {
        SDL_AddTimer(interval, WaitEvent::TimerCallback, eventParam);
    }
};

#endif //SIMPLEGAMEENGINE_WAITEVENT_H
