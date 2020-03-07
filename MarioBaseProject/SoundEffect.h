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

	static void Load(Mix_Chunk* sound, string path);
	static void Play(int channel, Mix_Chunk* gSoundEffect, int loop);

	//static Mix_Chunk* gSoundEffect;
};