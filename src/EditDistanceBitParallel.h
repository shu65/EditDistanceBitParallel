/*
 * EditDistanceBitParallel.h
 *
 *  Created on: Oct 17, 2013
 *      Author: shu
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
  Distance CalculateEditDistance(TWord *string0_p_eq, char *string1, size_t string1_length);
};

template<typename TChar, typename TWord>
EditDistanceBitParallel<TChar, TWord>::EditDistanceBitParallel() {
}

template<typename TChar, typename TWord>
EditDistanceBitParallel<TChar, TWord>::~EditDistanceBitParallel() {
}

template<typename TChar, typename TWord>
void EditDistanceBitParallel<TChar, TWord>::BuildPeq(TChar *string, size_t string_length, TWord *p_eq) {
  for (size_t i = 0; i < string_length; ++i) {
    char c = string[i];
    p_eq[c] |= 1l << i;
  }
}

template<typename TChar, typename TWord>
EditDistanceBitParallel<TChar, TWord>::Distance EditDistanceBitParallel<TChar, TWord>::CalculateEditDistance(
    TWord *string0_p_eq, char *string1, size_t string1_length) {
  Distance distance = string1_length;
  Word d0, h_p, h_n, v_p, v_n;
  Word top = 1l << (string1_length - 1);
  v_p = ~0;
  v_n = 0;
  for (size_t i = 0; i < string1_length; ++i) {
    Word p_m = string0_p_eq[string1[i]];
    d0 = (((p_m & v_p) + v_p) ^ v_p) | p_m | v_n;
    h_p = v_n | ~(d0 | v_p);
    h_n = d0 & v_p;
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
