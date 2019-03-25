
######################## PROJECT ########################

NAME = libgeo.a

######################### COLOR #########################

ERASE_LINE = '\033[2K\r'

BLANK = '\033[0m'
RED = '\033[31m'
YELLOW = '\033[33m'

######################## SOURCES ########################

SRC_PATH = ./sources/

SRC_MAT =	matrix_compute.c\
			matrix_operations.c
SRC_QUAT =	quaternion_compute.c\
			quaternion_operations.c
SRC_VEC =	vector_operations.c\
			vector_transform.c
SRC_OTHER =	angle_conversion.c\
			complex_number.c\
			copy.c

SRC_FILES = $(SRC_MAT) $(SRC_QUAT) $(SRC_VEC) $(SRC_OTHER)

######################## OBJECTS ########################

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_DIR = objects
OBJ_PATH = ./$(OBJ_DIR)/

OBJS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

######################## COMMANDS #######################

ifeq ($(OS),$(filter $(OS),Darwin Linux))
CC = /usr/bin/gcc
MAKE = /usr/bin/make
RMR = /bin/rm -rf
MKDIR = /bin/mkdir
PRINTF = /usr/bin/printf
AR = /usr/bin/ar rcs
RAN = /usr/bin/ranlib
else
CC = gcc
MAKE = make
RMR = rm -rf
MKDIR = mkdir
PRINTF = printf
AR = ar rcs
RAN = ranlib
endif

######################## INCLUDES #######################

INCLUDES = -I includes/
INC_FILES = includes/geometry.h

######################### FLAGS #########################

CFLAGS = -Werror -Wall -Wextra $(INCLUDES) -c

##################### MISCELLANEOUS #####################

COUNT = 0

######################### RULES #########################

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR):
	@ $(MKDIR) -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILES)
	@ $(eval COUNT = $(shell echo $$(($(COUNT)+1))))
	@ $(PRINTF) " %blibgeo%b	~ Compiling %bobject files%b: %b%b%b..." \
	$(RED) $(BLANK) $(YELLOW) $(BLANK) $(RED) $@ $(BLANK)
	@ $(CC) $(CFLAGS) $< -o $@
	@ $(PRINTF) $(ERASE_LINE)

$(NAME): $(OBJ_DIR) $(OBJS)
	@ $(PRINTF) " %blibgeo%b	~ Compiled %bobject files%b ! %b(%b files)%b\n" \
		$(RED) $(BLANK) $(YELLOW) $(BLANK) $(RED) $(COUNT) $(BLANK)
	@ $(AR) $(NAME) $(OBJS)
	@ $(RAN) $(NAME)
	@ $(PRINTF) " %blibgeo%b	~ Successfully compiled !\n" $(RED) $(BLANK)

clean:
	@ printf " %blibgeo%b	~ Cleaning %bobject files%b...\n" \
		$(RED) $(BLANK) $(YELLOW) $(BLANK)
	@ $(RMR) $(OBJ_PATH)

fclean: clean
	@ printf " %blibgeo%b	~ Cleaning %b%b%b...\n" \
		$(RED) $(BLANK) $(RED) $(NAME) $(BLANK)
	@ $(RMR) $(NAME)

re: fclean
	@ $(MAKE) all
