mkdir build
g++ -Wall -D__MACOSX_CORE__ index.cpp RtMidi.cpp -framework CoreMIDI -framework CoreAudio -framework CoreFoundation -framework ApplicationServices -o build/midi-to-keyboard-osx
