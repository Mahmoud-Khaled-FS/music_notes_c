#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#define BIT_PER_SAMPLES 16
#define SAMPLE_RATE 44100
#define CHANNELS 2
#define AMPLITUDE 32767.f
#define DURATION 0.5f
#define FREQUENCY 440.f
#define PIANO_KEYS 88
#define AUDIO_SIZE (SAMPLE_RATE * PIANO_KEYS * DURATION)

#define E5 76
#define D_5 75
#define B4 71
#define D5 74
#define C5 72
#define A4 69
#define C4 60
#define G4 67
#define F4 65
#define E4 64
#define D4 62
#define G_4 66
#define A3 57
#define E3 52

void write_16(int num, FILE *fd)
{
  fwrite(&num, 2, 1, fd);
}

void write_32(int num, FILE *fd)
{
  fwrite(&num, 4, 1, fd);
}

void write_8(int num, FILE *fd)
{
  fwrite(&num, 1, 1, fd);
}

void generate_note(int16_t *samples, int n, float duration)
{
  float freq = FREQUENCY * powf(2.0f, (n - A4) / 12.0f);
  for (size_t i = 0; i < SAMPLE_RATE * duration; i++)
  {
    float t = (float)i / (float)SAMPLE_RATE;
    float envelope = expf(-3.0f * t);
    float sampleValue = envelope *
                        (sin(2.0f * M_PI * freq * t) + 0.5f * sinf(2.0f * M_PI * 2.0f * freq * t) + 0.3f * sinf(2.0f * M_PI * 3.0f * freq * t) + 0.2f * sinf(2.0f * M_PI * 5.0f * freq * t));
    sampleValue /= (1.0f + 0.5f + 0.3f + 0.2f);
    float attackTime = 0.01f; // 10ms
    if (t < attackTime)
      sampleValue *= t / attackTime;
    if (t > duration - attackTime)
      sampleValue *= (duration - t) / attackTime;
    samples[i] = (int16_t)(AMPLITUDE * sampleValue);
  }
}

int main()
{
  int notes[] = {
      E5, D_5, E5, D_5, E5, B4, D5, C5, A4,
      C4, E4, A4, B4, E4, G_4, B4, C5,
      E5, D_5, E5, D_5, E5, B4, D5, C5, A4,
      C4, E4, A4, B4, E4, C5, B4, A4};

  int notes2[] = {
      A3, E4, A3, E4, A3, E4, A3, E4, A3,
      E3, A3, E3, A3, E3, A3, E3, A3,
      A3, E4, A3, E4, A3, E4, A3, E4, A3,
      E3, A3, E3, A3, E3, A3, E3, A3};

  int audioSize = (int)((sizeof(notes) / sizeof(notes[0]) * DURATION) * SAMPLE_RATE);

  int16_t *samples = (int16_t *)malloc(sizeof(int16_t) * audioSize);
  int16_t *samples2 = (int16_t *)malloc(sizeof(int16_t) * audioSize);
  printf("%d\n", audioSize);

  for (size_t i = 0; i < sizeof(notes) / sizeof(notes[0]); i++)
  {
    size_t offset = i * DURATION * SAMPLE_RATE;
    generate_note(samples + offset, notes[i], DURATION);
  }

  for (size_t i = 0; i < sizeof(notes2) / sizeof(notes2[0]); i++)
  {
    size_t offset = i * DURATION * SAMPLE_RATE;
    generate_note(samples2 + offset, notes2[i], DURATION);
  }

  for (size_t i = 0; i < (size_t)audioSize; i++)
  {
    int temp = samples[i] + samples2[i];
    if (temp > AMPLITUDE)
      temp = AMPLITUDE;
    if (temp < -AMPLITUDE)
      temp = -AMPLITUDE;
    samples[i] = temp;
  }

  FILE *fd = fopen("./example.wav", "wb");
  if (fd == NULL)
  {
    printf("[ERROR]: Can not open example.wav\n");
    return 1;
  }

  int byte_per_block = CHANNELS * (BIT_PER_SAMPLES / 8);
  fwrite("RIFF", 1, 4, fd);
  write_32(36 + (audioSize * byte_per_block), fd);
  fwrite("WAVE", 1, 4, fd);

  fwrite("fmt ", 1, 4, fd);
  write_32(16, fd);
  write_16(1, fd);
  write_16(CHANNELS, fd);
  write_32(SAMPLE_RATE, fd);
  write_32(SAMPLE_RATE * byte_per_block, fd);
  write_16(byte_per_block, fd);
  write_16(BIT_PER_SAMPLES, fd);
  fwrite("data", 1, 4, fd);
  write_32(audioSize * byte_per_block, fd);
  for (size_t i = 0; i < (size_t)audioSize; i++)
  {
    write_16(samples[i], fd);
    write_16(samples[i], fd);
  }

  fclose(fd);

  fd = fopen("./example.txt", "w");
  if (fd == NULL)
  {
    printf("[ERROR]: Can not open example.txt\n");
    return 1;
  }
  for (size_t i = 0; i < (size_t)audioSize; i++)
  {
    fprintf(fd, "%d\n", samples[i]);
  }
  fclose(fd);
  free(samples);

  return 0;
}
