/**************************************************************************
 *   Copyright (C) 2015 by Carlo Carrano                                  *
 *   crc@dazzlingsolutions.com                                            *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation; version 2 of the License.              *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU     *
 *   General Public License for more details.                             *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program; if not, write to the Free Software          *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  *
 *   USA.  																  *
 **************************************************************************/

/**************************************************************************
 * Change Log                                                             *
 *------------------------------------------------------------------------*
 * 03-17-2015	file created                                              *
 **************************************************************************/

#include "DZsoundSystem.h"

//
// constructor
//
DZsoundSystem::DZsoundSystem()
{
	DZ_LOG(DZ_LOG_TRACE, "Initializing sound system");

	// sound parameters default values
	int			_rate = 22050;
	Uint16		_format = AUDIO_S16;
	int			_channels = 2;
	char		log[256];
	int			log_idx = 0;
	const char*	format_str;
	int			num_chunk_decoders = 4096;

	init();			// loads all the configuration parameters in the
					// class attributes; if configuration data is not
					// available, default values from above will
					// be used

	Mix_Init(-1);	// initialize all codecs available on the system

	if (Mix_OpenAudio(rate, format, channels, chunkSize) == -1)
	{
		DZ_LOG(DZ_LOG_WARN, "Could not open the audio system - Audio will not work");
		isOpen = false;
	}
	else
	{
		isOpen = true;

		// print sound system parameters if log info is enabled

		(void) Mix_QuerySpec(&_rate, &_format, &_channels);
		switch(_format)
		{
			case AUDIO_U8:		format_str = "U8"; break;
			case AUDIO_S8:		format_str = "S8"; break;
			case AUDIO_U16LSB:	format_str = "U16LSB"; break;
			case AUDIO_S16LSB:	format_str = "S16LSB"; break;
			case AUDIO_U16MSB:	format_str = "U16MSB"; break;
			case AUDIO_S16MSB:	format_str = "S16MSB"; break;
			default:			format_str = "Unknown"; break;
		}

		num_chunk_decoders = Mix_GetNumChunkDecoders();


		log_idx = sprintf(log, "\t\t rate               = %d\n"
							   "\t\t format             = %s\n"
							   "\t\t channels           = %d\n"
							   "\t\t number of decoders = %d\n",
					 			_rate,
					 			format_str,
					 			_channels,
					 			num_chunk_decoders);

		for (int i = 0 ; i < num_chunk_decoders ; i++)
		{
			log_idx += sprintf(log+log_idx, "\t\t\t decoder %d = %s\n",
							   i+1, Mix_GetChunkDecoder(i));
		}

		DZ_LOG_STR(DZ_LOG_INFO,
				   "Opened sound system with the following parameters:\n", 
				   log);

		loadSoundEffectList();
		loadMusicList();
	}
}


//
// destructor
//
DZsoundSystem::~DZsoundSystem()
{
	int list_size;
	int i;

	if (isOpen == true)
	{
		list_size = soundEffectList.getSize();
		for (i=0 ; i < list_size ; i++)
		{
			if (soundEffectList[i].effect != 0)
			{
				Mix_FreeChunk(soundEffectList[i].effect);
			}
		}

		Mix_CloseAudio();

		list_size = musicList.getSize();
		for (i=0 ; i < list_size ; i++)
		{
			if (musicList[i].music != 0)
			{
				Mix_FreeMusic(musicList[i].music);
			}
		}

		isOpen = false;
	}
	Mix_Quit();
}

////////////////////////////////////////////////////////////////////////////////////////
// sound effect methods
//

void DZsoundSystem::loadSoundEffectList()
{
	if (isOpen == false)
	{
		DZ_LOG(DZ_LOG_WARN, "Sound system was not initialized");
		return;
	}

	// get the number of sound effects
	int list_size = soundEffectList.getSize();

	// allocate a separate channel for each sound effect, so that
	// we will be able to play any number of them simultaneously (almost)
	(void) Mix_AllocateChannels(list_size);

	// for each sound effect, allocate it in memory and set its own volume,
	// relative to the master volume
	for (int i=0 ; i < list_size ; i++)
	{
		soundEffectList[i].effect = Mix_LoadWAV(soundEffectList[i].filename.c_str());
		if (soundEffectList[i].effect == 0)
		{
			DZ_LOG_STR(DZ_LOG_WARN, "Could not load effect file ", soundEffectList[i].filename.c_str());
		}
		else
		{
			DZ_LOG_STR(DZ_LOG_TRACE, "Loaded effect file ", soundEffectList[i].filename.c_str());

			(void) Mix_VolumeChunk(soundEffectList[i].effect, soundEffectList[i].volume);
		}
	}
}


void DZsoundSystem::setEffectsMasterVolume(int volume)
{
	if (isOpen == true)
	{
		Mix_Volume(-1, volume);
	}
}


void DZsoundSystem::playEffect(unsigned int id, int number_of_loops, int fade_in_msec)
{
	if (isOpen == true)
	{
		if (fade_in_msec == 0)
		{
			Mix_PlayChannel((int) id, soundEffectList[id].effect, number_of_loops);
		}
		else
		{
			Mix_FadeInChannel((int) id, soundEffectList[id].effect, number_of_loops, fade_in_msec);
		}
	}
}



void DZsoundSystem::pauseEffect(unsigned int id)
{
	if (isOpen == true)
	{
		(void) Mix_Pause((int) id);
	}
}



void DZsoundSystem::resumeEffect(unsigned int id)
{
	if (isOpen == true)
	{
		(void) Mix_Resume((int) id);
	}
}


void DZsoundSystem::stopEffect(unsigned int id, int fade_out_msec)
{
	if (isOpen == true)
	{
		if (fade_out_msec == 0)
		{
			(void) Mix_HaltChannel((int) id);
		}
		else
		{
			(void) Mix_FadeOutChannel((int) id, fade_out_msec);
		}
	}
}



bool DZsoundSystem::isEffectPlaying(unsigned int id)
{
	if (isOpen == false)
	{
		return false;
	}
	return (Mix_Playing((int) id) == 1 ? true : false);
}



bool DZsoundSystem::isEffectPaused(unsigned int id)
{
	if (isOpen == false)
	{
		return false;
	}
	return (Mix_Paused((int) id) == 1 ? true : false);
}



////////////////////////////////////////////////////////////////////////////////////////
// music methods
//
void DZsoundSystem::loadMusicList()
{
	if (isOpen == false)
	{
		DZ_LOG(DZ_LOG_WARN, "Sound system was not initialized");
		return;
	}

	// get the number of music pieces
	int list_size = musicList.getSize();

	// for each music piece, allocate it in memory and set its own volume,
	// relative to the master volume
	for (int i=0 ; i < list_size ; i++)
	{
		musicList[i].music = Mix_LoadMUS(musicList[i].filename.c_str());
		if (musicList[i].music == 0)
		{
			DZ_LOG_STR(DZ_LOG_WARN, "Could not load music file ", musicList[i].filename.c_str());
		}
		else
		{
			DZ_LOG_STR(DZ_LOG_TRACE, "Loaded music file ", musicList[i].filename.c_str());
		}
	}
}




void DZsoundSystem::playMusic(unsigned int id, int number_of_loops, int fade_in_msec)
{
	if (isOpen == true)
	{
		(void) Mix_VolumeMusic(musicList[id].volume);

		if (fade_in_msec == 0)
		{
			Mix_PlayMusic(musicList[id].music, number_of_loops);
		}
		else
		{
			Mix_FadeInMusic(musicList[id].music, number_of_loops, fade_in_msec);
		}
	}
}




void DZsoundSystem::pauseMusic()
{
	if (isOpen == true)
	{
		(void) Mix_PauseMusic();
	}
}



void DZsoundSystem::resumeMusic()
{
	if (isOpen == true)
	{
		(void) Mix_ResumeMusic();
	}
}



void DZsoundSystem::stopMusic(int fade_out_msec)
{
	if (isOpen == true)
	{
		if (fade_out_msec == 0)
		{
			(void) Mix_HaltMusic();
		}
		else
		{
			(void) Mix_FadeOutMusic(fade_out_msec);
		}
	}
}



bool DZsoundSystem::isMusicPlaying()
{
	if (isOpen == false)
	{
		return false;
	}
	return (Mix_PlayingMusic() == 1 ? true : false);
}



bool DZsoundSystem::isMusicPaused()
{
	if (isOpen == false)
	{
		return false;
	}
	return (Mix_PausedMusic() == 1 ? true : false);
}



void DZsoundSystem::changeMusicVolume(int volume)
{
	if (isOpen == true)
	{
		Mix_VolumeMusic(volume);
	}
}

////////////////////////////////////////////////////////////////////////////////////////
// configuration from XML file or default
//
void DZsoundSystem::init()
{
}
