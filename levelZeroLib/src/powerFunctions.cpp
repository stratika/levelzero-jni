/*
 * MIT License
 *
 * Copyright (c) 2024, APT Group, Department of Computer Science,
 * The University of Manchester.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "powerFunctions.h"

#include <iostream>
#include <sstream>

#include "zes_api.h"
#include "ze_log.h"

/*
 * Class:     uk_ac_manchester_tornado_drivers_spirv_levelzero_sysman_PowerFunctions
 * Method:    zesDeviceEnumPowerDomains_native
 * Signature: (J[I[J)I
 */
JNIEXPORT jint JNICALL Java_uk_ac_manchester_tornado_drivers_spirv_levelzero_sysman_PowerFunctions_zesDeviceEnumPowerDomains_1native
  (JNIEnv *env, jobject object, jlong deviceHandler, jintArray numPowerDomains, jlongArray hMemory) {
    auto hDevice = reinterpret_cast<ze_device_handle_t>(deviceHandler);
    jint *arrayContent = static_cast<jint *>(env->GetIntArrayElements(numPowerDomains, 0));
    auto pCount = (uint32_t) arrayContent[0];
    ze_result_t result = zesDeviceEnumPowerDomains(hDevice, &pCount, nullptr);
    LOG_ZE_JNI("zesDeviceEnumPowerDomains", result);

    arrayContent[0] = pCount;
    env->ReleaseIntArrayElements(numPowerDomains, arrayContent, 0);
    return result;
}