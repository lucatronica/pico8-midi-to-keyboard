# PICO-8 MIDI to Keyboard

A program which converts MIDI inputs to keyboard inputs, allowing MIDI devices to be used with PICO-8.

[Download from the releases tab](https://github.com/lucatronica/pico8-midi-to-keyboard/releases/latest).

## MIDI to key conversion

The following mapping is used:

MIDI | ASCII
---- | -----
0-31 | 32-63
32-62 | 96-125

An inverse mapping can be created like this:

```lua
key_to_midi={}
for i=32,63 do
  key_to_midi[chr(i)]=i-32
end
for i=96,125 do
  key_to_midi[chr(i)]=32+(i-96)
end
```

## Building

### Windows

Open the `midi-to-keyboard` project in Visual Studio and build.

### Mac

Run `./build-osx.sh`.