CXX             ?= g++
CXXFLAGS        ?= -Werror -Wall -Wmissing-declarations -Wpointer-arith \
					 -Wwrite-strings -Wcast-qual -Wcast-align -Wformat-security \
					 -Wformat-nonliteral -Wmissing-format-attribute -Winline \
					 -pedantic-errors -fstack-protector-all -D_FORTIFY_SOURCE=2 \
					 -fPIC -std=c++11 -pthread

IMDB_DIR        ?= ../v2
KAGGLE_DIR  ?= ../v3

GENERICAPI_DIR   = $(IMDB_DIR)/pkg_deps/genericapi

INCLUDES         = -I$(GENERICAPI_DIR)/include -I$(IMDB_DIR)/include \
				   -I$(KAGGLE_DIR)/include -Iinclude

LIBS             = $(IMDB_DIR)/build/libs/libtangramgeneric.a \
				   $(KAGGLE_DIR)/build/libs/libtangramgeneric.a \
				   $(GENERICAPI_DIR)/build/libs/libtangramgenericapi.a

all: test_lib

test_lib: movies_msg_simple_function.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -shared -o libmoviesmsg.so movies_msg_simple_function.cpp gen/KaggleToIMDBTransform.cpp gen/my_transform.cpp $(LIBPATHS) $(LIBS)

clean:
	@rm -f libmoviesmsg.so