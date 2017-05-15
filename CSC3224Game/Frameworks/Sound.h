/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* This class is the class used to integrate WWise audio with the game engine
*
* The class is entirely commented out since I never fully got it working. I have left it in to show some of the progress and possibly to come back to in the future.
*/

#pragma once
/* Commented Out for now
#include "C:\\Program Files (x86)\\Audiokinetic\\Wwise 2016.2.3.6077\\SDK\\samples\\SoundEngine\\Win32\\AkFilePackageLowLevelIOBlocking.h"
#include <AK/SoundEngine/Common/AkMemoryMgr.h>                  // Memory Manager
#include <AK/SoundEngine/Common/AkModule.h>                     // Default memory and stream managers
#include <AK/SoundEngine/Common/IAkStreamMgr.h>                 // Streaming Manager
#include <AK/Tools/Common/AkPlatformFuncs.h>                    // Thread defines
#include <AK/SoundEngine/Common/AkSoundEngine.h>				// Sound Engine
#include <AK/MusicEngine/Common/AkMusicEngine.h>                // Music Engine
#include "AK/AkWwiseSDKVersion.h"
#include "AK/SoundEngine/Platforms/Windows/AkWinSoundEngine.h"

//#pragma comment(lib, "AKSoundEngine.lib")
//#pragma comment(lib, "AKMemoryMgr.lib")
//#pragma comment(lib, "AkStreamMgr.lib")
////#pragma comment(lib, "lib/AkAudioInputSource.lib")
//#pragma comment(lib, "AkMusicEngine.lib")
//#pragma comment(lib, "dsound.lib")
//#pragma comment(lib, "dinput8.lib")

// Custom alloc/free functions. These are declared as "extern" in AkMemoryMgr.h
// and MUST be defined by the game developer.
//namespace AK
//{
//#ifdef WIN32
//	void * AllocHook(size_t in_size)
//	{
//		return malloc(in_size);
//	}
//	void FreeHook(void * in_ptr)
//	{
//		free(in_ptr);
//	}
//	// Note: VirtualAllocHook() may be used by I/O pools of the default implementation
//	// of the Stream Manager, to allow "true" unbuffered I/O (using FILE_FLAG_NO_BUFFERING
//	// - refer to the Windows SDK documentation for more details). This is NOT mandatory;
//	// you may implement it with a simple malloc().
//	void * VirtualAllocHook(
//		void * in_pMemAddress,
//		size_t in_size,
//		DWORD in_dwAllocationType,
//		DWORD in_dwProtect
//	)
//	{
//		return VirtualAlloc(in_pMemAddress, in_size, in_dwAllocationType, in_dwProtect);
//	}
//	void VirtualFreeHook(
//		void * in_pMemAddress,
//		size_t in_size,
//		DWORD in_dwFreeType
//	)
//	{
//		VirtualFree(in_pMemAddress, in_size, in_dwFreeType);
//	}
//#endif
//}
*/
class Sound
{
public:
	Sound();
	~Sound();

	static bool InitSoundEngine();
	static void TerminateSoundEngine();
	static void ProcessAudio();
	//static CAkFilePackageLowLevelIOBlocking g_lowLevelIO;
};

