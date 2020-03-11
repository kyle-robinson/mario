#pragma once

#include <string>
#include <iostream>
#include <SDL_mixer.h>

using namespace std;

class SoundEffect
{
public:
	SoundEffect();
	~SoundEffect();

	void Load();
	void Play(int channel, Mix_Music* gSoundEffect, int loop);

	Mix_Chunk* jumpSound;
};