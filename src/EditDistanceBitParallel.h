/*
 * EditDistanceBitParallel.h
 *
 *   Copyright (c) 2013, Shuji Suzuki
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1. Redistributions of source code must retain the above Copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above Copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. Neither the name of the authors nor the names of its contributors
 *      may be used to endorse or promote products derived from this
 *      software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *   PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifndef EDITDISTANCEBITPARALLEL_H_
#define EDITDISTANCEBITPARALLEL_H_

#include <stdint.h>

namespace edit_distance_bit_parallel {

template <typename TChar, typename TWord>
class EditDistanceBitParallel {
public:
  typedef uint32_t Distance;
  typedef TChar Char;
  typedef TWord Word;

  EditDistanceBitParallel();
  virtual ~EditDistanceBitParallel();

  void BuildPeq(TChar *string, size_t string_length, TWord *p_eq);
  Distance CalculateEditDistance(TWord *string0_p_eq, TChar *string1, size_t string1_length);
};

template<typename TChar, typename TWord>
EditDistanceBitParallel<TChar, TWord>::EditDistanceBitParallel() {
}

template<typename TChar, typename TWord>
EditDistanceBitParallel<TChar, TWord>::~EditDistanceBitParallel() {
}

template<typename TChar, typename TWord>
void EditDistanceBitParallel<TChar, TWord>::BuildPeq(TChar *string, size_t string_length, TWord *p_eq) {
  const Word w = 1;
  for (size_t i = 0; i < string_length; ++i) {
    Char c = string[i];
    p_eq[c] |= w << i;
  }
}

template<typename TChar, typename TWord>
typename EditDistanceBitParallel<TChar, TWord>::Distance EditDistanceBitParallel<TChar, TWord>::CalculateEditDistance(
    TWord *string0_p_eq, TChar *string1, size_t string1_length) {
  Distance distance = string1_length;
  Word top = 1l << (string1_length - 1);
  Word v_p = ~0;
  Word v_n = 0;
  for (size_t i = 0; i < string1_length; ++i) {
    Word p_m = string0_p_eq[string1[i]];
    Word d0 = (((p_m & v_p) + v_p) ^ v_p) | p_m | v_n;
    Word h_p = v_n | ~(d0 | v_p);
    Word h_n = d0 & v_p;
    if ((h_p & top) != 0) {
      ++distance;
    } else if ((h_n & top) != 0) {
      --distance;
    }
    v_p = (h_n << 1) | ~(d0 | ((h_p << 1) | 1));
    v_n = d0 & ((h_p << 1) | 1);
  }
  return distance;
}

} /* namespace edit_distance_bit_parallel */

#endif /* EDITDISTANCEBITPARALLEL_H_ */
