GCC_ARGS = `pkg-config --cflags --libs glib-2.0` -Iinclude -Isricd/libsric

all:
	gcc -c $(GCC_ARGS) -o obj/power.o src/power.c
	gcc -c $(GCC_ARGS) -o obj/motor.o src/motor.c
	gcc -c $(GCC_ARGS) -o obj/servo.o src/servo.c
	gcc -c $(GCC_ARGS) -o obj/jio.o src/jio.c
	gcc -c $(GCC_ARGS) -o obj/srhw_internal.o src/srhw_internal.c
	gcc -c $(GCC_ARGS) -o obj/srhw.o src/srhw.c

	gcc -Wl -o bin/libsrhw \
		obj/srhw.o obj/power.o obj/motor.o obj/servo.o obj/jio.o obj/srhw_internal.o \
		-Lsricd/libsric -lsric -lglib-2.0
