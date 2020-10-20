.PHONY: build

build:
	g++ ./parse_cmd.cpp -o parseCmd
default_goal: build def 
.PHONY: def
def:
	./parseCmd -l -h -v -V12

.PHONY: run

run:
	./parseCmd -l


.DEFAULT_GOAL:=default_goal
