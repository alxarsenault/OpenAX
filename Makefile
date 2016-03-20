UNAME := $(shell uname)
LIB_DIR = lib
MODULES_DIR = $(shell ls modules)

LIB_NAME = axLib

all: create_lib_dir modules
	ar rsc lib/lib$(LIB_NAME).a $(shell ls modules/*/build/*.o)
	clang++ -shared -undefined dynamic_lookup -o lib/lib$(LIB_NAME).so $(shell ls modules/*/build/*.o)

create_lib_dir:
	@mkdir -p $(LIB_DIR)

.PHONY: modules $(MODULES_DIR)

modules: $(MODULES_DIR)

$(MODULES_DIR):
	make -C modules/$@
	cp modules/$@/lib/*.a $(LIB_DIR)/

install:
	mkdir -p /usr/local/include/$(LIB_NAME)/
	cp -v modules/*/include/*.{h,hpp} /usr/local/include/axLib/ 2> /dev/null
	cp -v $(LIB_DIR)/*.a /usr/local/lib/ 2> /dev/null
	cp -v $(LIB_DIR)/*.so /usr/local/lib/ 2> /dev/null

clean:
	rm -f $(LIB_DIR)/*
	for d in $(MODULES_DIR); do (cd modules/$$d; echo $$d; $(MAKE) clean;) done
