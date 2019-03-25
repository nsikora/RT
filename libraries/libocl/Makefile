
######################## PROJECT ########################

NAME = libocl.a

######################### COLOR #########################

ERASE_LINE = '\033[2K\r'

BLANK = '\033[0m'
GREEN = '\033[32m'
YELLOW = '\033[33m'

####################### LIBRARIES #######################

LIBFT = ../libft/

SRC_PATH = ./sources/
SRC_FILES =	ft_ocl_init_release.c\
			ft_ocl_platform.c\
			ft_ocl_device.c\
			ft_ocl_queue.c\
			ft_ocl_program_kernel.c\
			ft_ocl_init_error.c\
			ft_ocl_kernel_error.c\
			ft_ocl_set_kernel_arg.c\
			ft_ocl_device_info.c

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_DIR = objects
OBJ_PATH = ./$(OBJ_DIR)/

OBJS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

######################## INCLUDES #######################

INC_DIRS = -I includes/ -I $(LIBFT)includes/

ifeq ($(OS),MINGW32_NT-6.2)
INC_DIRS += -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v9.2\include"
endif

INC_FILES = includes/ocl_framework.h

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
	@ $(PRINTF) " %blibocl%b	~ Compiling %bobject files%b: %b%b%b..." \
	$(GREEN) $(BLANK) $(YELLOW) $(BLANK) $(GREEN) $@ $(BLANK)
	@ $(CC) $(FLAGS_OBJ) $< -o $@
	@ $(PRINTF) $(ERASE_LINE)

$(NAME): $(OBJ_DIR) $(OBJS)
	@ $(PRINTF) " %blibocl%b	~ Compiled %bobject files%b ! %b(%b files)%b\n" \
		$(GREEN) $(BLANK) $(YELLOW) $(BLANK) $(GREEN) $(COUNT) $(BLANK)
	@ $(AR) $(NAME) $(OBJS)
	@ $(RAN) $(NAME)
	@ $(PRINTF) " %blibocl%b	~ Successfully compiled !\n" $(GREEN) $(BLANK)

clean:
	@ printf " %blibocl%b	~ Cleaning %bobject files%b...\n" \
		$(GREEN) $(BLANK) $(YELLOW) $(BLANK)
	@ $(RMR) $(OBJ_PATH)

fclean: clean
	@ printf " %blibocl%b	~ Cleaning %b%b%b...\n" \
		$(GREEN) $(BLANK) $(GREEN) $(NAME) $(BLANK)
	@ $(RMR) $(NAME)

re: fclean all
