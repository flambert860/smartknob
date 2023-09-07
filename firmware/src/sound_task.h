#pragma once

//#if SK_DISPLAY

#include <Arduino.h>

#include "logger.h"
#include "proto_gen/smartknob.pb.h"
#include "task.h"
#include "sound/XT_I2S_Audio.h"
#include "sound/WavData.h"
#include "sound/MusicDefinitions.h"


#define I2S_DOUT 22 // i2S Data out oin
#define I2S_BCLK 26 // Bit clock
#define I2S_LRC 25  // Left/Right clock, also known as Frame clock or word select

class SoundTask : public Task<SoundTask> {
    friend class Task<SoundTask>; // Allow base Task to invoke protected run()

    public:
        SoundTask(const uint8_t task_core);
        ~SoundTask();

        QueueHandle_t getKnobStateQueue();

        XT_I2S_Class I2SAudio(I2S_LRC, I2S_BCLK, I2S_DOUT, I2S_NUM_0);

        XT_Wav_Class MySound(WavData16BitStereo);

        void setLogger(Logger* logger);

    protected:
        void run();

    private:

        QueueHandle_t knob_state_queue_;

        PB_SmartKnobState state_;
        SemaphoreHandle_t mutex_;
        //uint16_t brightness_;
        Logger* logger_;
        void log(const char* msg);
};

//#else

//class SoundTask {};

//#endif
