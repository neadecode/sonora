#ifndef S_DEVICEINFO_H
#define S_DEVICEINFO_H

#include <stdint.h>

#if defined(__cplusplus)
enum class MID : uint16_t {
#else
typedef uint16_t MID;  //FALLBACK FOR EXTERN C
enum {
#endif
    #pragma region MANUFACTURER LIST
    MICROSOFT = 1,
    CREATIVE = 2,
    MEDIAVISION = 3,
    FUJITSU = 4,
    PRAGMATRAX = 5,
    CYRIX = 6,
    PHILIPS_SPEECH_PROCESSING = 7,
    NETXL = 8,
    ZYXEL = 9,
    BECUBED = 10,
    AARDVARK = 11,
    BINTEC = 12,
    HEWLETT_PACKARD = 13,
    ACULAB = 14,
    FAITH = 15,
    MITEL = 16,
    QUANTUM3D = 17,
    SNI = 18,
    EMU = 19,
    ARTISOFT = 20,
    TURTLE_BEACH = 21,
    IBM = 22,
    VOCALTEC = 23,
    ROLAND = 24,
    DSP_SOLUTIONS = 25,
    NEC = 26,
    ATI = 27,
    WANGLABS = 28,
    TANDY = 29,
    VOYETRA = 30,
    ANTEX = 31,
    ICL_PS = 32,
    INTEL = 33,
    GRAVIS = 34,
    VAL = 35,
    INTERACTIVE = 36,
    YAMAHA = 37,
    EVEREX = 38,
    ECHO = 39,
    SIERRA = 40,
    CAT = 41,
    APPS = 42,
    DSP_GROUP = 43,
    MELABS = 44,
    COMPUTER_FRIENDS = 45,
    ESS = 46,
    AUDIOFILE = 47,
    MOTOROLA = 48,
    CANOPUS = 49,
    EPSON = 50,
    TRUEVISION = 51,
    AZTECH = 52,
    VIDEOLOGIC = 53,
    SCALACS = 54,
    KORG = 55,
    APT = 56,
    ICS = 57,
    ITERATEDSYS = 58,
    METHEUS = 59,
    LOGITECH = 60,
    WINNOV = 61,
    NCR = 62,
    EXAN = 63,
    AST = 64,
    WILLOWPOND = 65,
    SONICFOUNDRY = 66,
    VITEC = 67,
    MOSCOM = 68,
    SILICONSOFT = 69,
    TERRATEC = 70,
    MEDIASONIC = 71,
    SANYO = 72,
    SUPERMAC = 73,
    AUDIOPT = 74,
    NOGATECH = 75,
    SPEECHCOMP = 76,
    AHEAD = 77,
    DOLBY = 78,
    OKI = 79,
    AURAVISION = 80,
    OLIVETTI = 81,
    IOMAGIC = 82,
    MATSUSHITA = 83,
    CONTROLRES = 84,
    XEBEC = 85,
    NEWMEDIA = 86,
    NMS = 87,
    LYRRUS = 88,
    COMPUSIC = 89,
    OPTI = 90,
    ADLACC = 91,
    COMPAQ = 92,
    DIALOGIC = 93,
    INSOFT = 94,
    MPTUS = 95,
    WEITEK = 96,
    LERNOUT_AND_HAUSPIE = 97,
    QCIAR = 98,
    APPLE = 99,
    DIGITAL = 100,
    MOTU = 101,
    WORKBIT = 102,
    OSITECH = 103,
    MIRO = 104,
    CIRRUSLOGIC = 105,
    ISOLUTION = 106,
    HORIZONS = 107,
    CONCEPTS = 108,
    VTG = 109,
    RADIUS = 110,
    ROCKWELL = 111,
    XYZ = 112,
    OPCODE = 113,
    VOXWARE = 114,
    NORTHERN_TELECOM = 115,
    APICOM = 116,
    GRANDE = 117,
    ADDX = 118,
    WILDCAT = 119,
    RHETOREX = 120,
    BROOKTREE = 121,
    ENSONIQ = 125
    #pragma endregion
};

#if defined(__cplusplus)
enum class PID : uint16_t {
#else
typedef uint16_t Product; //FALLBACK FOR EXTERN C
enum {
#endif
    #pragma region PID LIST
    ADLIB = 1,
    G711 = 2,           // MM_MSFT_ACM_G711
    GSM610 = 3,         // MM_MSFT_ACM_GSM610
    IMAADPCM = 4,       // MM_MSFT_ACM_IMAADPCM
    JOYSTICK = 5,       // MM_PC_JOYSTICK
    _MIDI_MAPPER = 6,    // MM_MIDI_MAPPER
    MPU401_MIDIIN = 7,
    MPU401_MIDIOUT = 8,
    MSADPCM = 9,        // MM_MSFT_ACM_MSADPCM
    WSS_FMSYNTH_STEREO = 10,
    WSS_AUX = 11,
    WSS_MIXER = 12,
    WSS_WAVEIN = 13,
    WSS_WAVEOUT = 14,
    MSACM = 15,         // MM_MSFT_MSACM
    MSFILTER = 16,      // MM_MSFT_ACM_MSFILTER
    WSS_OEM_AUX = 17,
    WSS_OEM_MIXER = 18,
    WSS_OEM_FMSYNTH_STEREO = 19,
    WSS_OEM_WAVEIN = 20,
    WSS_OEM_WAVEOUT = 21,
    GENERIC_AUX_CD = 22,
    GENERIC_AUX_LINE = 23,
    GENERIC_AUX_MIC = 24,
    GENERIC_MIDIOUT = 25,
    GENERIC_MIDIIN = 26,
    GENERIC_MIDISYNTH = 27,
    GENERIC_WAVEIN = 28,
    GENERIC_WAVEOUT = 29,
    PCSPEAKER_WAVEOUT = 30,
    PCM_CONVERTER = 31, // MM_MSFT_ACM_PCM
    SNDBLST_SYNTH = 32,
    SNDBLST_MIDIIN = 33,
    SNDBLST_MIDIOUT = 34,
    SNDBLST_WAVEIN = 35,
    SNDBLST_WAVEOUT = 36,
    _WAVE_MAPPER = 37
    #pragma endregion
};

#endif