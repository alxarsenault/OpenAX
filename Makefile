UNAME := $(shell uname)
LIB_DIR = lib

LIB_NAME = OpenAX

# List of all modules to compile.
MODULES_DIR := $(shell ls modules)

# List of module to combine in OpenAX.a and OpenAX.so
MODULES_LIST := Core Event OS Render Utils Widget Xml

# Create list of path modules/MODULE_NAME/build/*.o from MODULES_LIST.
MODULES_OBJ := $(addsuffix /build/*.o, $(addprefix modules/, $(MODULES_LIST)));

all: create_lib_dir modules
	@ar rsc lib/lib$(LIB_NAME).a $(shell ls $(MODULES_OBJ))
	@clang++ -shared -undefined dynamic_lookup -o lib/lib$(LIB_NAME).so $(shell ls $(MODULES_OBJ))

# bing:
# 	@echo $(MODULES_OBJ)

create_lib_dir:
	@mkdir -p $(LIB_DIR)

.PHONY: modules $(MODULES_DIR)

modules: $(MODULES_DIR)

$(MODULES_DIR):
	@make -C modules/$@
	@cp modules/$@/lib/*.a $(LIB_DIR)/

install:
	@mkdir -p /usr/local/include/$(LIB_NAME)/
	@cp -f -v modules/**/include/* /usr/local/include/OpenAX/ 2> /dev/null
	@cp -f -v $(LIB_DIR)/*.a /usr/local/lib/ 2> /dev/null
	@cp -f -v $(LIB_DIR)/*.so /usr/local/lib/ 2> /dev/null

clean:
	@rm -f $(LIB_DIR)/*
	@for d in $(MODULES_DIR); do (cd modules/$$d; echo $$d; $(MAKE) clean;) done
