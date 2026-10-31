// SONIC ROBO BLAST 2 - port NumWorks
// Nom et niveau d'API de l'app, lus par la calculatrice
#include <stdint.h>

const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "SRB2";
const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;
