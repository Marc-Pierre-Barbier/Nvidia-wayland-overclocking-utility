#include "nvml.h"
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static nvmlReturn_t setClock(nvmlDevice_t * device, long offset, nvmlClockType_t type) {
	nvmlClockOffset_t nvmlOffset;
	memset(&nvmlOffset, 0, sizeof(nvmlOffset));
	nvmlOffset.version = nvmlClockOffset_v1;
	nvmlOffset.clockOffsetMHz = offset;
	nvmlOffset.type = type;//nvmlClockType_t::NVML_CLOCK_GRAPHICS;
	nvmlPstates_t pstates[] = { NVML_PSTATE_0, NVML_PSTATE_1, NVML_PSTATE_2, NVML_PSTATE_3, NVML_PSTATE_4, NVML_PSTATE_5, NVML_PSTATE_6, NVML_PSTATE_7, NVML_PSTATE_8, NVML_PSTATE_9, NVML_PSTATE_10, NVML_PSTATE_11, NVML_PSTATE_12, NVML_PSTATE_13, NVML_PSTATE_14, NVML_PSTATE_15 };

	for(unsigned long i = 0; i < sizeof(pstates) / sizeof(nvmlPstates_t); i++) {
		nvmlOffset.pstate = pstates[i];
	}
	return nvmlDeviceSetClockOffsets(*device, &nvmlOffset);
}

int main(int argc, char ** argv) {
	if(argc != 4) {
	usage:
		printf("format %s [CORE] [MEM] [SM]\n", argv[0]);
		return EXIT_FAILURE;
	}
	long core = strtol(argv[1], NULL, 10);
	if(errno != 0) goto usage;
	long mem = strtol(argv[2], NULL, 10);
	if(errno != 0) goto usage;
	long sm = strtol(argv[3], NULL, 10);
	if(errno != 0) goto usage;

	nvmlInit();

	nvmlDevice_t device;
	nvmlReturn_t result = nvmlDeviceGetHandleByIndex_v2(0, &device);
	if(result != NVML_SUCCESS) {
		printf("Failed to get device: %s\n", nvmlErrorString(result));
		return EXIT_FAILURE;
	}

	result = setClock(&device, core, NVML_CLOCK_GRAPHICS);
	if(result != NVML_SUCCESS) {
		printf("CORE: Failed to set clock: %s\n", nvmlErrorString(result));
	} else {
		printf("Core clock set!\n");
	}

	result = setClock(&device, mem, NVML_CLOCK_MEM);
	if(result != NVML_SUCCESS) {
		printf("MEM: Failed to set clock: %s\n", nvmlErrorString(result));
	} else {
		printf("Mem clock set!\n");
	}

	result = setClock(&device, sm, NVML_CLOCK_SM);
	if(result != NVML_SUCCESS) {
		printf("SM: Failed to set clock: %s\n", nvmlErrorString(result));
	} else {
		printf("SM clock set!\n");
	}
}
