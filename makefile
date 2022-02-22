# ----------------------------
# Makefile Options
# ----------------------------

NAME = Snake
ICON = icon.png
DESCRIPTION = "Snake for the TI-84 CE"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
