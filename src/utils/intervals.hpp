#pragma once

#include "common.hpp"
class Interval {
public:
  double max, min;

  Interval(double min = infinty, double max = -infinty) : max(max), min(min) {};

  double size() const { return max - min; }

  bool contains(double x) { return x >= min && x <= max; }

  double clamp(double x) const {
    if (x < min)
      return min;
    if (x > max)
      return max;
    return x;
  }

  bool surrounds(double x) { return x > min && x < max; }
  static const Interval empty, universe;
};

const Interval Interval::empty = Interval();
const Interval Interval::universe = Interval(-infinty, +infinty);
