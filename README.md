# Quick and dirty nvml nvidia clock setter

Nvidia just release the nvidia 555 beta driver which fixes a lot of wayland issues.

But also add nvmlDeviceSetClockOffsets which allows to overclock on wayland.
sadly they didn't provide an integration into nvidia-settings so this is why this program exists.

# THIS PROJECT WAS RUSHED AND COME WITH ABSOLUTELY NOT GUARANTEE

## build

just run the build.sh it will output the "nvoc" executable

## FORMAT

format ./nvoc [CORE] [MEM] [SM]
