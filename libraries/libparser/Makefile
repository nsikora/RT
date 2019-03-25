
######################## PROJECT ########################

NAME = libparser.a

######################### COLOR #########################

ERASE_LINE = '\033[2K\r'

BLANK = '\033[0m'
GREEN = '\033[32m'
YELLOW = '\033[33m'

####################### LIBRARIES #######################

LIBFT = ../libft/

SRC_PATH = ./sources/
SRC_FILES =	parse.c\
			check.c\
			error_parsing.c\
			error_parsing_2.c\
			parse_info.c\
			parse_info_2.c\
			parse_info_3.c

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_DIR = objects
OBJ_PATH = ./$(OBJ_DIR)/

OBJS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

######################## INCLUDES #######################

INC_DIRS = -I includes/ -I $(LIBFT)includes/

INC_FILES = includes/parse.h

######################### FLAGS #########################

FLAGS_DEFAULT = -Werror -Wall -Wextra
FLAGS_OBJ = $(FLAGS_DEFAULT) $(INC_DIRS) -c

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

##################### MISCELLANEOUS #####################

COUNT = 0

######################### RULES #########################

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR):
	@ $(MKDIR) -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILES)
	@ $(eval COUNT = $(shell echo $$(($(COUNT)+1))))
	@ $(PRINTF) " %blibparser%b	~ Compiling %bobject files%b: %b%b%b..." \
	$(GREEN) $(BLANK) $(YELLOW) $(BLANK) $(GREEN) $@ $(BLANK)
	@ $(CC) $(FLAGS_OBJ) $< -o $@
	@ $(PRINTF) $(ERASE_LINE)

$(NAME): $(OBJ_DIR) $(OBJS)
	@ $(PRINTF) " %blibparser%b	~ Compiled %bobject files%b ! %b(%b files)%b\n" \
		$(GREEN) $(BLANK) $(YELLOW) $(BLANK) $(GREEN) $(COUNT) $(BLANK)
	@ $(AR) $(NAME) $(OBJS)
	@ $(RAN) $(NAME)
	@ $(PRINTF) " %blibparser%b	~ Successfully compiled !\n" $(GREEN) $(BLANK)

clean:
	@ printf " %blibparser%b	~ Cleaning %bobject files%b...\n" \
		$(GREEN) $(BLANK) $(YELLOW) $(BLANK)
	@ $(RMR) $(OBJ_PATH)

fclean: clean
	@ printf " %blibparser%b	~ Cleaning %b%b%b...\n" \
		$(GREEN) $(BLANK) $(GREEN) $(NAME) $(BLANK)
	@ $(RMR) $(NAME)

re: fclean all
