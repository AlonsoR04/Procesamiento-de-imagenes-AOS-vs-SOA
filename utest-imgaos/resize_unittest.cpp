#include "imgaos/imgeaos.hpp"
#include "gtest/gtest.h"

#include <cstdint>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

TEST(InterpolarTestAOS, interpolar8){

  const Pixel<uint8_t> pixel1 = {100, 100, 100};
  const Pixel<uint8_t> pixel2 = {250, 0, 40};
  const float factor_interpolacion = 0.6f;
  const Pixel<uint8_t> interpolacion = interpolate(pixel1, pixel2, factor_interpolacion);

  EXPECT_EQ(interpolacion.r, static_cast<uint8_t>(190)); // c1.r + f_i(c2.r-c1.r)
  EXPECT_EQ(interpolacion.g, static_cast<uint8_t>(39)); // c1.g + f_i(c2.g-c1.g)
  EXPECT_EQ(interpolacion.b, static_cast<uint8_t>(64)); // c1.b + f_i(c2.b-c1.b)
}

TEST(InterpolarTestAOS, interpolar16){

  const Pixel<uint16_t> pixel1 = {1000, 1000, 1000};
  const Pixel<uint16_t> pixel2 = {2500, 0, 400};
  const float factor_interpolacion = 0.6f;
  const Pixel<uint16_t> interpolacion = interpolate(pixel1, pixel2, factor_interpolacion);

  EXPECT_EQ(interpolacion.r, static_cast<uint16_t>(1900)); // c1.r + f_i(c2.r-c1.r)
  EXPECT_EQ(interpolacion.g, static_cast<uint16_t>(400)); // c1.g + f_i(c2.g-c1.g)
  EXPECT_EQ(interpolacion.b, static_cast<uint16_t>(640)); // c1.b + f_i(c2.b-c1.b)
}

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
