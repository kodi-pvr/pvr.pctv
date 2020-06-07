/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include <string>

#pragma once

class StringUtils
{
public:
  static std::string Format(const char* fmt, ...);
  static std::string FormatV(const char* fmt, va_list args);
};
