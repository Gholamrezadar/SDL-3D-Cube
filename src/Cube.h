#pragma once
#include "Renderer.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

std::vector<glm::vec2> generateCube(float angle = 0.0f, bool isOrthographic = false);
