// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

#include "imgsoa/imgesoa.hpp"

#include "gtest/gtest.h"
#include <cstddef>
#include <cstdint>
#include <vector>

TEST(TestInterpolate,Interpolate8t0) {
  // Definicion de datos
  PixelData<uint8_t> data;
  data.r = {100};
  data.g = {150};
  data.b = {200};
  uint8_t r_out = 0,g_out = 0,b_out = 0;
  size_t constexpr idx1 = 0;
  size_t  constexpr idx2 = 0;
  float constexpr  t = 0;

  // Función
  interpolate(data,idx1,idx2,t,r_out,g_out,b_out);

  // Comprobación
  EXPECT_EQ(r_out,100);
  EXPECT_EQ(g_out,150);
  EXPECT_EQ(b_out,200);
}

TEST(TestInterpolate,Interpolate8t1) {
  // Definicion de datos
  PixelData<uint8_t> data;
  data.r = {100,200};
  data.g = {150,240};
  data.b = {200,190};
  uint8_t r_out = 0,g_out = 0,b_out = 0;
  size_t constexpr idx1 = 0;
  size_t  constexpr idx2 = 1;
  float constexpr  t = 1;

  // Función
  interpolate(data,idx1,idx2,t,r_out,g_out,b_out);

  // Comprobación
  EXPECT_EQ(r_out,200);
  EXPECT_EQ(g_out,240);
  EXPECT_EQ(b_out,190);
}

TEST(TestInterpolate,Interpolate8t01) {
  // Definicion de datos
  PixelData<uint8_t> data;
  data.r = {100,200};
  data.g = {150,240};
  data.b = {200,190};
  uint8_t r_out = 0,g_out = 0,b_out = 0;
  size_t constexpr idx1 = 0;
  size_t  constexpr idx2 = 1;
  float constexpr t = 0.733f;

  // Función
  interpolate(data,idx1,idx2,t,r_out,g_out,b_out);

  // Comprobación
  EXPECT_EQ(r_out,173);
  EXPECT_EQ(g_out,215);
  EXPECT_EQ(b_out,192);
}

TEST(TestInterpolate,Interpolate16t0) {
  // Definicion de datos
  PixelData<uint16_t> data;
  data.r = {6969};
  data.g = {3343};
  data.b = {3823};
  uint16_t r_out = 0,g_out = 0,b_out = 0;
  size_t constexpr idx1 = 0;
  size_t  constexpr idx2 = 0;
  float constexpr  t = 0;

  // Función
  interpolate(data,idx1,idx2,t,r_out,g_out,b_out);

  // Comprobación
  EXPECT_EQ(r_out,6969);
  EXPECT_EQ(g_out,3343);
  EXPECT_EQ(b_out,3823);
}

TEST(TestInterpolate,Interpolate16t1) {
  // Definicion de datos
  PixelData<uint16_t> data;
  data.r = {1002,6969};
  data.g = {1501,3343};
  data.b = {2007,3823};
  uint16_t r_out = 0,g_out = 0,b_out = 0;
  size_t constexpr idx1 = 0;
  size_t  constexpr idx2 = 1;
  float constexpr  t = 1;

  // Función
  interpolate(data,idx1,idx2,t,r_out,g_out,b_out);

  // Comprobación
  EXPECT_EQ(r_out,6969);
  EXPECT_EQ(g_out,3343);
  EXPECT_EQ(b_out,3823);
}

TEST(TestInterpolate,Interpolate16t01) {
  // Definicion de datos
  PixelData<uint16_t> data;
  data.r = {1002,6969};
  data.g = {1501,3343};
  data.b = {2007,3823};
  uint16_t r_out = 0,g_out = 0,b_out = 0;
  size_t constexpr idx1 = 0;
  size_t  constexpr idx2 = 1;
  float constexpr t = 0.733f;

  // Función
  interpolate(data,idx1,idx2,t,r_out,g_out,b_out);

  // Comprobación
  EXPECT_EQ(r_out,5375);
  EXPECT_EQ(g_out,2851);
  EXPECT_EQ(b_out,3338);
}

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)