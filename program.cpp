#include <fstream>
#include <raylib.h>
#include <vector>
#include "program.hpp"
#define fieldPos field[(int)pos.y / spacingY * rX + (int)pos.x / spacingX]
void DrawColorGrid(int sX, int sY, Color c) {
    int spacingX = WIDTH  / sX,
        spacingY = HEIGHT / sY;
    for(int x =0; x < sX; x++)
        DrawLine(x * spacingX, 0, x * spacingX, HEIGHT, c);
    for(int y =0; y < sY; y++)
        DrawLine(0, y * spacingY, WIDTH, y * spacingY, c);
}

void ExportAudio(byte* field) {
    std::ofstream of("recording.wav");
    WAVHeader header;
    int SamplesPerX = header.SampleRate, Samples = SamplesPerX * rX;
    header.ByteRate      = header.NumChannels * header.BitsPerSample / 8 * header.SampleRate;
    header.Subchunk2Size = header.NumChannels * header.BitsPerSample / 8 * Samples;
    header.BlockAlign    = header.NumChannels * header.BitsPerSample / 8;
    header.ChunkSize     = header.Subchunk2Size + 36;
    
    of.write((char*)&header, sizeof(WAVHeader));
    const double period = 1. / header.SampleRate;
    double current = 0;
    byte buffer[SamplesPerX];
    for(int x =0; x < rX; x++) {
        std::vector<int> currentTones;
        for(int i =0; i < rY; i++) if(field[x + i * rX]) currentTones.push_back(i);
        // Write all the samples
        for(int sample = 0; sample < SamplesPerX; sample++) {
            double Sample = 0.00;
            for(int i =0; i < currentTones.size(); i++)
                Sample += funcf(1
                                * (sample + current) * period
                                * (tones[rY - currentTones[i]])
                                * (2 * M_PI)
                               )* volume;
            if(currentTones.size() > 0) Sample /= currentTones.size();
            buffer[sample] = Sample;
        }
        of.write((char*)buffer, SamplesPerX);
        current += SamplesPerX;
    }
    
    of.close();
}
int main() {
    SetTraceLogLevel(LOG_NONE);
    SetTargetFPS(60);
    InitWindow(WIDTH, HEIGHT, "MIDI Maker");
    byte field[rX * rY] = {};
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACK);
        DrawColorGrid(rX, rY, GRID);
        for(int i =0; i < rX * rY; i++) {
            if(field[i]) {
                int x = i % rX, y = i / rX;
                DrawRectangle(x * spacingX, y * spacingY, spacingX, spacingY, { (byte)(spacingXX*x+spacingYY*y), (byte)(spacingXX*x), (byte)(spacingYY * y), 255});
            }
        }

        Vector2 pos = GetMousePosition();
        if(IsMouseButtonReleased(PLACE_ONE)) fieldPos = !fieldPos;
        if(IsMouseButtonDown(HOLD_MORE))     fieldPos = 1;
        if(IsKeyPressed(DELETEALL)) for(int i =0; i < rX * rY; i++) field[i] = 0;
        if(IsKeyPressed(EXPORTBTN)) ExportAudio(field);
        
        
        EndDrawing();
    }
}
