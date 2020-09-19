#ifndef CUBE_DECODER_H
#define CUBE_DECODER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static const char* cube_sides[6] = {"Blue", "Orange", "Yellow", "Green", "Red", "White"};
static const char* cube_colors[6] = {"Green", "Yellow", "Red", "White", "Orange", "Blue"};
void parse_cube(uint8_t result_buffer[6][9], uint8_t cube_data[20]);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* MODULE_H */
