#pragma once

#include <chrono>

#define TICK(x) auto time_begin_##x = std::chrono::steady_clock::now();
#define TOCK(x) cout << "spends:" << std::chrono::duration_cast<double>(std::chrono::steady_clock::now() - time_beigin_##x).count() << "S" << std::endl;