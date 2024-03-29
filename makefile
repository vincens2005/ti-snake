# ----------------------------
# Makefile Options
# ----------------------------

NAME = Snake
ICON = icon.png
DESCRIPTION = "Snake for the TI-84 CE"
COMPRESSED = NO
ARCHIVED = NO
HAS_PRINTF := NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# stolen from the font example

# fonts.c depends on testfont.inc, which is built from testfont.fnt
FONTDIR = $(SRCDIR)/fonts
FONT = $(FONTDIR)/testfont.fnt
FONT_INC = $(FONTDIR)/testfont.inc

DEPS = $(FONT_INC)

# ----------------------------

include $(shell cedev-config --makefile)

# ----------------------------

$(FONT_INC): $(FONT)
	$(Q)$(call MKDIR,$(@D))
	$(Q)convfont -o carray -f $< -a 1 -b 1 -w bold -c 2 -x 9 -l 0x0B -Z $@
