#pragma once

#include <iostream>

#include "cppgpio.h"

// Main class used for testing only
class Main final
{
public:
    void run(void);
    void setup(void);

    esp_event_loop_handle_t gpio_loop_handle {};

    // LED pin on my NodeMCU
    CPPGPIO::GpioOutput cppLed { GPIO_NUM_2, true };
    // Repurpose the BOOT button to work as an input
    CPPGPIO::GpioInput cppButton { GPIO_NUM_0 };
    // A second input to demonstrate Event_ID different event handlers
    CPPGPIO::GpioInput cppButton2 { GPIO_NUM_12 };

    // Event Handler for cppButton
    static void  button_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data);
    // Event Handler for cppButton2
    static void  button2_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data);
    // Event Handler for custom loop
    static void task_custom_event(void* handler_args, esp_event_base_t base, int32_t id, void* event_data);
    // Handle for the queue
    static xQueueHandle button_evt_queue;
    // Prototype for the task
    static void gpio_task_example(void *arg);

}; // Main Class
