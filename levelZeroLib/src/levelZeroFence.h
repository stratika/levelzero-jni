/*
 * MIT License
 *
 * Copyright (c) 2021, APT Group, Department of Computer Science,
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
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroFence */

#ifndef _Included_uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroFence
#define _Included_uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroFence
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroFence
 * Method:    zeFenceCreate_native
 * Signature: (JLuk/ac/manchester/tornado/drivers/spirv/levelzero/ZeFenceDesc;Luk/ac/manchester/tornado/drivers/spirv/levelzero/ZeFenceHandle;)I
*/
JNIEXPORT jint JNICALL Java_uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroFence_zeFenceCreate_1native
    (JNIEnv *, jobject, jlong, jobject, jobject);

/*
 * Class:     uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroFence
 * Method:    zeFenceHostSynchronize_native
 * Signature: (JJ)I
 */
    JNIEXPORT jint JNICALL Java_uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroFence_zeFenceHostSynchronize_1native
    (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroFence
 * Method:    zeFenceReset_native
 * Signature: (J)I
*/
JNIEXPORT jint JNICALL Java_uk_ac_manchester_tornado_drivers_spirv_levelzero_LevelZeroFence_zeFenceReset_1native
    (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif