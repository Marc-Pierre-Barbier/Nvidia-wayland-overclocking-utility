#include "nvml.h"
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static nvmlReturn_t setClock(nvmlDevice_t * device, long state, long offset, nvmlClockType_t type) {
	nvmlClockOffset_t nvmlOffset;
	memset(&nvmlOffset, 0, sizeof(nvmlOffset));
	nvmlOffset.version = nvmlClockOffset_v1;
	nvmlOffset.clockOffsetMHz = offset;
	nvmlOffset.type = type;//nvmlClockType_t::NVML_CLOCK_GRAPHICS;
	nvmlPstates_t pstates[] = { NVML_PSTATE_0, NVML_PSTATE_1, NVML_PSTATE_2, NVML_PSTATE_3, NVML_PSTATE_4, NVML_PSTATE_5, NVML_PSTATE_6, NVML_PSTATE_7, NVML_PSTATE_8, NVML_PSTATE_9, NVML_PSTATE_10, NVML_PSTATE_11, NVML_PSTATE_12, NVML_PSTATE_13, NVML_PSTATE_14, NVML_PSTATE_15 };
	nvmlOffset.pstate = pstates[state];
	return nvmlDeviceSetClockOffsets(*device, &nvmlOffset);
}

void setClocks(nvmlDevice_t * device, long state, long core, long mem, long sm) {
	nvmlReturn_t result = setClock(device, state, core, NVML_CLOCK_GRAPHICS);
	if(result != NVML_SUCCESS) {
		printf("CORE: Failed to set clock: %s PSTATE%ld\n", nvmlErrorString(result), state);
	} else {
		printf("Core clock set!\n");
	}

	result = setClock(device, state, mem, NVML_CLOCK_MEM);
	if(result != NVML_SUCCESS) {
		printf("MEM: Failed to set clock: %s PSTATE%ld\n", nvmlErrorString(result), state);
	} else {
		printf("Mem clock set!\n");
	}

	result = setClock(device, sm, state, NVML_CLOCK_SM);
	if(result != NVML_SUCCESS) {
		printf("SM: Failed to set clock: %s PSTATE%ld\n", nvmlErrorString(result), state);
	} else {
		printf("SM clock set!\n");
	}
}

int main(int argc, char ** argv) {
	if(argc != 5) {
	usage:
		printf("format %s [PSTATE or -1 for all] [CORE] [MEM] [SM]\n", argv[0]);
		return EXIT_FAILURE;
	}
	long core = strtol(argv[2], NULL, 10);
	if(errno != 0) goto usage;
	long mem = strtol(argv[3], NULL, 10);
	if(errno != 0) goto usage;
	long sm = strtol(argv[4], NULL, 10);
	if(errno != 0) goto usage;
	long state = strtol(argv[1], NULL, 10);
	if(errno != 0) goto usage;

	if(state != -1 && state > 15)
		goto usage;

	nvmlInit();

	nvmlDevice_t device;
	nvmlReturn_t result = nvmlDeviceGetHandleByIndex_v2(0, &device);
	if(result != NVML_SUCCESS) {
		printf("Failed to get device: %s\n", nvmlErrorString(result));
		return EXIT_FAILURE;
	}

	if(state != -1) {
		setClocks(&device, state, core, mem, sm);
	} else {
		for(int i = 0; i < 16; i++) {
			setClocks(&device, i, core, mem, sm);
		}
	}


}
