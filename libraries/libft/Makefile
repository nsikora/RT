# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 14:23:08 by dtheo             #+#    #+#              #
#    Updated: 2018/08/20 00:29:42 by dtheo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################## PROJECT ########################

NAME = libft.a

######################### COLOR #########################

ERASE_LINE = '\033[2K\r'

BLANK = '\033[0m'
CYAN = '\033[36m'
YELLOW = '\033[33m'

######################## SOURCES ########################

SRC_PATH = ./sources/

SRC_FILES = ft_abs.c ft_atoi.c ft_fatoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
	ft_strsplit.c ft_isascii.c ft_isdigit.c ft_islower.c ft_isprint.c \
	ft_isspace.c ft_isupper.c ft_itoa.c ft_memalloc.c ft_memccpy.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c \
	ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
	ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strclr.c ft_strcmp.c \
	ft_strcpy.c ft_strdel.c ft_strdup.c ft_striter.c ft_striteri.c \
	ft_strlen.c ft_strncpy.c ft_strnew.c ft_strtrim.c ft_tolower.c \
	ft_toupper.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_strstr.c ft_strnstr.c ft_strequ.c \
	ft_strnequ.c ft_strmap.c ft_strmapi.c ft_strsub.c ft_strjoin.c \
	ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstpush.c \
	ft_lstiter.c ft_lstmap.c ft_factorial.c ft_pow.c ft_stralloc.c \
	ft_lstlen.c get_next_line.c ft_vector2_new.c ft_vector2_mag.c \
	ft_vector2_mult.c ft_vector2_scl.c ft_vector2_div.c ft_vector2_add.c \
	ft_vector2_sub.c ft_vector2_norm.c ft_vector3_new.c ft_vector3_mag.c \
	ft_vector3_dot.c ft_vector3_scl.c ft_vector3_div.c ft_vector3_cross.c \
	ft_vector3_sub.c ft_vector3_add.c ft_vector3_norm.c \
	ft_vector3_rodrigues.c ft_memrchr.c ft_error.c ft_ftoa.c

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
INC_FILES = includes/libft.h

######################### FLAGS #########################

CFLAGS = -Werror -Wall -Wextra $(INCLUDES) -c

##################### MISCELLANEOUS #####################

COUNT = 0

######################### RULES #########################

.PHONY : all clean fclean re

all: $(NAME)

$(OBJ_DIR):
	@ $(MKDIR) -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILES)
	@ $(eval COUNT = $(shell echo $$(($(COUNT)+1))))
	@ printf " %blibft%b	~ Compiling %bobject files%b: %b%b%b..." \
		$(CYAN) $(BLANK) $(YELLOW) $(BLANK) $(CYAN) $@ $(BLANK)
	@ $(CC) $(CFLAGS) $< -o $@
	@ $(PRINTF) $(ERASE_LINE)

$(NAME): $(OBJ_DIR) $(OBJS)
	@ printf " %blibft%b	~ Compiled %bobject files%b ! %b(%b files)%b\n" \
		$(CYAN) $(BLANK) $(YELLOW) $(BLANK) $(CYAN) $(COUNT) $(BLANK)
	@ ar -rcs $(NAME) $(OBJS)
	@ ranlib $(NAME)
	@ printf " %blibft%b	~ Successfully compiled !\n" $(CYAN) $(BLANK)

clean:
	@ printf " %blibft%b	~ Cleaning %bobject files%b...\n" \
		$(CYAN) $(BLANK) $(YELLOW) $(BLANK)
	@ rm -f $(OBJS)

fclean: clean
	@ printf " %blibft%b	~ Cleaning %b%b%b...\n" \
		$(CYAN) $(BLANK) $(CYAN) $(NAME) $(BLANK)
	@ rm -f $(NAME)

re : fclean all
