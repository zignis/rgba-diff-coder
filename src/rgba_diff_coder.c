#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rgba_diff_coder"

typedef struct {
  unsigned int r, g, b, a;
}
RGBA;

void encode(const RGBA * input, RGBA * output, int pixel_count) {
  assert(pixel_count % 4 == 0);

  output[0] = input[0];

  for (int i = 1; i < pixel_count; i++) {
    RGBA curr = input[i];
    RGBA prev = input[i - 1];

    RGBA out = {
      r: curr.r - prev.r,
      g: curr.g - prev.g,
      b: curr.b - prev.b,
      a: curr.a - prev.a
    };

    output[i] = out;
  }
}

void decode(const RGBA * input, RGBA * output, int pixel_count) {
  assert(pixel_count % 4 == 0);

  output[0] = input[0];

  for (int i = 1; i < pixel_count; i++) {
    RGBA curr = input[i];
    RGBA prev = output[i - 1];

    RGBA out = {
      r: prev.r + curr.r,
      g: prev.g + curr.g,
      b: prev.b + curr.b,
      a: prev.a + curr.a
    };

    output[i] = out;
  }
}
