#pragma once

struct InputEvents {
    std::vector<SDL_MouseMotionEvent> mouseMotion;
    std::vector<SDL_KeyboardEvent> keyDown;
    std::vector<SDL_QuitEvent> quit;

    void Clear()
    {
        mouseMotion.clear();
        keyDown.clear();
        quit.clear();
    }
};