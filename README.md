# PICO-8 MIDI to Keyboard

A program which converts MIDI inputs to keyboard inputs, allowing MIDI devices to be used with PICO-8.

[Download from the releases tab](https://github.com/lucatronica/pico8-midi-to-keyboard/releases/latest).

## Running

On Windows, run:

```
.\midi-to-keyboard-windows.exe
```

#### Specifying which MIDI controller to use

To specify which MIDI controller to use, figure out its name and then enter its as the first argument.

Partial matches also work. The search is case sensitive. For example, if your controller is called "microKey-25", you can use it with the command:

```
.\midi-to-keyboard-windows.exe microKEY
```

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
