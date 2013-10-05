#include "playablecharacter.h"

PlayableCharacter::PlayableCharacter()
{
    previousState = NONE;
    currentState = NONE;
}

void PlayableCharacter::update(long int elapsed)
{
    Entity::update(elapsed);

    // query controls
    
    // TEMP, C'EST BIN LAID
    // Needs refactor and find a proper way of handling states

    static long int m_timer;
    switch (currentState)
    {
    case NONE:
        // todo: wait for game start
        currentState = TELEPORT;
        m_visible = true;
        break;

    case TELEPORT:
        if (currentState != previousState)
        {
            setCurrentAnimation("teleport");
            m_timer = 0;
            previousState = currentState;
        }

        // temp, should be physic and transition once hits ground
        m_timer += elapsed;
        if (m_timer > 90) currentState = TELEPORT_END;

        break;

    case TELEPORT_END:
        if (currentState != previousState)
        {
            setCurrentAnimation("teleport_end");
            previousState = currentState;
        }

        if (m_animList[m_currentAnim].isCompleted())
        {
            currentState = IDLE;
        }
        break;

    case IDLE:
        if (currentState != previousState)
        {
            setCurrentAnimation("idle");
            m_timer = 0;
            previousState = currentState;
        }

        // if move ...

        // if shoot ...

        // if jump ...

        // if slide ...

        // if long idle
        m_timer += elapsed;
        if (m_timer > 3600) currentState = IDLE_BLINK;

        break;

    case IDLE_BLINK:
        if (currentState != previousState)
        {
            setCurrentAnimation("idle_blink");
            previousState = currentState;
        }

        if (m_animList[m_currentAnim].isCompleted())
        {
            currentState = IDLE;
        }
        break;

    case RUN:
        if (currentState != previousState)
        {
            setCurrentAnimation("run");
            previousState = currentState;
        }

        break;

    case JUMP:

        break;

    case SLIDE:

        break;
    }
}