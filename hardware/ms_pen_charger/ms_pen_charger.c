#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define SYSFS_PATH "/sys/devices/platform/soc/soc:surface_util/ms_pen_charger/ms_pen_charger"

// Function to turn the pencharger on
jint Java_me_phh_treble_app_MSPenCharger_turnOnPenCharger(JNIEnv *env, jobject obj) {
    FILE *file = fopen(SYSFS_PATH, "w");
    if (!file) {
        return 1;
    }
    fprintf(file, "0");
    fclose(file);

    return 0;
}

// Function to turn the pencharger off
jint Java_me_phh_treble_app_MSPenCharger_turnOffPenCharger(JNIEnv *env, jobject obj) {

    FILE *file = fopen(SYSFS_PATH, "w");
    if (!file) {
        return 1;
    }
    fprintf(file, "1");
    fclose(file);

    return 0;
}

// read the pencharger status
jint Java_me_phh_treble_app_MSPenCharger_readPenCharger(JNIEnv *env, jobject obj) {

    FILE *file = fopen(SYSFS_PATH, "r");
    if (!file) {
        return -1;
    }
    char buffer[16];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error reading file");
        fclose(file);
        return -1; // Return an error code if the file cannot be read
    }
    fclose(file);

    // Convert the read content to an integer
    int status = atoi(buffer);
    return status;
}