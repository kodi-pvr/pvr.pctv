/*
 *  Copyright (C) 2005-2021 Team Kodi (https://kodi.tv)
 *  Copyright (C) 2011 Pulse-Eight
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "addon.h"

#include "PctvData.h"

#include <kodi/Filesystem.h>
#include <kodi/tools/StringUtils.h>

using kodi::tools::StringUtils;

ADDON_STATUS CPCTVAddon::CreateInstance(const kodi::addon::IInstanceInfo& instance,
                                        KODI_ADDON_INSTANCE_HDL& hdl)
{
  if (instance.IsType(ADDON_INSTANCE_PVR))
  {
    kodi::Log(ADDON_LOG_DEBUG, "%s - Creating PCTV Systems PVR-Client", __func__);

    if (!kodi::vfs::DirectoryExists(kodi::addon::GetUserPath()))
    {
      kodi::vfs::CreateDirectory(kodi::addon::GetUserPath());
    }

    m_strHostname = kodi::addon::GetSettingString("host", DEFAULT_HOST);
    m_iPortWeb = kodi::addon::GetSettingInt("webport", DEFAULT_WEB_PORT);
    m_bUsePIN = kodi::addon::GetSettingBoolean("usepin", DEFAULT_USEPIN);
    m_strPin = StringUtils::Format("%04i", kodi::addon::GetSettingInt("pin", 0));
    m_strMimeType.clear();
    m_bUseMpegTSMimeType = kodi::addon::GetSettingBoolean("usempegts", DEFAULT_USE_MPEGTS);
    if (m_bUseMpegTSMimeType)
      m_strMimeType = MPEGTS_MIMETYPE;
    else
      m_strMimeType = kodi::addon::GetSettingString("mimetype", "");
    m_bTranscode = kodi::addon::GetSettingBoolean("transcode", DEFAULT_TRANSCODE);
    m_iBitrate = kodi::addon::GetSettingInt("bitrate", DEFAULT_BITRATE);

    Pctv* usedInstance = new Pctv(m_strHostname, m_iPortWeb, m_strPin, m_strMimeType,
                                  m_iBitrate, m_bTranscode, m_bUsePIN, instance);
    hdl = usedInstance;
    m_usedInstances.emplace(instance.GetID(), usedInstance);

    if (!usedInstance->Open())
      return ADDON_STATUS_LOST_CONNECTION;

    return ADDON_STATUS_OK;
  }

  return ADDON_STATUS_UNKNOWN;
}

void CPCTVAddon::DestroyInstance(const kodi::addon::IInstanceInfo& instance,
                                 const KODI_ADDON_INSTANCE_HDL hdl)
{
  if (instance.IsType(ADDON_INSTANCE_PVR))
  {
    kodi::Log(ADDON_LOG_DEBUG, "%s: Destoying octonet pvr instance", __func__);

    const auto& it = m_usedInstances.find(instance.GetID());
    if (it != m_usedInstances.end())
    {
      m_usedInstances.erase(it);
    }
  }
}

ADDON_STATUS CPCTVAddon::SetSetting(const std::string& settingName,
                                    const kodi::addon::CSettingValue& settingValue)
{
  if (settingName == "host")
  {
    if (m_strHostname != settingValue.GetString())
    {
      kodi::Log(ADDON_LOG_INFO, "%s - Changed Setting 'host' from %s to %s", __func__,
                m_strHostname.c_str(), settingValue.GetString().c_str());
      return ADDON_STATUS_NEED_RESTART;
    }
  }
  else if (settingName == "webport")
  {
    if (m_iPortWeb != settingValue.GetInt())
    {
      kodi::Log(ADDON_LOG_INFO, "%s - Changed Setting 'webport' from %u to %u", __func__,
                m_iPortWeb, settingValue.GetInt());
      return ADDON_STATUS_NEED_RESTART;
    }
  }
  else if (settingName == "usepin")
  {
    if (m_bUsePIN != settingValue.GetBoolean())
    {
      kodi::Log(ADDON_LOG_INFO, "%s - Changed Setting 'usepin'", __func__);
      return ADDON_STATUS_NEED_RESTART; // restart is needed
    }
  }
  else if (settingName == "pin")
  {
    if (m_strPin != StringUtils::Format("%04i", settingValue.GetInt()))
    {
      kodi::Log(ADDON_LOG_INFO, "%s - Changed Setting 'pin'", __func__);
      return ADDON_STATUS_NEED_RESTART;
    }
  }
  else if (settingName == "transcode")
  {
    if (m_bTranscode != settingValue.GetInt())
    {
      kodi::Log(ADDON_LOG_INFO, "%s - Changed Setting 'transcode'", __func__);
      return ADDON_STATUS_NEED_RESTART; // restart is needed to update strStreamURL in Channel entries
    }
  }
  else if (settingName == "bitrate")
  {
    if (m_iBitrate != settingValue.GetInt())
    {
      kodi::Log(ADDON_LOG_INFO, "%s - Changed Setting 'bitrate' from %u to %u", __func__,
                m_iBitrate, settingValue.GetInt());
      return ADDON_STATUS_NEED_RESTART; // restart is needed to update strStreamURL in Channel entries
    }
  }

  return ADDON_STATUS_OK;
}

ADDONCREATOR(CPCTVAddon)
