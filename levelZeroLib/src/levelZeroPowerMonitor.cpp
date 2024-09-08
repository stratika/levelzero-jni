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
#include "levelZeroPowerMonitor.h"

#include <iostream>
#include <vector>


#include "ze_api.h"
#include "ze_log.h"
#include "zes_api.h"



bool IsIntegratedGPU(zes_device_handle_t hSysmanDevice) {
    uint32_t numPowerDomains = 0;
    ze_result_t result = zesDeviceEnumPowerDomains(hSysmanDevice, &numPowerDomains, nullptr);
    LOG_ZE_JNI("zesDeviceEnumPowerDomains", result);
    return numPowerDomains == 0;
}

/*
 * Class:     uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroPowerMonitor
 * Method:    ZesInit
 * Signature: ()[J
 */

JNIEXPORT jlongArray JNICALL Java_uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroPowerMonitor_ZesInit
  (JNIEnv* env, jobject obj, jlongArray jDeviceHandles) {
    
    jsize length = env->GetArrayLength(jDeviceHandles);
    jlong* deviceElements = env->GetLongArrayElements(jDeviceHandles, nullptr);

    std::vector<zes_device_handle_t> sysmanHandles;

    for (jsize i = 0; i < length; ++i) {
        ze_device_handle_t deviceHandle = reinterpret_cast<ze_device_handle_t>(deviceElements[i]);
        zes_device_handle_t sysmanHandle = reinterpret_cast<zes_device_handle_t>(deviceHandle);
        sysmanHandles.push_back(sysmanHandle);
    }

    env->ReleaseLongArrayElements(jDeviceHandles, deviceElements, 0);

    jlongArray result = env->NewLongArray(sysmanHandles.size());
    jlong* sysmanElements = env->GetLongArrayElements(result, nullptr);

    for (size_t i = 0; i < sysmanHandles.size(); ++i) {
        sysmanElements[i] = reinterpret_cast<jlong>(sysmanHandles[i]);
    }

    env->ReleaseLongArrayElements(result, sysmanElements, 0);

    return result;
}


/*
 * Class:     uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroPowerMonitor
 * Method:    checkPowerQueryPossible
 * Signature: ([J)I
 */
JNIEXPORT jint JNICALL Java_uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroPowerMonitor_checkPowerQueryPossible
  (JNIEnv* env, jobject obj, jlongArray jSysmanDevices){

    jsize length = env->GetArrayLength(jSysmanDevices);
    std::vector<zes_device_handle_t> allSysmanDevices(length);
    jlong* elements = env->GetLongArrayElements(jSysmanDevices, nullptr);

    for (jsize i = 0; i < length; ++i) {
        allSysmanDevices[i] = reinterpret_cast<zes_device_handle_t>(elements[i]);
    }

    env->ReleaseLongArrayElements(jSysmanDevices, elements, 0);

    if (allSysmanDevices.empty()) {
        return -1; // No Sysman devices found
    }

    std::vector<zes_device_handle_t>  sysmanDevicesToQuery;
    for (auto& sysmanDevice : allSysmanDevices) {
        if (!IsIntegratedGPU(sysmanDevice)) {
            sysmanDevicesToQuery.push_back(sysmanDevice);
        }
    }
   
    if (sysmanDevicesToQuery.empty()) {
        return -2; // All iGPUs - Cannot calculate power consumption
    }
    else{
        return 0; //Success
    }

}

/*
 * Class:     uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroPowerMonitor
 * Method:    getSysmanDevicesToQuery
 * Signature: ([J)[J
 */
JNIEXPORT jlongArray JNICALL Java_uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroPowerMonitor_getSysmanDevicesToQuery
  (JNIEnv* env, jobject obj, jlongArray jSysmanDevices){

    // Convert jlongArray to a C++ array
    jsize length = env->GetArrayLength(jSysmanDevices);
    jlong* sysmanDevices = env->GetLongArrayElements(jSysmanDevices, NULL);

    std::vector<jlong> sysmanDevicesToQuery;

    for (jsize i = 0; i < length; ++i) {
        jlong sysmanDevice = sysmanDevices[i];
        
        // Cast jlong to zes_device_handle_t
        zes_device_handle_t hSysmanDevice = reinterpret_cast<zes_device_handle_t>(sysmanDevice);
        if (!IsIntegratedGPU(hSysmanDevice)) {
            sysmanDevicesToQuery.push_back(sysmanDevice);
        }
    }

    env->ReleaseLongArrayElements(jSysmanDevices, sysmanDevices, 0);

    jlongArray sysmanDevicesArray = env->NewLongArray(sysmanDevicesToQuery.size());
    if (sysmanDevicesArray == NULL) {
        return NULL; // Out of memory error
    }

    env->SetLongArrayRegion(sysmanDevicesArray, 0, sysmanDevicesToQuery.size(), sysmanDevicesToQuery.data());

    return sysmanDevicesArray;

}

/*
 * Class:     uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroPowerMonitor
 * Method:    getEnergyCounters
 * Signature: (J)Ljava/util/List;
 */
JNIEXPORT jobject JNICALL Java_uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroPowerMonitor_getEnergyCounters
  (JNIEnv *env, jobject obj, jlong sysmanDeviceHandle){

    zes_device_handle_t hSysmanDevice = reinterpret_cast<zes_device_handle_t>(sysmanDeviceHandle);

    uint32_t numPowerDomains = 0;
    ze_result_t result = zesDeviceEnumPowerDomains(hSysmanDevice, &numPowerDomains, nullptr);
    #ifdef LOG_JNI
    LOG_ZE_JNI("zesDeviceEnumPowerDomains", result);
    #endif

    std::vector<zes_pwr_handle_t> powerHandles(numPowerDomains);
    result = zesDeviceEnumPowerDomains(hSysmanDevice, &numPowerDomains, powerHandles.data());
    #ifdef LOG_JNI
    LOG_ZE_JNI("zesDeviceEnumPowerDomains", result);
    #endif

    jclass arrayListClass = env->FindClass("java/util/ArrayList");
    jmethodID arrayListConstructor = env->GetMethodID(arrayListClass, "<init>", "()V");
    jobject energyCounterList = env->NewObject(arrayListClass, arrayListConstructor);
    jmethodID arrayListAdd = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");

    jclass energyCounterClass = env->FindClass("uk/ac/manchester/tornado/drivers/spirv/levelzero/ZesPowerEnergyCounter");
    jmethodID energyCounterConstructor = env->GetMethodID(energyCounterClass, "<init>", "(JJ)V");

    for (auto &powerHandle : powerHandles) {
        zes_power_energy_counter_t energyCounter = {};
        result = zesPowerGetEnergyCounter(powerHandle, &energyCounter);
        #ifdef LOG_JNI
        LOG_ZE_JNI("zesPowerGetEnergyCounter", result);
        #endif
        if (result == ZE_RESULT_SUCCESS) {
            jobject energyCounterObject = env->NewObject(energyCounterClass, energyCounterConstructor, 
                                                         static_cast<jlong>(energyCounter.energy),
                                                         static_cast<jlong>(energyCounter.timestamp));
            env->CallBooleanMethod(energyCounterList, arrayListAdd, energyCounterObject);
        }
    }

    return energyCounterList;

}


/*
 * Class:     uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroPowerMonitor
 * Method:    calculatePowerUsage
 * Signature: (Luk/ac/manchester/tornado/drivers/spirv/levelzero/ZesPowerEnergyCounter;Luk/ac/manchester/tornado/drivers/spirv/levelzero/ZesPowerEnergyCounter;)D
 */
JNIEXPORT jdouble JNICALL Java_uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroPowerMonitor_calculatePowerUsage
  (JNIEnv *env, jobject obj, jobject initialEnergyCounters, jobject finalEnergyCounters){
    
    jclass arrayListClass = env->GetObjectClass(initialEnergyCounters);
    jmethodID getMethod = env->GetMethodID(arrayListClass, "get", "(I)Ljava/lang/Object;");
    jmethodID sizeMethod = env->GetMethodID(arrayListClass, "size", "()I");

    
    jint size = env->CallIntMethod(initialEnergyCounters, sizeMethod);
    
    jclass energyCounterClass = env->FindClass("uk/ac/manchester/tornado/drivers/spirv/levelzero/ZesPowerEnergyCounter");
    jfieldID energyField = env->GetFieldID(energyCounterClass, "energy", "J");
    jfieldID timestampField = env->GetFieldID(energyCounterClass, "timestamp", "J");

    uint64_t totalEnergyUsed = 0;
    uint64_t totalTimeElapsed = 0;

    for (jint i = 0; i < size; ++i) {
       
        jobject initialEnergyCounter = env->CallObjectMethod(initialEnergyCounters, getMethod, i);
        jobject finalEnergyCounter = env->CallObjectMethod(finalEnergyCounters, getMethod, i);

        jlong initialEnergy = env->GetLongField(initialEnergyCounter, energyField);
        jlong initialTimestamp = env->GetLongField(initialEnergyCounter, timestampField);
        jlong finalEnergy = env->GetLongField(finalEnergyCounter, energyField);
        jlong finalTimestamp = env->GetLongField(finalEnergyCounter, timestampField);

        // Calculate energy used and time elapsed for this domain
        totalEnergyUsed += finalEnergy - initialEnergy;
        totalTimeElapsed += finalTimestamp - initialTimestamp;
    }

    
    double powerConsumption = (static_cast<double>(totalTimeElapsed) != 0) 
        ? (static_cast<double>(totalEnergyUsed) / totalTimeElapsed) * 1000 
        : 0.0; // mW

    return powerConsumption;

}

/*
 * Class:     uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroPowerMonitor
 * Method:    zesDeviceEnumPowerDomains_native
 * Signature: (J[I[J)I
 */
JNIEXPORT jint JNICALL Java_uk_ac_manchester_tornado_drivers_spirv_levelzero_sysman_PowerFunctions_zesDeviceEnumPowerDomains_1native
  (JNIEnv *env, jobject object, jlong deviceHandler, jintArray numPowerDomains, jlongArray hMemory) {
    auto hDevice = reinterpret_cast<ze_device_handle_t>(deviceHandler);
    jint *arrayContent = static_cast<jint *>(env->GetIntArrayElements(numPowerDomains, 0));
    auto pCount = (uint32_t) arrayContent[0];
    ze_result_t result = zesDeviceEnumPowerDomains(hDevice, &pCount, nullptr);
    #ifdef LOG_JNI
    LOG_ZE_JNI("zesDeviceEnumPowerDomains", result);
    #endif
    arrayContent[0] = pCount;
    env->ReleaseIntArrayElements(numPowerDomains, arrayContent, 0);
    return result;
}

