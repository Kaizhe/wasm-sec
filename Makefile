.PHONY: all

all: compile run

install:
	@echo "+ $@"
	./scripts/install
compile:
	@echo "+ $@"
	./scripts/compile
run:
	@echo "+ $@"
	./scripts/run

