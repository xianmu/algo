
# (A) Production use (optimized mode)
OPT ?= -O2 -DNDEBUG
# (B) Debug mode, w/ full line-level debugging symbols
# OPT ?= -g2 -Wall -fPIC
# (C) Profiling mode: opt, but w/debugging symbols
# OPT ?= -O2 -g2 -DNDEBUG
#-----------------------------------------------

CXXFLAGS += -I. $(OPT) -lgtest -lpthread

skip_list_test:
	$(CXX) $(CXXFLAGS) -o skip_list_test skip_list_test.cpp

