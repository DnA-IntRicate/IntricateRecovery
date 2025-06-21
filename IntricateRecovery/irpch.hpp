#pragma once

#ifndef NOMINMAX
    #define NOMINMAX
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <ostream>
#include <fstream>
#include <istream>
#include <string>
#include <filesystem>
#include <iomanip>
#include <regex>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstdint>
#include <numeric>
#include <random>
#include <limits>

#include <atomic>
#include <algorithm>
#include <memory>
#include <chrono>
#include <thread>
#include <utility>
#include <functional>
#include <execution>
#include <variant>
#include <mutex>
#include <stdexcept>
#include <typeinfo>
#include <type_traits>

#include <array>
#include <vector>
#include <iterator>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <tuple>

#ifdef INTRICATE_PLATFORM_WINDOWS
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
        #include <Windows.h>
    #endif
#endif
