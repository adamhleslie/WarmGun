debug:
	@rm -r Build
	@mkdir Build
	@cd Build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make

release:
	@rm -r Build
	@mkdir Build
	@cd Build && cmake -DCMAKE_BUILD_TYPE=Release .. && make

run:
	@cd Build/Binaries && ./GameEngine

val:
	@cd Build/Binaries && valgrind ./GameEngine

gdb:
	@cd Build/Binaries && gdb ./GameEngine
