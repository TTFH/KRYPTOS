TARGET = kryptos

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -O3

SOURCES = main.cpp
SOURCES += src/utils.cpp src/quagmire.cpp src/hill_cipher.cpp src/transposition.cpp

OBJDIR = obj
OBJS = $(SOURCES:.cpp=.o)
OBJS := $(OBJS:.c=.o)
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(OBJS)))

.DEFAULT_GOAL := rebuild
.PHONY: all clean rebuild

all: $(TARGET)
	@echo Build complete.

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: src/%.cpp src/%.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

rebuild: clean all

clean:
	rm -f $(TARGET) $(OBJDIR)/*.o
