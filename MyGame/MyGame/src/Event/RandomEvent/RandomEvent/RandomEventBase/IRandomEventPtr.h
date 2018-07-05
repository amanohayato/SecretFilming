#pragma once
#include <memory>

// ランダムイベントポインタ
class IRandomEvent;
using IRandomEventPtr = std::shared_ptr<IRandomEvent>;