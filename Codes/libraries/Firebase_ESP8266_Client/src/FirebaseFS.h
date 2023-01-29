#ifndef FirebaseFS_H
#define FirebaseFS_H
#include <Arduino.h>

#pragma once

#define FIREBASE_ESP8266_CLIENT 1

/**
 * To use other flash file systems
 *
 * LittleFS File system
 *
 * #include <LittleFS.h>
 * #define DEFAULT_FLASH_FS LittleFS //For ESP8266 LitteFS
 *
 *
 * FAT File system
 *
 * #include <FFat.h>
 * #define DEFAULT_FLASH_FS FFat  //For ESP32 FAT
 *
 */
#if defined(ESP8266) || defined(ESP32)
#define DEFAULT_FLASH_FS SPIFFS
#endif

/**
 * To use SD card file systems with different hardware interface
 * e.g. SDMMC hardware bus on the ESP32
 * https://github.com/espressif/arduino-esp32/tree/master/libraries/SD#faq
 *
 * #include <SD_MMC.h>
 * #define DEFAULT_SD_FS SD_MMC //For ESP32 SDMMC
 *
 */

#if defined(ESP8266) || defined(ESP32)
#include <SD.h>
#define DEFAULT_SD_FS SD
#define CARD_TYPE_SD 1
#endif

// Comment to exclude the Firebase Realtime Database
#define ENABLE_RTDB

#define ENABLE_ERROR_QUEUE

// Comment to exclude Firebase Cloud Messaging
#define ENABLE_FCM

/** Use PSRAM for supported ESP8266 module */
#define FIREBASE_USE_PSRAM

// To enable OTA updates
#define ENABLE_OTA_FIRMWARE_UPDATE

// For ESP8266 W5100 Ethernet module
// #define ENABLE_ESP8266_W5100_ETH


// To enable external Client for ESP8266.
// This will enable automatically for other devices.
// #define FB_ENABLE_EXTERNAL_CLIENT


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// You can create your own header file "CustomFirebaseFS.h" in the same diectory of 
// "FirebaseFS.h" and put your own custom config to overwrite or 
// change the default config in "FirebaseFS.h".
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

/** This is an example of "CustomFirebaseFS.h" 

#pragma once

#ifndef CustomFirebaseFS_H
#define CustomFirebaseFS_H

// Use external client instead of internal client
#define FB_ENABLE_EXTERNAL_CLIENT // define to use external client

// Use LittleFS instead of SPIFFS
#include "LittleFS.h"
#undef DEFAULT_FLASH_FS // remove Flash FS defined macro
#define DEFAULT_FLASH_FS LittleFS

// Disable Error Queue and FCM.
#undef ENABLE_ERROR_QUEUE
#undef ENABLE_FCM

#endif

*/
#if __has_include("CustomFirebaseFS.h")
#include "CustomFirebaseFS.h"
#endif

#endif