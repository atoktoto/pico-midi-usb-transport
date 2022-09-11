# pico-midi-usb-transport
Pico SDK, RP2040 transport for [FortySevenEffects/arduino_midi_library](https://github.com/FortySevenEffects/arduino_midi_library).
This library adds a nice-looking API to USB MIDI host and does not require Arduino so can be built with Pico SDK.

```cpp
void onNote(Channel channel, byte note, byte velocity) {
    printf("Note ON ch=%d, note=%d, vel=%d\n", channel, note, velocity);
}

MIDI.setHandleNoteOn(onNote);
```

Depends on a fork of TinyUSB library adding support for USB MIDI Host: https://github.com/atoktoto/tinyusb/tree/midihost.

## Usage

Checkout the example: https://github.com/atoktoto/pico-midi-usb-transport/tree/main/examples/print-notes