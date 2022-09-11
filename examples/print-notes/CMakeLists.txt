

add_executable(example-print-notes main.cpp)
target_include_directories(example-print-notes PUBLIC
        .
        )
target_link_libraries(example-print-notes
        pico-midi-usb
        )
pico_add_extra_outputs(example-print-notes)