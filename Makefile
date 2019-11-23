build:
	scons

clean:
	rm .sconsign.dblite
	scons -c

.PHONY: build clean