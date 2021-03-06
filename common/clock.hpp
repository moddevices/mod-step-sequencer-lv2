#ifndef _H_CLOCK_
#define _H_CLOCK_

#include <cstdint>
#include <math.h>
#include <cstdlib>
#include <ctime>

#define LO -1
#define HI 1

enum SyncMode {
    FREE_RUNNING = 0,
    HOST_BPM_SYNC,
    HOST_QUANTIZED_SYNC
};

class PluginClock {
public:
    PluginClock();
    ~PluginClock();
    void transmitHostInfo(const bool playing, const float beatstPerBar,
            const int hostBeat, const float hostBarBeat, const float hostBpm);
    void setSampleRate(float sampleRate);
    void setSyncMode(int mode);
    void setInternalBpmValue(float internalBpm);
    void setDivision(int division);
    void setSwing(float swing);
    void setRandomizeTiming(float randomize);
    void syncClock();
    void setPos(uint32_t pos);
    void setNumBarsElapsed(uint32_t numBarsElapsed);
    void calcPeriod();
    void closeGate();
    void reset();
    uint32_t getNumFramesQuarterNote();
    bool     getGate() const;
    float    getSampleRate() const;
    int      getSyncMode() const;
    float    getInternalBpmValue() const;
    float    getFrequency();
    int      *getDivision();
    uint32_t *getPeriod();
    uint32_t *getPos();
    float    getSwing() const;
    float    getRandomizeTiming() const;
    void     tick();

private:
    void setBpm(float bpm);

    bool gate;
    bool trigger;
    bool beatSync;
    bool phaseReset;
    bool playing;
    bool previousPlaying;
    bool endOfBar;
    bool init;

    uint32_t period;
    uint32_t halfWavelength;
    uint32_t quarterWaveLength;
    uint32_t pos;
    uint32_t numFramesQuarterNote;

    float randomValue;
    float beatsPerBar;
    float bpm;
    float swing;
    float randomize;
    float internalBpm;
    float hostBpm;
    float previousBpm;
    float sampleRate;
    int division;
    float divisionValue;

    float hostBarBeat;
    float beatTick;
    float frequency;
    int syncMode;
    int previousSyncMode;
    int hostTick;
    int hostBeat;
    int barLength;
    int numBarsElapsed;
    int previousBeat;
    int triggerIndex;

    int arpMode;

    // "1/1" "1/2" "1/3" "1/4" "1/4." "1/4T" "1/8" "1/8." "1/8T" "1/16" "1/16." "1/16T" "1/32"
    float divisionValues[13] {0.5, 1, 1.5, 2.0, 2.66666, 3.0, 4.0, 5.33333, 6.0, 8.0, 10.66666, 12.0, 16.0};
};

#endif
