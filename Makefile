CC = cc
# Add flags to notify us of all errors and crash if any error occurs.
CFLAGS = -Wall -Wextra -pedantic -Werror -g
LDFLAGS = -Wall -Wextra -pedantic -Werror -g

# The directory to which the test program is written
BUILDDIR = build

OUT = test

# Notice how we don't depend on test.c, but test.o
# This tells Make that we want the test.o to be built
$(BUILDDIR)/$(OUT): $(BUILDDIR)/test.o
	mkdir -p $(BUILDDIR)
# Link the object file. $^ gives us all dependancies
	$(CC) $(LDFLAGS) $^ -o $@

# Compile any C file given to an object file
# simple makefile behavior. $< gives us the first item in the 'dependancy list' (the things after the colon)
# $@ gives us what the 'rule' (combo of output and dependancy) is going to output
$(BUILDDIR)/%.o: %.c
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@
