#pragma once

#include "stdafx.h"
#include "entity.h"

enum CharacterState {NONE, TELEPORT, TELEPORT_END, IDLE, IDLE_BLINK, RUN, JUMP, SLIDE};

class PlayableCharacter : public Entity
{
public:
    PlayableCharacter();

    virtual void update(long int elapsed);

private:

    CharacterState previousState;
    CharacterState currentState;
};