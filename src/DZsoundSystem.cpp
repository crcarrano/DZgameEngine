/**************************************************************************
 *   Copyright (C) 2015 by Carlo Carrano                                  *
 *   crc@dazzlingsolutions.com                                            *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU Lesser General Public License as       *
 *   published by the Free Software Foundation; version 3 of the License. *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU     *
 *   Lesser General Public License for more details.                      *
 *   You should have received a copy of the Lesser GNU General Public     *
 *   License along with this program; if not, write to the Free Software  *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  *
 *   USA.  																  *
 **************************************************************************/

/**************************************************************************
 * Change Log                                                             *
 *------------------------------------------------------------------------*
 * 05-21-2015	modified distribution license                             *
 * 03-17-2015	file created                                              *
 **************************************************************************/

#include "DZsoundSystem.h"
#include "DZproject.h"
#include "DZxmlParser.h"

//
// constructor
//
DZsoundSystem::DZsoundSystem()
{
	DZ_LOG(DZ_LOG_TRACE, "Initializing sound system");

	int			_rate;
	Uint16		_format;
	int			_channels;
	int			num_chunk_decoders;
	char		log[256];
	int			log_idx = 0;
	const char*	format_str;

	soundEffectListPtr = new DZarray<SOUND_EFFECT*>;
	musicListPtr = new DZarray<MUSIC_PIECE*>;

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

		loadSoundEffectList();
		loadMusicList();
	}

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


	log_idx = sprintf(log, "\t rate               = %d\n"
						   "\t\t format             = %s\n"
						   "\t\t channels           = %d\n"
						   "\t\t number of decoders = %d",
				 			_rate,
				 			format_str,
				 			_channels,
				 			num_chunk_decoders);

	for (int i = 0 ; i < num_chunk_decoders ; i++)
	{
		log_idx += sprintf(log+log_idx, "\n\t\t  decoder %d = %s",
						   i+1, Mix_GetChunkDecoder(i));
	}

	DZ_LOG_STR(DZ_LOG_INFO,
			   "Opened sound system with the following parameters:\n", 
			   log);
}


//
// destructor
//
DZsoundSystem::~DZsoundSystem()
{
	int list_size;
	int i;

	DZ_LOG(DZ_LOG_TRACE, "Terminating sound system");

	if (isOpen == true)
	{
		list_size = soundEffectListPtr->getSize();
		for (i=0 ; i < list_size ; i++)
		{
			if ((*soundEffectListPtr)[i] != 0)
			{
				if ((*soundEffectListPtr)[i]->effect != 0)
				{
					Mix_FreeChunk((*soundEffectListPtr)[i]->effect);
				}
				delete (*soundEffectListPtr)[i];
			}
		}
		delete soundEffectListPtr;

		Mix_CloseAudio();

		list_size = musicListPtr->getSize();
		for (i=0 ; i < list_size ; i++)
		{
			if ((*musicListPtr)[i] != 0)
			{
				if ((*musicListPtr)[i]->music != 0)
				{
					Mix_FreeMusic((*musicListPtr)[i]->music);
				}
				delete (*musicListPtr)[i];
			}
		}
		delete musicListPtr;

		isOpen = false;
	}
	Mix_Quit();
}

////////////////////////////////////////////////////////////////////////////////////////
// sound effect methods
//

bool DZsoundSystem::isEffectAvailable(unsigned int id)
{
	if ((*soundEffectListPtr)[id] != 0)
	{
		return true;
	}
	return false;
}

void DZsoundSystem::loadSoundEffectList()
{
	if (isOpen == false)
	{
		DZ_LOG(DZ_LOG_WARN, "Sound system was not initialized");
		return;
	}

	// get the number of sound effects
	int list_size = soundEffectListPtr->getSize();

	// allocate a separate channel for each sound effect, so that
	// we will be able to play any number of them simultaneously (almost)
	(void) Mix_AllocateChannels(list_size);

	// for each sound effect, allocate it in memory and set its own volume,
	// relative to the master volume
	for (int i=0 ; i < list_size ; i++)
	{
		if ((*soundEffectListPtr)[i] == 0)
		{
			continue;
		}
		(*soundEffectListPtr)[i]->effect = Mix_LoadWAV((*soundEffectListPtr)[i]->filename.c_str());
		if ((*soundEffectListPtr)[i]->effect == 0)
		{
			DZ_LOG_STR(DZ_LOG_WARN, "Could not load effect file ", (*soundEffectListPtr)[i]->filename.c_str());
		}
		else
		{
			DZ_LOG_STR(DZ_LOG_TRACE, "Loaded effect file ", (*soundEffectListPtr)[i]->filename.c_str());

			(void) Mix_VolumeChunk((*soundEffectListPtr)[i]->effect, (*soundEffectListPtr)[i]->volume);
		}
	}
}


void DZsoundSystem::setEffectsMasterVolume(int volume)
{
	if (isOpen == true)
	{
		for (int i=0 ; i < channels ; i++)
		{
			Mix_Volume(i, volume);
		}
	}
}


void DZsoundSystem::playEffect(unsigned int id, int number_of_loops, int fade_in_msec)
{
	if (isOpen == true)
	{
		if (fade_in_msec == 0)
		{
			Mix_PlayChannel((int) id, (*soundEffectListPtr)[id]->effect, number_of_loops);
		}
		else
		{
			Mix_FadeInChannel((int) id, (*soundEffectListPtr)[id]->effect, number_of_loops, fade_in_msec);
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
bool DZsoundSystem::isMusicAvailable(unsigned int id)
{
	if ((*musicListPtr)[id] != 0)
	{
		return true;
	}
	return false;
}

void DZsoundSystem::loadMusicList()
{
	if (isOpen == false)
	{
		DZ_LOG(DZ_LOG_WARN, "Sound system was not initialized");
		return;
	}

	// get the number of music pieces
	int list_size = musicListPtr->getSize();

	// for each music piece, allocate it in memory and set its own volume,
	// relative to the master volume
	for (int i=0 ; i < list_size ; i++)
	{
		if ((*musicListPtr)[i] == 0)
		{
			continue;
		}
		(*musicListPtr)[i]->music = Mix_LoadMUS((*musicListPtr)[i]->filename.c_str());
		if ((*musicListPtr)[i]->music == 0)
		{
			DZ_LOG_STR(DZ_LOG_WARN, "Could not load music file ", (*musicListPtr)[i]->filename.c_str());
		}
		else
		{
			DZ_LOG_STR(DZ_LOG_TRACE, "Loaded music file ", (*musicListPtr)[i]->filename.c_str());
		}
	}
}




void DZsoundSystem::playMusic(unsigned int id, int number_of_loops, int fade_in_msec)
{
	if (isOpen == true)
	{
		if (fade_in_msec == 0)
		{
			Mix_PlayMusic((*musicListPtr)[id]->music, number_of_loops);
		}
		else
		{
			Mix_FadeInMusic((*musicListPtr)[id]->music, number_of_loops, fade_in_msec);
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
	unsigned int id;
	string fname;

	DZ_LOG(DZ_LOG_TRACE, "...entering...");
	
	// initialize default values
	rate = 22050;
	format = MIX_DEFAULT_FORMAT;
	channels = 2;
	chunkSize = 4096;

	// read configuration file
	DZxmlParser	doc(DZCONFIGFILE);

	// read sound element
	if (doc.getSound() == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "Cannot read sound system configuration; using defaults");
		return;
	}

	// get sound system configuration parameters
	rate = doc.getSoundSample();
	format = doc.getSoundFormat();
	channels = doc.getSoundChannels();
	chunkSize = doc.getSoundChunks();

	DZ_LOG(DZ_LOG_TRACE, "Reading music elements");

	// set intro music soundtrack, defined in DZproject.h
	if (DZ_INTRO_AVAILABLE)
	{
		(*musicListPtr)[0] = new MUSIC_PIECE;
		fname.assign(DZ_INTRO_MUSIC_FILE);
		(*musicListPtr)[0]->filename = fname;
	}
	else
	{
		(*musicListPtr)[0] = 0;
	}

	if (doc.getMusic() == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "Cannot read music list");
	}
	else
	{
		// set music volume
		changeMusicVolume((int)doc.getMusicVolume());

		// read and store music list
		if (doc.getFirstPiece() == 0)
		{
			DZ_LOG(DZ_LOG_WARN, "Cannot read music piece");
		}
		else
		{
			do
			{
				id = doc.getPieceID();
				(*musicListPtr)[id] = new MUSIC_PIECE;
				fname.assign(doc.getPieceFilename());
				DZ_LOG_STR(DZ_LOG_TRACE, "Storing Music Piece filename: ", fname.c_str());
				(*musicListPtr)[id]->filename = fname;
			} while (doc.getNextPiece() != 0);
		}
	}

	DZ_LOG(DZ_LOG_TRACE, "Reading sound effect elements");

	if (doc.getEffects() == 0)
	{
		DZ_LOG(DZ_LOG_WARN, "Cannot read sound effects list");
	}
	else
	{
		// set sound effects master volume
		setEffectsMasterVolume((int)doc.getEffectMasterVolume());

		// read and store sound effects list
		if (doc.getFirstEffect() == 0)
		{
			DZ_LOG(DZ_LOG_WARN, "Cannot read sound effect");
		}
		else
		{
			do
			{
				id = doc.getEffectID();
				(*soundEffectListPtr)[id] = new SOUND_EFFECT;
				(*soundEffectListPtr)[id]->volume = doc.getEffectVolume();
				fname.assign(doc.getEffectFilename());
				DZ_LOG_STR(DZ_LOG_TRACE, "Storing Sound Effect filename: ", fname.c_str());
				(*soundEffectListPtr)[id]->filename = fname;
			} while (doc.getNextEffect() != 0);
		}
	}
}
