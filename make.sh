x86_64-w64-mingw32-gcc -c main.c \
&& x86_64-w64-mingw32-gcc -o notepad.exe main.o \
&& rm main.o \
&& open $PWD
