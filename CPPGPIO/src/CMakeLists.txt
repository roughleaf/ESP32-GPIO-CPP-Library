set(SOURCES main.cpp
            CPPGPIO/cppgpio_input.cpp
            CPPGPIO/cppgpio_output.cpp)
            
idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS .  ../include/CPPGPIO)
