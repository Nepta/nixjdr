# GNU Make solution makefile autogenerated by Premake
# Type "make help" for usage help

ifndef config
  config=debug
endif
export config

PROJECTS := map.bin

.PHONY: all clean help $(PROJECTS)

all: $(PROJECTS)

map.bin: 
	@echo "==== Building map.bin ($(config)) ===="
	@${MAKE} --no-print-directory -C . -f map.bin.make

clean:
	@${MAKE} --no-print-directory -C . -f map.bin.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "   debug"
	@echo "   release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   map.bin"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
