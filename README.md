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

1. Notes are defined as numeric constants (following the MIDI standard):
1. The frequency for each note is calculated from its number m using the formula: <br>
   $$f_m = 440 \times 2^{\frac{(m - 69)}{12}}$$

   Where:

   - $f_m$ is the frequency of note $m$
   - $m$ is the note number (MIDI standard)

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

## Acknowledgments

- https://newt.phys.unsw.edu.au/jw/notes.html
