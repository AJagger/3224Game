/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* This class is the class used to integrate WWise audio with the game engine
* 
* The class is entirely commented out since I never fully got it working. I have left it in to show some of the progress and possibly to come back to in the future.
*/

#include "stdafx.h"
#include "Sound.h"
/* commented out for now
#include <cassert>
//#include "AK/AkPlatforms.h"
//#include "AK/AkWwiseSDKVersion.h"
//#include <AK/SoundEngine/Common/AkMemoryMgr.h>
//#include <AK/SoundEngine/Common/AkModule.h>
//#include <cassert>
//#include <AK/SoundEngine/Common/IAkStreamMgr.h>                 // Streaming Manager
//#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
//#include <AK/MusicEngine/Common/AkMusicEngine.h> 
//#include <AK/SoundEngine/Common/AkSoundEngine.h>
//#include <AK/SoundEngine/Common/AkTypes.h>
//#include <AK/SoundEngine/Common/AkSoundEngineExport.h>
//#include <AK/IBytes.h>
//#include <AK/SoundEngine/Platforms/Windows/AkTypes.h>
//#include <AK/SoundEngine/Platforms/Windows/AkSimd.h>
//#include <AK/SoundEngine/Platforms/Windows/AkWinSoundEngine.h>
#include "C:\\Program Files (x86)\\Audiokinetic\\Wwise 2016.2.3.6077\\SDK\\samples\\SoundEngine\\Win32\\AkFilePackageLowLevelIOBlocking.h"
#include <AK/SoundEngine/Common/AkMemoryMgr.h>                  // Memory Manager
#include <AK/SoundEngine/Common/AkModule.h>                     // Default memory and stream managers
#include <AK/SoundEngine/Common/IAkStreamMgr.h>                 // Streaming Manager
#include <AK/Tools/Common/AkPlatformFuncs.h>                    // Thread defines
#include <AK/SoundEngine/Common/AkSoundEngine.h>				// Sound Engine
#include <AK/MusicEngine/Common/AkMusicEngine.h>                // Music Engine
#include <AK/SoundEngine/Common/AkTypes.h>
#include <AK/SoundEngine/Common/AkSoundEngineExport.h>

*/

Sound::Sound()
{
}


Sound::~Sound()
{
}

bool Sound::InitSoundEngine()
{
	/* Commented out for now
	//Initialise Memory Manager
	AkMemSettings memSettings;
	memSettings.uMaxNumPools = 20;

	if(AK::MemoryMgr::Init(&memSettings) != AK_Success)
	{
		assert(!"Could not create the WWise memory manager.");
		return false;
	}

	////Initialise Streaming Manager
	//AkStreamMgrSettings stmSettings;
	//AK::StreamMgr::GetDefaultSettings(stmSettings);

	//if (!AK::StreamMgr::Create(stmSettings))
	//{
	//	assert(!"Could not create the WWise Streaming Manager");
	//	return false;
	//}

	////Create Streaming Device
	//AkDeviceSettings deviceSettings;
	//AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

	//if (g_lowLevelIO.Init(deviceSettings) != AK_Success)
	//{
	//	assert(!"Could not create the streaming device and Low-Level I/O system");
	//	return false;
	//}

	////Create Sound Engine
	//AkInitSettings initSettings;
	//AkPlatformInitSettings platformInitSettings;

	//AK::SoundEngine::GetDefaultInitSettings(initSettings);
	//AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

	//if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
	//{
	//	assert(!"Could not initialize the WWise Sound Engine.");
	//	return false;
	//}

	////Initialise Music Engine
	//AkMusicSettings musicInit;
	//AK::MusicEngine::GetDefaultInitSettings(musicInit);

	//if (AK::MusicEngine::Init(&musicInit) != AK_Success)
	//{
	//	assert(!"Could not initialize the WWise Music Engine.");
	//	return false;
	//}
	*/
	return true;
}

void Sound::TerminateSoundEngine()
{
	//AK::MusicEngine::Term();
	//AK::SoundEngine::Term();

	//g_lowLevelIO.Term();

	//if (AK::IAkStreamMgr::Get()) 
	//{
	//	AK::IAkStreamMgr::Get()->Destroy();
	//}

	//AK::MemoryMgr::Term();
}

void Sound::ProcessAudio()
{
	//AK::SoundEngine::RenderAudio();
}


