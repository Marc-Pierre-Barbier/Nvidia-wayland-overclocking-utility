gcc -c src/main.c
gcc -o nvoc main.o /usr/lib64/libnvidia-ml.so
rm main.o
