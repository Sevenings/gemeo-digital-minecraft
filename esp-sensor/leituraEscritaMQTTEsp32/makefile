# Version 1.0

SKETCH=leituraEscritaMQTTEsp32.ino
COMPLEMENTS=
FQBN=esp32:esp32:esp32
PORT=/dev/ttyACM0
BAUDRATE=115200

# https://arduino.github.io/arduino-cli/0.35/getting-started/

build: $(SKETCH) $(COMPLEMENTS)
	arduino-cli compile --fqbn $(FQBN) --build-path build 

compile: $(SKETCH) $(COMPLEMENTS)
	arduino-cli compile --fqbn $(FQBN) 

run:
	arduino-cli upload -p $(PORT) --fqbn $(FQBN)

monitor:
	arduino-cli monitor -p $(PORT) -c baudrate=$(BAUDRATE)

clear:
	rm -r build

all: compile run monitor

