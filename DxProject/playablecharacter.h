#pragma once

#include "stdafx.h"
#include "entity.h"
#include "controlmanager.h"

static const float MOVE_SPEED = 0.096f; // (96.0f / 1000.0f) pixels per second
static const float SLIDE_SPEED = 0.192f; // (192.0f / 1000.0f) pixels per second
static const long int SLIDE_TIME = 400; 

static const float JUMP_IMPULSION_VALUE = 0.4f; 
static const float JUMP_GRAVITY_VALUE = 0.0015f;

class PlayableCharacter : public Entity
{
public:
    PlayableCharacter();

    virtual void Update(long int);

private:
    enum CharacterState {NONE, TELEPORT, TELEPORT_END, IDLE, IDLE_BLINK, RUN, JUMP, SLIDE};
    CharacterState m_currentState;
    CharacterState m_previousState;

    ControllerState m_currentInputs;
    ControllerState m_previousInputs;

    float m_jumpImpulsion;

    void MoveLeft(long int, float);
    void MoveRight(long int, float);

    bool MoveUpDown(long int);
   
};