build_run: build run
.PHONY: build_run

build:
	@cd Build && make
.PHONY: build

debug:
	-@rm -r Build
	@mkdir Build
	@cd Build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make
.PHONY: debug

release:
	-@rm -r Build
	@mkdir Build
	@cd Build && cmake -DCMAKE_BUILD_TYPE=Release .. && make
.PHONY: release

run:
	@cd Build/Binaries && ./GameEngine
.PHONY: run

val:
	@cd Build/Binaries && valgrind ./GameEngine
.PHONY: val

gdb:
	@cd Build/Binaries && gdb ./GameEngine
.PHONY: gdb

clean:
	-@rm -r Build
.PHONY: clean
