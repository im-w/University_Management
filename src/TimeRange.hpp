#ifndef TIMERANGE_HPP
#define TIMERANGE_HPP

#include <string>

struct TimeRange {
  std::string weekday;
  int startHour;
  int endHour;
};

TimeRange parseTimeRange(const std::string &timeStr);
bool isOverlap(const TimeRange &timeRange1, const TimeRange &timeRange2);

#endif // TIMERANGE_HPP
