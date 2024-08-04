#pragma once
class SDL_mutex;
class SDL_cond;
class GameData;
class SooCommand;
class GameThreadData{
private:
    SDL_mutex *m_mutex;
    SDL_cond  *m_cond;
public:
    int        renderUpdate;
    int        gameSpeed;
    GameData  *gameData;
    GameThreadData();
    virtual ~GameThreadData();
    int excuteMutex(SooCommand *,void *);
};