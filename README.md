# Music Notes Generator

WaveSynth Demo is a simple C application for generating musical notes and melodies programmatically. It is a proof-of-concept to experiment with sound synthesis and basic piano-like tones.

## Features

- Generate sine and additive harmonic waves.
- Supports multiple notes played simultaneously (simple chords).
- Phase-continuous wave generation to avoid clicks between notes.
- Basic ADSR envelope (attack & release) for smoother notes.
- Export generated audio to WAV format.
- Example: plays a simplified version of Beethoven’s Für Elise.

## Getting Started

### Prerequisites

- C compiler (e.g., GCC, Clang or MSVC)

### Compile

```bash
gcc -o wavesynth main.c -lm
```

### Run

```bash
./wavesynth
```

- Generates `example.wav` with the programmed melody.

## How It Works

1. Notes are defined using constants: `A4 = 440 Hz`, `E5 = 659` Hz, etc.
1. Each note is generated with additive synthesis.
1. An ADSR envelope is applied for smoother transitions.
1. Multiple notes can be mixed into the same buffer for chords.
1. Finally, samples are written to a WAV file.

### Example: Für Elise

```c
int notes[] = {E5, D#5, E5, D#5, E5, B4, D5, C5, A4, ...};
int notes2[] = {A3, E4, A3, E4, A3, E4, ...};

generate_note(samples, notes[i], DURATION);
generate_note(samples, notes2[i], DURATION);
```

## Notes

This project is for experimentation and learning — it is not a fully-featured synthesizer or music library.

## License

This project is licensed under the [MIT License](LICENSE).
