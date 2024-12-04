#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define SYSFS_PATH "/sys/devices/platform/soc/soc:surface_util/ms_pen_charger/ms_pen_charger"

// Function to check if the file exists
int file_exists(const char *path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

// Function to read the sysfs file
jstring Java_com_thain_duo_MSPenCharger_readSysfs(JNIEnv *env, jobject obj) {
    if (!file_exists(SYSFS_PATH)) {
        return (*env)->NewStringUTF(env, "Error: File does not exist");
    }

    FILE *file = fopen(SYSFS_PATH, "r");
    if (file == NULL) {
        return (*env)->NewStringUTF(env, "Error: Unable to open file");
    }

    char buffer[128];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        return (*env)->NewStringUTF(env, "Error: Unable to read file");
    }

    fclose(file);
    return (*env)->NewStringUTF(env, buffer);
}

// Function to turn the pencharger on
jstring Java_com_thain_duo_MSPenCharger_turnOnPenCharger(JNIEnv *env, jobject obj) {
    if (!file_exists(SYSFS_PATH)) {
        return (*env)->NewStringUTF(env, "Error: File does not exist");
    }

    FILE *file = fopen(SYSFS_PATH, "r");

    fprintf(file, "0");
    fclose(file);

    fclose(file);
    return (*env)->NewStringUTF(env, buffer);
}

// Function to turn the pencharger off
jstring Java_com_thain_duo_MSPenCharger_turnOffPenCharger(JNIEnv *env, jobject obj) {
    if (!file_exists(SYSFS_PATH)) {
        return (*env)->NewStringUTF(env, "Error: File does not exist");
    }

    FILE *file = fopen(SYSFS_PATH, "r");

    fprintf(file, "1");
    fclose(file);

    fclose(file);
    return (*env)->NewStringUTF(env, buffer);
}

// Function to write to the sysfs file
void Java_com_thain_duo_MSPenCharger_writeSysfs(JNIEnv *env, jobject obj, jstring value) {
    if (!file_exists(SYSFS_PATH)) {
        return; // File does not exist, so do nothing
    }

    const char *nativeValue = (*env)->GetStringUTFChars(env, value, 0);

    FILE *file = fopen(SYSFS_PATH, "w");
    if (file != NULL) {
        fprintf(file, "%s", nativeValue);
        fclose(file);
    }

    (*env)->ReleaseStringUTFChars(env, value, nativeValue);
}
