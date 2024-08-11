#pragma once
#include <raylib.h>
#include <sys/types.h>
#include <cmath>

// Settings
const Color GRID = WHITE, BACK = BLACK;            
const int
    WIDTH  = 800,
    HEIGHT = 600,
    rX     =  25,
    rY     =  20;
const int volume = 127;
constexpr int spacingX = WIDTH / rX, spacingY = HEIGHT / rY;
constexpr float spacingYY = 255. / rY, spacingXX = 255. / rX;
const double tones[rY] = {
        261.63, 293.66, 329.63, 349.23,
        392.00, 440.00, 493.88, 523.25,
        587.33, 659.25, 698.46, 783.99,
        
        880.00,  987.77,  1046.5,  1174.66,
        1318.51, 1396.91, 1567.98, 1760
};
enum Keys {
    PLACE_ONE = MOUSE_BUTTON_LEFT,
    HOLD_MORE = MOUSE_BUTTON_RIGHT,
    DELETEALL = KEY_DELETE,
    EXPORTBTN = KEY_SPACE,
};
// Headers and stuff
struct WAVHeader {
    char    ChunkID[4]     = {'R', 'I', 'F', 'F'};
    int32_t ChunkSize      =  0;
    char    Format[4]      = {'W', 'A', 'V', 'E'};
    char    Subchunk1ID[4] = {'f', 'm', 't', ' '};
    int32_t Subchunk1Size  = 16;
    int16_t AudioFormat    =  1;
    int16_t NumChannels    =  1;
    int32_t SampleRate     = {44100};
    int32_t ByteRate       =  0;
    int16_t BlockAlign     =  0;
    int16_t BitsPerSample  =  8;
    
    char    Subchunk2ID[4] = {'d', 'a', 't', 'a'};
    int32_t Subchunk2Size;
};

inline float funcf(double input) {
    return sin(input) + 1;
}
typedef unsigned char byte;
