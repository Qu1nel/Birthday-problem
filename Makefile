TARGET 		:= main

EXTERN_LIBS := 

SRC_DIR     := src
INCLD_DIR 	:= include
OBJ_DIR     := objects

CC 			:= clang
CFLAGS 		:= -std=c17 -Wall -Wextra -Werror -Wshadow -Wvla -Walloca -Wundef -Wfloat-equal \
			   -Wstrict-prototypes -Wconversion -Wswitch-enum -Wswitch-default -Wimplicit-fallthrough \
			   -Wunreachable-code -Wformat=2 -Wparentheses -Wmisleading-indentation -Wpedantic -pedantic -O2

CPPFLAGS 	:= -I$(INCLD_DIR)
LDFLAGS 	:= $(addprefix -l,$(EXTERN_LIBS))

OBJECTS     := $(patsubst %.c, $(OBJ_DIR)/%.o, $(patsubst $(SRC_DIR)/%, %, $(shell find $(SRC_DIR) -type f -name '*.c' 2>/dev/null)))

RM          := rm -f
MAKEFLAGS 	+= --no-print-directory
DIR_DUP     = mkdir -p $(@D)



.PHONY: all
all: build

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(info [LINKING] $@ : $(CC) $(OBJECTS) $(LDFLAGS) -o $@)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)
	$(info [COMPILED] $@ : $(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS))

.PHONY: build
build: $(TARGET)  ## Compile project

.PHONY: re
re:  ## Recompile project
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean
clean:  ## Remove all object files
	$(info $(RM) $(OBJECTS))
	$(RM) $(OBJECTS)

.PHONY: fclean
fclean: clean  ## Remove all executable files + object files
	$(info $(RM) $(TARGET))
	$(RM) $(TARGET)

.DEFAULT_GOAL := help
.PHONY: help
help:  ## Show this output, i.e. help to use the commands
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' Makefile | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

info-%:
	@make --dry-run --always-make $* | grep -v "info"

print-%:
	@$(info '$*'='$($*)')


.SILENT:
