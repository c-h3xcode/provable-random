#include <fairandom/fairandom.h>
#include <fairandom/hex.h>
#include <fairandom/proof.h>
#include <stdio.h>
#include <string.h>

#define TEST_VECTORS_COUNT 4
#define TEST_VECTOR_LEN 64

#define testvec_array(name) char name[TEST_VECTORS_COUNT][TEST_VECTOR_LEN]

testvec_array(test_vectors) = {
    {0x69, 0xF7, 0x4D, 0x2A, 0x7E, 0x1A, 0x36, 0x41, 0xA5, 0xA4, 0xFC,
     0x3E, 0x82, 0x5B, 0x6E, 0x52, 0x68, 0xED, 0x54, 0x66, 0x15, 0x28,
     0xCA, 0xBC, 0xEA, 0x11, 0x1A, 0xA3, 0x1D, 0x7E, 0x26, 0x5A, 0x41,
     0xD1, 0xB2, 0xA1, 0x1C, 0x73, 0x51, 0xC2, 0x1F, 0xFB, 0x58, 0xBD,
     0x91, 0x00, 0x70, 0x0D, 0x9F, 0x8C, 0x63, 0x92, 0x23, 0xAC, 0xD4,
     0x4C, 0xEB, 0x6F, 0xEF, 0x15, 0x1C, 0x92, 0xCB, 0x61},
    {0x92, 0x6A, 0x55, 0x6C, 0xA9, 0x6C, 0xE1, 0x59, 0x6D, 0xF9, 0x09,
     0xA1, 0x33, 0xA7, 0xD5, 0x98, 0x58, 0xF1, 0x4F, 0xA2, 0x40, 0x8D,
     0xB4, 0x66, 0xC0, 0x47, 0x81, 0x51, 0x4A, 0xA0, 0xEE, 0x5C, 0x4D,
     0x24, 0x90, 0xB6, 0x29, 0xC6, 0x8A, 0xDC, 0xDC, 0x98, 0x4B, 0x51,
     0x10, 0x09, 0x1C, 0xFB, 0x7E, 0x75, 0x32, 0x9F, 0xD8, 0x2A, 0x5B,
     0x4D, 0xAD, 0x2E, 0xCB, 0xD1, 0x11, 0x0F, 0xA7, 0xDA},
    {0x60, 0x9B, 0x90, 0xF9, 0x46, 0xF6, 0xCD, 0x6D, 0xF0, 0x1E, 0x5B,
     0x26, 0x67, 0x6B, 0x1C, 0x49, 0x6A, 0x82, 0x0D, 0x66, 0xEB, 0x6C,
     0x1A, 0xD6, 0x67, 0x86, 0x80, 0x8F, 0x0C, 0x1E, 0x35, 0x64, 0x96,
     0x4B, 0x46, 0xC8, 0x3F, 0xD6, 0x33, 0x03, 0x0A, 0x68, 0xB8, 0xFC,
     0x34, 0xB0, 0xB2, 0x25, 0x0F, 0xE1, 0xFA, 0x64, 0xB5, 0xF5, 0x25,
     0xD8, 0xC3, 0x37, 0x9D, 0x2F, 0xE2, 0x34, 0x06, 0x49},
    {0x48, 0x98, 0x51, 0x77, 0x3F, 0x8A, 0x6A, 0x51, 0xCD, 0xDC, 0x4B,
     0x39, 0x66, 0x9A, 0x82, 0x23, 0x63, 0xF6, 0xA2, 0x7A, 0x74, 0x04,
     0x72, 0xE5, 0x59, 0x86, 0xA9, 0xB4, 0x1B, 0xFA, 0xFB, 0x58, 0x93,
     0x27, 0x4C, 0x5B, 0xE9, 0x3E, 0x71, 0x5F, 0x83, 0x0E, 0x59, 0x31,
     0x66, 0x35, 0xE3, 0xF0, 0x03, 0xD3, 0x9A, 0x4E, 0xBF, 0xC3, 0x20,
     0x10, 0x6B, 0xE5, 0x39, 0x2D, 0x79, 0xE7, 0xA4, 0x9F}};

testvec_array(test_vector_results) = {
    {0x7A, 0xD7, 0xDB, 0x59, 0x27, 0x4C, 0x53, 0x28, 0x42, 0x36, 0x65,
     0x49, 0x6A, 0xE5, 0xEA, 0xE0, 0x42, 0x2E, 0x47, 0x08, 0x0A, 0xFE,
     0xE7, 0x9D, 0x53, 0x3E, 0x49, 0x66, 0x22, 0x12, 0x0B, 0x91, 0x89,
     0xBD, 0xB0, 0x16, 0xAC, 0xD1, 0x13, 0x7B, 0x0F, 0xB4, 0xE0, 0xA1,
     0xB6, 0xDC, 0x33, 0xD8, 0x31, 0xA2, 0xA4, 0x8D, 0x60, 0xA4, 0x7A,
     0xD8, 0xAA, 0xAA, 0x1E, 0xFC, 0xD4, 0xE5, 0xC1, 0x87},
    {0x69, 0xEC, 0xE9, 0xCC, 0xB0, 0x3D, 0xC7, 0x7F, 0x90, 0x04, 0xBF,
     0x72, 0x5D, 0x32, 0xAD, 0x7B, 0xF7, 0x10, 0xB7, 0x70, 0x21, 0x35,
     0x35, 0x39, 0x83, 0xF6, 0xE2, 0x1C, 0x42, 0x8C, 0xA1, 0x66, 0xA6,
     0x5B, 0x68, 0x15, 0x4F, 0x2F, 0xA1, 0x75, 0x42, 0x0E, 0x42, 0x33,
     0x47, 0x3B, 0xBC, 0x3A, 0x7B, 0x31, 0x08, 0xFB, 0x6E, 0x2C, 0x77,
     0x11, 0x6C, 0x5C, 0xD1, 0x93, 0xB9, 0x4B, 0x1A, 0xE4},
    {0x47, 0x49, 0xDA, 0x18, 0x59, 0xF7, 0xE3, 0x26, 0x8F, 0x33, 0x5C,
     0x7B, 0x4C, 0x10, 0x4C, 0x48, 0xDE, 0x1B, 0x58, 0x20, 0x01, 0x78,
     0x29, 0x19, 0x2D, 0x1F, 0x4D, 0x9C, 0x6E, 0x79, 0xF3, 0x8B, 0xE4,
     0x32, 0x0A, 0x96, 0x3C, 0xB3, 0xCF, 0x06, 0x70, 0x37, 0xF6, 0xD2,
     0xFA, 0x6F, 0x36, 0xB9, 0x81, 0x5F, 0xD3, 0xAA, 0x18, 0x0B, 0x52,
     0x0E, 0xD8, 0x54, 0x27, 0x43, 0x34, 0x2D, 0x8E, 0x3C},
    {0xDF, 0x4F, 0x9C, 0xC4, 0xC3, 0x02, 0xA6, 0x5A, 0x87, 0x8F, 0x67,
     0x8C, 0xB9, 0x1F, 0x7F, 0xFB, 0xC9, 0x2A, 0x39, 0xF2, 0xB4, 0x7E,
     0xED, 0x67, 0xB4, 0x57, 0xB4, 0xAB, 0xD9, 0xF6, 0x59, 0x47, 0xA1,
     0x48, 0x3C, 0x60, 0xA1, 0xC1, 0x70, 0xDC, 0xC7, 0xA8, 0x62, 0x48,
     0x0D, 0xD8, 0xB7, 0x40, 0xDC, 0xB9, 0x71, 0xBD, 0x61, 0xB7, 0xBE,
     0xD3, 0xD2, 0x81, 0xFC, 0x34, 0xDE, 0x06, 0x0B, 0x21},
};

int main(void) {
  for (int i = 0; i < TEST_VECTORS_COUNT; i++) {
    fr_generator_t *generator =
        fr_generator_new(FR_DEFAULT_ROUNDS, FR_DEFAULT_SALT);
    fr_generator_seed(generator, FR_SEED_TYPE_STRING, test_vectors[i],
                      TEST_VECTOR_LEN);

    char output[TEST_VECTOR_LEN];
    fr_generate(generator, output, TEST_VECTOR_LEN);

    fr_generator_free(generator);

    if (memcmp(output, test_vector_results[i],
               (long unsigned int)TEST_VECTOR_LEN) != 0) {
      printf("Test vector %d failed\n", i);
      return 1;
    }
  }
  return 0;
}