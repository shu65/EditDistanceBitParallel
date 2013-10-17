/*
 * EditDistanceBitParallelTest.cpp
 *
 *  Created on: Oct 17, 2013
 *      Author: shu
 */

#include <gtest/gtest.h>
#include <string>
#include <fstream>

TEST(EditDistanceBitParallelTest, CalculateEditDistance) {
  typedef bio_sequence::IsStringEndWithEndIterator<string::iterator> IsStringEnd;
  typedef bio_sequence::aligner::basic::LocalAligner LocalAligner;
  typedef bio_sequence::SimpleSubstituteScore<const char, LocalAligner::Score> Score;
  typedef bio_sequence::aligner::basic::EditBlocks EditBlocks;
  string str0 = "aaaaaaaa";
  string str1 = "bbbbbbbb";
  IsStringEnd is_string0_end(str0.end());
  IsStringEnd is_string1_end(str1.end());
  LocalAligner local_aligner;
  local_aligner.SetMaxString0Size(str0.size());
  local_aligner.SetMaxString1Size(str1.size());
  LocalAligner::Score score;
  EditBlocks edit_blocks;

  LocalAligner::Position string0_start = 0;
  LocalAligner::Position string1_start = 0;
  LocalAligner::Position string0_end = 0;
  LocalAligner::Position string1_end = 0;
  local_aligner.Align(str0.begin(), is_string0_end, str1.begin(),
      is_string1_end, Score(1, -3), -8, -1, &score,
      &string0_start, &string0_end, &string1_start,
      &string1_end, &edit_blocks);

  EXPECT_EQ(0, score);
  EXPECT_EQ(0, edit_blocks.GetSize());
}


