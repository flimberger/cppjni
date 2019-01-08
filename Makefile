CMAKE?=	cmake
CTEST?=	ctest

OBJ_DIR?=	${PWD}

all:	test
.PHONY:	all

test:	build
	cd ${OBJ_DIR} && ${CTEST} -V
.PHONY:	test

build:
	${CMAKE} --build ${OBJ_DIR}
.PHONY:	build

clean:
	${CMAKE} --build ${OBJ_DIR} --target clean
.PHONY:	clean
