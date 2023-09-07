//#if SK_DISPLAY
#include "sound_task.h"
#include "semaphore_guard.h"

static const uint8_t LEDC_CHANNEL_LCD_BACKLIGHT = 0;

SoundTask::SoundTask(const uint8_t task_core) : Task{"Sound", 2048, 1, task_core} {
  knob_state_queue_ = xQueueCreate(1, sizeof(PB_SmartKnobState));
  assert(knob_state_queue_ != NULL);

  mutex_ = xSemaphoreCreateMutex();
  assert(mutex_ != NULL);
}

SoundTask::~SoundTask() {
  vQueueDelete(knob_state_queue_);
  vSemaphoreDelete(mutex_);
}

void SoundTask::run() {
    //init setup for sound??
    
    PB_SmartKnobState state;

    while(1) {
        if (xQueueReceive(knob_state_queue_, &state, portMAX_DELAY) == pdFALSE) {
          continue;
        }

        int32_t current_pos = state.current_position;

        if(current_pos % 10 == 0) {
            MySound.Volume = 100;

            I2SAudio.Play(&MySound);
        }



        {
          SemaphoreGuard lock(mutex_);
          //
          
        }
        I2SAudio.FillBuffer();
        delay(2);
    }
}

QueueHandle_t SoundTask::getKnobStateQueue() {
  return knob_state_queue_;
}

void SoundTask::setLogger(Logger* logger) {
    logger_ = logger;
}

void SoundTask::log(const char* msg) {
    if (logger_ != nullptr) {
        logger_->log(msg);
    }
}

//#endif