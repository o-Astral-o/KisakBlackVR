#pragma once

struct MemoryFile // sizeof=0x8024
{                                       // XREF: SaveGame/r
                                        // ?UI_Gametype_UploadToFileShare_f@@YAXXZ/r ...
    unsigned __int8 *buffer;
    int bufferSize;
    int bytesUsed;
    int cacheBufferUsed;
    int segmentIndex;
    int segmentStart;
    int nonZeroCount;
    int zeroCount;
    bool errorOnOverflow;
    bool memoryOverflow;
    bool compress_enabled;
    bool rle_enabled;
    bool is_writing;
    // padding byte
    // padding byte
    // padding byte
    int cacheBufferAvail;
    unsigned __int8 cacheBuffer[32760];
};

void __cdecl MemFile_WriteByte(MemoryFile *memFile, unsigned __int8 value);
void __cdecl MemFile_WriteShort(MemoryFile *memFile, __int16 value);
