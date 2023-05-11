#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers


#include <map>
#include <list>
#include <mutex>
#include <vector>
#include <bitset>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <algorithm>
#include <filesystem>
#include <functional>
#include <unordered_map>

#include "model.h"
#include "camera.h"
#include "lru_cache.hpp"

#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"winhttp.lib")
#pragma comment(lib,"wininet.lib")


