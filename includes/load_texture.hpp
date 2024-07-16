#pragma once

#include "../includes/stb_image.h"

#include "glad/glad.h"
#include <iostream>

unsigned int load_texture(const char *path, const std::string &directory, bool gamma);
