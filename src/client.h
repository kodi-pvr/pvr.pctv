/*
 *  Copyright (C) 2005-2020 Team Kodi
 *  https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include "kodi/libXBMC_addon.h"
#include "kodi/libXBMC_pvr.h"

#define DEFAULT_HOST "192.168.1.20"
#define DEFAULT_WEB_PORT 80
#define DEFAULT_PIN "0000"
#define DEFAULT_AUTH ""
#define DEFAULT_TRANSCODE false
#define DEFAULT_USEPIN false
#define DEFAULT_BITRATE 1200

extern bool m_bCreated;
extern std::string g_strHostname;
extern int g_iPortWeb;
extern std::string g_strPin;
extern std::string g_strAuth;
//extern std::string                   g_strBaseUrl;
extern int g_iStartNumber;
extern std::string g_strUserPath;
extern std::string g_strClientPath;
extern bool g_bTranscode;
extern bool g_bUsePIN;
extern int g_iBitrate;

extern ADDON::CHelper_libXBMC_addon* XBMC;
extern CHelper_libXBMC_pvr* PVR;

extern std::string PathCombine(const std::string& strPath, const std::string& strFileName);
extern std::string GetClientFilePath(const std::string& strFileName);
extern std::string GetUserFilePath(const std::string& strFileName);
