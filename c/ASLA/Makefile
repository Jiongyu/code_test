CC:=gcc
OBJECT_PLAY:=./player
OBJECT_RECORDER:=./recorder

PLAY:=./player.c
RECORD:=./recorder.c

make:
	${CC} ${PLAY} -o ${OBJECT_PLAY} -lasound
	${CC} ${RECORD} -o ${OBJECT_RECORDER} -lasound

clean:
	rm -rf ${OBJECT_PLAY} ${OBJECT_RECORDER}