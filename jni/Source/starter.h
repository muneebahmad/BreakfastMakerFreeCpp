/*
 * starter.h
 *
 *  Created on: 03-Jan-2015
 *      Author: muneebahmad
 */

#ifndef STARTER_H_
#define STARTER_H_

#include <jni.h>

#include <WiEngine.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_algorithmi_maker_breakfast_free_main_MainActivity_nativeKick(JNIEnv*, jobject);

void startGame(wyScene* scene);

#ifdef __cplusplus
}
#endif

#endif /* STARTER_H_ */
