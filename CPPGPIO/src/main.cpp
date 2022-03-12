#include "main.h"

Main App;

xQueueHandle Main::button_evt_queue {nullptr};

void Main::run(void)
{
    vTaskDelay(pdMS_TO_TICKS(200));
    cppLed.setLevel(cppButton.read());
}

void Main::setup(void)
{
    button_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);

    esp_event_loop_args_t gpio_loop_args;
    gpio_loop_args.queue_size = 5;
    gpio_loop_args.task_name = "loop_task"; // Task will be created
    gpio_loop_args.task_priority = uxTaskPriorityGet(NULL);
    gpio_loop_args.task_stack_size = 2048;
    gpio_loop_args.task_core_id = tskNO_AFFINITY;

    esp_event_loop_create(&gpio_loop_args, &gpio_loop_handle); // Create Custom Event Loop
    esp_event_loop_create_default();    // Create System Event Loop

    cppButton.enableInterrupt(GPIO_INTR_NEGEDGE);
    cppButton.setQueueHandle(button_evt_queue);

    cppButton2.enablePullup();
    cppButton2.enableInterrupt(GPIO_INTR_NEGEDGE);
    cppButton2.setEventHandler(gpio_loop_handle, &task_custom_event);
}

extern "C" void app_main(void)
{
    App.setup();

    while (true)
    {
        App.run();
    }    
}

void  Main::button_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data)
{
    std::cout << "Button triggered interrupt with ID: " << id << '\n';
}

void  Main::button2_event_handler(void *handler_args, esp_event_base_t base, int32_t id, void *event_data)
{
    std::cout << "Button triggered interrupt with ID: " << id << '\n';
}

void Main::task_custom_event(void* handler_args, esp_event_base_t base, int32_t id, void* event_data)
{
    std::cout << "Button triggered interrupt with ID: " << id << " With Custom Loop\n";
}

void Main::gpio_task_example(void *arg)
{
   uint32_t io_num;
    for (;;)
    {
        if (xQueueReceive(Main::button_evt_queue, &io_num, portMAX_DELAY))
        {
            std::cout << "Interrupt triggered from pin " << (int)io_num << " and send to queue\n";
        }
    }
}
