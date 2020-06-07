/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "utils.h"

#include <stdarg.h>

#define FORMAT_BLOCK_SIZE 2048 // # of bytes to increment per try

std::string StringUtils::Format(const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  std::string str = FormatV(fmt, args);
  va_end(args);

  return str;
}

std::string StringUtils::FormatV(const char* fmt, va_list args)
{
  if (fmt == nullptr)
    return "";

  int size = FORMAT_BLOCK_SIZE;
  va_list argCopy;

  char* cstr = reinterpret_cast<char*>(malloc(sizeof(char) * size));
  if (cstr == nullptr)
    return "";

  while (1)
  {
    va_copy(argCopy, args);

    int nActual = vsnprintf(cstr, size, fmt, argCopy);
    va_end(argCopy);

    if (nActual > -1 && nActual < size) // We got a valid result
    {
      std::string str(cstr, nActual);
      free(cstr);
      return str;
    }
    if (nActual > -1) // Exactly what we will need (glibc 2.1)
      size = nActual + 1;
    else // Let's try to double the size (glibc 2.0)
      size *= 2;

    char* new_cstr = reinterpret_cast<char*>(realloc(cstr, sizeof(char) * size));
    if (new_cstr == nullptr)
      break;

    cstr = new_cstr;
  }

  free(cstr);
  return "";
}
