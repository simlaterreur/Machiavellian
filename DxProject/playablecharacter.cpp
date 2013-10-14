#include "playablecharacter.h"

PlayableCharacter::PlayableCharacter()
{
    m_currentState = NONE;
    m_previousState = NONE;

}

void PlayableCharacter::Update(long int elapsed)
{
    Entity::Update(elapsed); // base class update, takes care of animation

    // query controls
    m_previousInputs = m_currentInputs;
    ControlManager::getInstance().QueryInputs(m_currentInputs);

    // TEMP, C'EST BIN LAID
    // Needs refactor and find a proper way of handling states

    static long int m_timer;
    switch (m_currentState)
    {
    case NONE:
        // todo: wait for game start
        m_currentState = TELEPORT;
        m_visible = true;
        break;

    case TELEPORT:
        if (m_currentState != m_previousState)
        {
            SetCurrentAnimation("teleport");
            m_timer = 0;
            m_previousState = m_currentState;
        }

        // temp, should be physic and transition once hits ground
        m_timer += elapsed;
        if (m_timer > 90) m_currentState = TELEPORT_END;

        break;

    case TELEPORT_END:
        if (m_currentState != m_previousState)
        {
            SetCurrentAnimation("teleport_end");
            m_previousState = m_currentState;
        }

        if (m_animList[m_currentAnim].Completed())
        {
            m_currentState = IDLE;
        }
        break;

    case IDLE:
        if (m_currentState != m_previousState)
        {
            SetCurrentAnimation("idle");
            m_timer = 0;
            m_previousState = m_currentState;
        }

        // if long idle
        m_timer += elapsed;
        if (m_timer > 3600) m_currentState = IDLE_BLINK;

        // if move ...
        if (m_currentInputs.left || m_currentInputs.right)
        {
            m_currentState = RUN;
        }

        // if slide ...
        if (m_currentInputs.down && (m_currentInputs.a && !m_previousInputs.a))
        {
            m_currentState = SLIDE;
        }

        // if shoot ...

        // if jump ...
        if (!m_currentInputs.down && (m_currentInputs.a && !m_previousInputs.a))
        {
            m_currentState = JUMP;
        }

        break;

    case IDLE_BLINK:
        if (m_currentState != m_previousState)
        {
            SetCurrentAnimation("idle_blink");
            m_previousState = m_currentState;
        }

        if (m_animList[m_currentAnim].Completed())
        {
            m_currentState = IDLE;
        }

        // if move ...
        if (m_currentInputs.left || m_currentInputs.right)
        {
            m_currentState = RUN;
        }

        // if slide ...
        if (m_currentInputs.down && (m_currentInputs.a && !m_previousInputs.a))
        {
            m_currentState = SLIDE;
        }

        // if shoot ...

        // if jump ...
        if (!m_currentInputs.down && (m_currentInputs.a && !m_previousInputs.a))
        {
            m_currentState = JUMP;
        }

        break;

    case RUN:
        if (m_currentState != m_previousState)
        {
            SetCurrentAnimation("run");
            m_previousState = m_currentState;
        }

        if (m_currentInputs.left)
        {
            MoveLeft(elapsed, MOVE_SPEED);
        }
        else if (m_currentInputs.right)
        {
            MoveRight(elapsed, MOVE_SPEED);
        }
        else
        {
            m_currentState = IDLE;
        }

        // if slide ...
        if (m_currentInputs.down && (m_currentInputs.a && !m_previousInputs.a))
        {
            m_currentState = SLIDE;
        }

        // if jump ...
        if (!m_currentInputs.down && (m_currentInputs.a && !m_previousInputs.a))
        {
            m_currentState = JUMP;
        }

        break;

    case JUMP: // should be called AIR
        if (m_currentState != m_previousState)
        {
            SetCurrentAnimation("air");
            m_previousState = m_currentState;
            m_jumpImpulsion = JUMP_IMPULSION_VALUE; // should be assigned on the transition ? What about falling
        }

        if (!m_currentInputs.a && m_jumpImpulsion > 0)
        {
            m_jumpImpulsion = 0;
        }

        if (m_currentInputs.left)
        {
            MoveLeft(elapsed, MOVE_SPEED);
        }
        else if (m_currentInputs.right)
        {
            MoveRight(elapsed, MOVE_SPEED);
        }

        if (!MoveUpDown(elapsed))
        {
            m_currentState = IDLE;
        }

        break;

    case SLIDE:
        if (m_currentState != m_previousState)
        {
            SetCurrentAnimation("slide");
            m_timer = 0;
            m_previousState = m_currentState;
        }

        m_timer += elapsed;
        if (m_timer > SLIDE_TIME) m_currentState = IDLE;

        if (m_currentInputs.left)
        {
            MoveLeft(elapsed, SLIDE_SPEED);
        }
        else if (m_currentInputs.right)
        {
            MoveRight(elapsed, SLIDE_SPEED);
        }
        else if (m_facingLeft)
        {
            MoveLeft(elapsed, SLIDE_SPEED);
        }
        else
        {
            MoveRight(elapsed, SLIDE_SPEED);
        }

        // if jump ...
        if (!m_currentInputs.down && (m_currentInputs.a && !m_previousInputs.a))
        {
            m_currentState = JUMP;
        }

        break;
    }
}

void PlayableCharacter::MoveLeft(long int elapsed, float speed)
{
    m_facingLeft = true;
    m_pos.first -= elapsed * speed;
}

void PlayableCharacter::MoveRight(long int elapsed, float speed)
{
    m_facingLeft = false;
    m_pos.first += elapsed * speed;
}

bool PlayableCharacter::MoveUpDown(long int elapsed)
{
    m_pos.second -= elapsed * m_jumpImpulsion;
    m_jumpImpulsion -= elapsed * JUMP_GRAVITY_VALUE;
    if (m_jumpImpulsion < -JUMP_IMPULSION_VALUE)
    {
        m_jumpImpulsion = -JUMP_IMPULSION_VALUE;
    }

    // faked collision
    if (m_pos.second >= 192)
    {
        m_pos.second = 192;
        return false;
    }

    return true;
}