#include "TimeRange.hpp"
#include <string>

TimeRange parseTimeRange(const std::string &timeStr) {
  TimeRange timeRange;
  size_t pos = 0;
  for (; pos < timeStr.size() && timeStr[pos] != ':'; ++pos) {
    timeRange.weekday += timeStr[pos];
  }
  pos++;
  std::string startHourStr;
  for (; pos < timeStr.size() && timeStr[pos] != '-'; ++pos) {
    startHourStr += timeStr[pos];
  }
  pos++;
  std::string endHourStr;
  for (; pos < timeStr.size(); ++pos) {
    endHourStr += timeStr[pos];
  }
  timeRange.startHour = std::stoi(startHourStr);
  timeRange.endHour = std::stoi(endHourStr);
  return timeRange;
}

bool isOverlap(const TimeRange &timeRange1, const TimeRange &timeRange2) {
  if (timeRange1.weekday != timeRange2.weekday) {
    return false;
  }
  return !(timeRange1.endHour <= timeRange2.startHour ||
           timeRange2.endHour <= timeRange1.startHour);
}
