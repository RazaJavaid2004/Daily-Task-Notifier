# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DailyTaskNotifier_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DailyTaskNotifier_autogen.dir\\ParseCache.txt"
  "DailyTaskNotifier_autogen"
  )
endif()
