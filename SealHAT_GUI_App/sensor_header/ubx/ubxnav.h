/*
 * SealHAT
 * Anthony Koutroulis
 * modified from ubxproto library by Alexey Edelev aka semlanik
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 *
 * Additionally to GNU Lesser General Public License you MUST NOT
 * static link this library and MUST add link to author
 * and source of this library in your application.
 *
 * Actual LGPL text https://www.gnu.org/licenses/lgpl.html
 *
 * File: ubxlog.h
 */

#ifndef UBLOXNAV_H
#define UBLOXNAV_H

#include "ubxmessage.h"
#ifdef __cplusplus
extern "C"
{
#endif

extern UBXMsgBuffer getNAV_PVT_POLL();

#ifdef __cplusplus
}
#endif

#endif // UBLOXNAV_H

