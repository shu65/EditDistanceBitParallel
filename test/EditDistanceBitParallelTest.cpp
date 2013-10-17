/*
 * EditDistanceBitParallelTest.cpp
 *
 *  Created on: Oct 17, 2013
 *      Author: shu
 */

#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include "../src/EditDistanceBitParallel.h"

TEST(EditDistanceBitParallelTest, CalculateEditDistance) {
  typedef edit_distance_bit_parallel::EditDistanceBitParallel<uint8_t, uint64_t> TestEditDistanceBitParallel;

  TestEditDistanceBitParallel::Char alphabet_size = 4;
  TestEditDistanceBitParallel::Char str0_values[] = { 0, 1, 2, 3, 0, 1, 2, 3 };
  std::vector<TestEditDistanceBitParallel::Char> str0(&str0_values[0],
      &str0_values[0] + sizeof(str0_values) / sizeof(str0_values[0]));

  TestEditDistanceBitParallel::Char str1_values[] = { 0, 0, 2, 3, 0, 1, 2, 3 };
  std::vector<TestEditDistanceBitParallel::Char> str1(&str1_values[0],
      &str1_values[0] + sizeof(str1_values) / sizeof(str1_values[0]));
  std::vector<TestEditDistanceBitParallel::Word> str0_p_eq(alphabet_size, 0);

  TestEditDistanceBitParallel editdistance_bit_parallel;
  editdistance_bit_parallel.BuildPeq(&str0[0], str0.size(), &str0_p_eq[0]);
  TestEditDistanceBitParallel::Distance distance = editdistance_bit_parallel.CalculateEditDistance(
      &str0_p_eq[0], &str1[0], str1.size());

  EXPECT_EQ(1, distance);
}

