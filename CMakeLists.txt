add_executable(Pico-NEC-IR-Decoder
        main.c
        )

target_link_libraries(Pico-NEC-IR-Decoder pico_stdlib)

pico_add_extra_outputs(Pico-NEC-IR-Decoder)

pico_enable_stdio_usb(Pico-NEC-IR-Decoder 1)
pico_enable_stdio_uart(Pico-NEC-IR-Decoder 0)