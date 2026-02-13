BUILD_DIR_RELEASE=.build_release
BUILD_DIR_DEBUG=.build_debug
COMPILE_COMMANDS_DIR=.compile_commands

all:
	@echo "Usage:"
	@echo "    make <release | .debug>"
	@echo "    make <check>"
	@echo "    make <clean>"

release:
	$(shell if [ ! -d $(BUILD_DIR_RELEASE) ]; then mkdir $(BUILD_DIR_RELEASE); fi )
	cd $(BUILD_DIR_RELEASE) ; cmake -DCMAKE_BUILD_TYPE=Release .. ; make -j ; cd ..
	cp $(BUILD_DIR_RELEASE)/texpacker .

.debug:
	$(shell if [ ! -d $(BUILD_DIR_DEBUG) ]; then mkdir $(BUILD_DIR_DEBUG); fi )
	cd $(BUILD_DIR_DEBUG) ; cmake -DCMAKE_BUILD_TYPE=Debug .. ; make -j ; cd ..
	cp $(BUILD_DIR_DEBUG)/texpacker .

check:
	cppcheck -j 1 --enable=all -f -I src src/ 2> cppcheck-output

build_compile_commands:
	$(shell if [ ! -d $(COMPILE_COMMANDS_DIR) ]; then mkdir $(COMPILE_COMMANDS_DIR); fi )
	cd $(COMPILE_COMMANDS_DIR) && cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
	rm -fr compile_commands.json && ln -s $(COMPILE_COMMANDS_DIR)/compile_commands.json compile_commands.json

clean:
	rm -fr $(BUILD_DIR_RELEASE) $(BUILD_DIR_DEBUG) texpacker
	rm -fr $(COMPILE_COMMANDS_DIR) .cache/

