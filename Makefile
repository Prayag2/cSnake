srcFiles := $(wildcard src/*.c)
headerFiles := $(wildcard src/*.h)
buildDir := bin
buildTarget := ${buildDir}/main

run: build
	sh -c ${buildTarget}

build: ${buildTarget}
${buildTarget}: ${srcFiles} ${headerFiles} ${buildDir}
	gcc ${srcFiles} -lncurses -o ${buildTarget}
${buildDir}:
	mkdir -p $@
