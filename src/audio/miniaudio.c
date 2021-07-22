#define STB_VORBIS_HEADER_ONLY
#include "audio/stb_vorbis.c"

#define DR_MP3_IMPLEMENTATION
#include "audio/dr_mp3.h"

#define DR_WAV_IMPLEMENTATION
#include "audio/dr_wav.h"

#define MINIAUDIO_IMPLEMENTATION
#include "audio/miniaudio.h"

#undef STB_VORBIS_HEADER_ONLY
#include "audio/stb_vorbis.c"
