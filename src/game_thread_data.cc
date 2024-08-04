#include <SDL2/SDL.h>
#include "soo/soo_exception.h"
#include "soo/soo_command.h"
#include "game_thread_data.h"

GameThreadData::GameThreadData():
    renderUpdate(0),gameSpeed(1000){
    m_mutex=SDL_CreateMutex();
    THROW_SDL_NULL(m_mutex)
    m_cond=SDL_CreateCond();
    THROW_SDL_NULL(m_cond)
}
GameThreadData::~GameThreadData()
{
    SDL_DestroyMutex(m_mutex);
    SDL_DestroyCond(m_cond);
}
int GameThreadData::excuteMutex(SooCommand *cmd,void *data)
{
    int res=0;
    SDL_LockMutex(m_mutex);
    res=cmd->execute(data);
    SDL_UnlockMutex(m_mutex);
    return res;

}
