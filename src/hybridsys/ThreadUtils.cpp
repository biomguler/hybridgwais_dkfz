/*
 *    Copyright (C) 2018-2023 by Lars Wienbrandt and Jan Christian Kässens,
 *    Institute of Clinical Molecular Biology, Kiel University
 *    
 *    This file is part of HybridGWAIS.
 *
 *    HybridGWAIS is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    HybridGWAIS is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with HybridGWAIS. If not, see <https://www.gnu.org/licenses/>.
 */

// exposes the non-standard pthread_setname_np() function
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <pthread.h>

#include <thread>
#include <cstring>
#include <array>

#include "ThreadUtils.h"

using namespace std;

/*static*/ const unsigned long ThreadUtils::MAX_THREAD_NAME_LEN = 16; /* see man page PTHREAD_SETNAME_NP(3) */

void ThreadUtils::setThreadName(const string& newname) {
    array<char, MAX_THREAD_NAME_LEN> c_newname;
    memcpy(c_newname.data(), newname.c_str(), max(newname.length(), MAX_THREAD_NAME_LEN-1));
    c_newname[MAX_THREAD_NAME_LEN-1] = 0;

    pthread_setname_np(pthread_self(), c_newname.data());
}
