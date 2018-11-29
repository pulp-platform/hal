build:
	scons | grep -v "is up to date"

clean:
	scons -c

.PHONY: build clean