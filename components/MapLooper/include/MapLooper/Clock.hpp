/*
           __  
  /\/\    / /  
 /    \  / /   
/ /\/\ \/ /___ 
\/    \/\____/ 
MapLooper
(c) Mathias Bredholt 2020

*-0-*-0-*-0-*-0-*-0-*-0-*-0-*-0-*-0-*

Clock.hpp
A clock module that interfaces with Ableton Link.

*/

#pragma once

#include <climits>
#include <cstdint>
#include <functional>

#include "esp_attr.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace MapLooper {
class Clock {
 public:
  static constexpr double TICKS_PER_QUARTER_NOTE = 48.0;
  static constexpr float DEFAULT_TEMPO = 120.0f;
  static const int q = 4;

  Clock();

  void reset();

  void start();

  void stop();

  int32_t getTicks() const;

  float getTempo() const;

  void setTempo(float val);

  bool isLinked() const;

  void setStartStopCallback(std::function<void(bool)> callback);

  int getTickInterval() const;

 private:
  void* _link;

  TaskHandle_t _link_task_handle;
};

class TickFunction {
 public:
  bool is_on_tick(int32_t ticks) {
    if (ticks != last_time) {
      last_time = ticks;
      return true;
    }
    return false;
  }

 private:
  int32_t last_time = INT_MIN;
};

}  // namespace MapLooper
