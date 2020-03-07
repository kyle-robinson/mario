#include "SoundEffect.h"

SoundEffect::SoundEffect()
{
	gSoundEffect = NULL;
}

SoundEffect::~SoundEffect()
{
	Mix_FreeMusic(gSoundEffect);
	gSoundEffect = NULL;
}

void SoundEffect::Load(Mix_Music* sound, string path)
{
	sound = Mix_LoadMUS(path.c_str());
	if (sound == NULL)
	{
		cout << "Failed to load sound effect! Error: " << Mix_GetError() << endl;
	}
}

void SoundEffect::Play(int channel, Mix_Music* sound, int loop)
{
	Mix_PlayMusic(sound, loop);
}