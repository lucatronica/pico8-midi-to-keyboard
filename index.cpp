#include <iostream>

// Simulates a key press.
void pressKey(char key);

#if defined(_WIN32)

#include <Windows.h>

HKL winKeyboardLayout = GetKeyboardLayout(0);

void pressKey(char key) {
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = key;
	input.ki.wVk = 0;
	input.ki.dwFlags = KEYEVENTF_UNICODE;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;

	SendInput(1, &input, sizeof(INPUT));
}

// TODO linux
// TODO osx

#endif

#include "RtMidi.h"

char midiTable[128];

void initMidiTable() {
	// fill with ' '
	for (int i = 0; i < 128; i++) {
		midiTable[i] = ' ';
	}

	// full range
	for (int i = 32; i <= 63; i++) {
		midiTable[i - 32] = i;
	}

	int n1 = (63 - 32) + 1;
	for (int i = 96; i <= 125; i++) {
		midiTable[n1 + (i - 96)] = i;
	}
}

void exitWithMessage(std::string message, int code) {
	std::cout << message << std::endl;
	std::cin.get();
	exit(code);
}

int getMidiPort(RtMidiIn* midiIn, char* preferredPortName) {
	int portCount = midiIn->getPortCount();
	if (portCount == 0) {
		exitWithMessage("No MIDI inputs found.", EXIT_FAILURE);
	}

	if (portCount > 1) {
		// Find best port from name.
		if (preferredPortName != nullptr) {
			for (int i = 0; i < portCount; i++) {
				auto portName = midiIn->getPortName(i);
				if (portName.find(preferredPortName) != std::string::npos) {
					return i;
				}
			}
		}
	}

	return 0;
}

void midiInputCallback(double deltaTime, std::vector<unsigned char> *message, void *userData) {
	if (message->size() == 3) {
		auto status = message->at(0);
		auto data1 = message->at(1);
		// auto data2 = message->at(2);

		int a = status & 0b11110000;
		int b = 0b10010000;
		if (a == b) {
			int note = data1 & 0b01111111;

			pressKey(midiTable[note]);
		}
	}
}

int main(int argc, char** argv) {
	char* preferredPortName = argc <= 1 ? nullptr : argv[1];

	initMidiTable();

	RtMidiIn* midiIn = new RtMidiIn();

	int port = getMidiPort(midiIn, preferredPortName);
	midiIn->openPort(port);

	midiIn->setCallback(&midiInputCallback);

	auto portName = midiIn->getPortName(port);

	std::cout << "PICO-8 MIDI to Keyboard ready!" << std::endl;
	std::cout << "MIDI device: " << portName << std::endl;

	// wait
	std::cin.get();

	return 0;
}
