#include <pico/platform.h>

#include <cstdio>
#include "pico/stdlib.h"

#include "MIDI.h"
#include "TUSB-MIDI.hpp"

using namespace usbMidi;

UsbMidiTransport usbMIDITransport(0);
MidiInterface<UsbMidiTransport> MIDI((UsbMidiTransport&)usbMIDITransport);

void onNote(Channel channel, byte note, byte velocity) {
    printf("Note ON ch=%d, note=%d, vel=%d\n", channel, note, velocity);
}

void offNote(Channel channel, byte note, byte velocity) {
    printf("Note OFF ch=%d, note=%d, vel=%d\n", channel, note, velocity);
}

void onControlChange(Channel channel, byte b1, byte b2) {
    printf("ControlChange ch=%d, b1=%d, b2=%d\n", channel, b1, b2);
}

int main(void) {
    stdio_init_all();
    printf("pico-midi-usb transport example\n");

    tusb_init();

    MIDI.begin(11);
    MIDI.setHandleNoteOn(onNote);
    MIDI.setHandleNoteOff(offNote);
    MIDI.setHandleControlChange(onControlChange);

    while(true) {
        tuh_task();
        MIDI.read();
    }
}

void tuh_midi_rx_cb(uint8_t dev_addr, uint32_t num_packets) {
    usbMIDITransport.tuh_midi_rx_cb(dev_addr, num_packets);
}

void tuh_midi_mount_cb(uint8_t dev_addr, uint8_t in_ep, uint8_t out_ep, uint8_t num_cables_rx, uint16_t num_cables_tx) {
    printf("MIDI device address = %u, IN endpoint %u has %u cables, OUT endpoint %u has %u cables\r\n",
            dev_addr, in_ep & 0xf, num_cables_rx, out_ep & 0xf, num_cables_tx);

    usbMIDITransport.midi_dev_addr = dev_addr;
}

// Invoked when device with hid interface is un-mounted
void tuh_midi_umount_cb(uint8_t dev_addr, uint8_t instance) {
    printf("MIDI device address = %d, instance = %d is unmounted\r\n", dev_addr, instance);

    usbMIDITransport.midi_dev_addr = 0;
}