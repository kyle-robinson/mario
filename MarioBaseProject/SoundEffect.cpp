#include "SoundEffect.h"

SoundEffect::SoundEffect()
{
	jumpSound = NULL;
}

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(jumpSound);
	jumpSound = NULL;
}

void SoundEffect::Load()
{
	jumpSound = Mix_LoadWAV("Music/WAV/Jump.wav");
	if (jumpSound == NULL)
	{
		cout << "Failed to load sound effect! Error: " << Mix_GetError() << endl;
	}
}

void SoundEffect::Play(int channel, Mix_Music* sound, int loop)
{
	Mix_PlayMusic(sound, loop);
}