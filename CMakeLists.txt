cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico-midi-usb-transport C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(PICO_PLATFORM "rp2040")

pico_sdk_init()

set(FAMILY rp2040)
set(BOARD pico_sdk)

add_library(arduino-midi STATIC
        lib/arduino_midi_library/src/MIDI.cpp
        )
target_include_directories(arduino-midi
        PUBLIC lib/arduino_midi_library/src
        )

add_subdirectory(src)
add_subdirectory(examples)

