
######################## PROJECT ########################

NAME = rt

########################## OS ###########################

OS := $(shell uname)

######################### COLOR #########################

ERASE_LINE = '\033[2K\r'
ERASE_LAST_LINE = '\033[0K\r'

BLANK = '\033[0m'
MAGENTA = '\033[35m'
YELLOW = '\033[33m'

###################### BREW PATH ########################

BREW_PATH = $(HOME)/.brew/
BREW_LIB_PATH = $(BREW_PATH)lib/

######################### STR ###########################

CAPTION = $(MAGENTA)$(NAME)$(BLANK)
STR_SDL2 = $(MAGENTA)"SDL2"$(BLANK)
STR_SDL2_I = $(MAGENTA)"SDL2_image"$(BLANK)
STR_SDL2_T = $(MAGENTA)"SDL2_ttf"$(BLANK)
STR_OCL = $(MAGENTA)"OpenCL"$(BLANK)

####################### LIBRARIES #######################

LIB = ./libraries/

LIBFT_PATH = $(LIB)libft/
LIBFT = $(LIBFT_PATH)libft.a

LIBOCL_PATH = $(LIB)libocl/
LIBOCL = $(LIBOCL_PATH)libocl.a

LIBGEO_PATH = $(LIB)libgeo/
LIBGEO = $(LIBGEO_PATH)libgeo.a

LIBPARSER_PATH = $(LIB)libparser/
LIBPARSER = $(LIBPARSER_PATH)libparser.a

######################## SOURCES ########################

SRC_PATH = ./sources/

SRC_CORE = main.c\
		   core.c\
		   compute_rt.c\
		   compute_rt2.c\
		   compute_rt3.c\
		   compute_rt_border.c\
		   compute_rt_antialiasing.c\
		   compute_rt_postprocess.c\
		   compute_rt_postprocess_filter.c\
		   build_obj.c\
		   init_arg.c\
		   init_arg_border.c\
		   init_arg_antialiasing.c\
		   init_arg_postprocess.c\
		   set_arg_postprocess.c\
		   release_memobjs.c\
		   screenshots.c\
		   texture_load.c\
		   texture_load2.c\
		   editor.c\
		   editor2.c\
		   bresenham.c\
		   load_msg.c\
		   add_obj.c

SRC_SDL =	sdl.c\
			sdl_img.c\
			sdl_ttf.c\
			sdl_ttf_render.c\
			sdl_merge_layers.c

SRC_INIT =	init_param.c\
			init_ocl.c\
			init_env_info.c\
			rt_info.c\
			fill_tab_info.c\
			fill_param_rt.c\
			init_menu.c\
			fill_texture_mode.c\
			get_elem_nb.c\
			put_nb_error.c\
			ft_free_temp.c

SRC_EVENT = event_keydown.c\
			event_keyup.c\
			event_keyup2.c\
			event_mousemotion.c\
			event_buttonup.c\
			event_buttonup2.c\
			event_get_changes.c\
			event_fps_limiter.c\
			event_win.c\
			event_scroll.c\
			event_menu_postp.c\
			event_screenshot.c\
			event_fullscreen.c\
			event_win_update_specs.c

SRC_DRAW =	draw_angle_in.c\
			draw_angle_out.c\
			draw_square.c\
			draw_gradient.c\
			draw_angle_option.c

SRC_MENU =	menu_base.c\
			menu_str.c\
			menu_str_editor.c\
			menu_str2.c\
			menu_draw_event.c\
			menu_option.c\
			menu_display_load.c\
			edit_obj.c\
			edit_obj_light.c\
			menu_create_surf.c\
			create_lay_logo.c

SRC_SLIDE =	slider.c\
			slider_trans.c\
			slider_reflect.c\
			slider_refract.c\
			slider_spec.c\
			slider_ambient.c\
			slider_fov.c\
			slider_color.c\
			slider_texture.c\
			slider_texture2.c\
			slider_texture_scl.c

SRC_FILES = $(SRC_CORE) $(SRC_EVENT) $(SRC_INIT)\
 			$(SRC_DRAW) $(SRC_SDL) $(SRC_MENU) \
 			$(SRC_SLIDE)

######################## OBJECTS ########################

OBJ_DIR = objects
OBJ_PATH = ./$(OBJ_DIR)/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

######################## COMMANDS #######################

ifeq ($(OS),$(filter $(OS),Darwin Linux))
CC = /usr/bin/gcc
MAKE = /usr/bin/make
RM = /bin/rm -f
RMR = /bin/rm -rf
MKDIR = /bin/mkdir
PRINTF = /usr/bin/printf
else
CC = gcc
MAKE = make
RM = rm -f
RMR = rm -rf
MKDIR = mkdir
PRINTF = printf
endif

######################## INCLUDES #######################

INC = includes

INC_DEP = "$(BREW_PATH)include/"
INC_LIBFT = $(LIBFT_PATH)$(INC)
INC_LIBOCL = $(LIBOCL_PATH)$(INC)
INC_LIBGEO = $(LIBGEO_PATH)$(INC)
INC_LIBPARSER = $(LIBPARSER_PATH)$(INC)
INC_RT = $(INC)

INC_DIRS =	$(addprefix -I, $(INC_LIBFT) $(INC_LIBOCL) $(INC_LIBPARSER)\
			$(INC_LIBGEO) $(INC_RT)\
			$(INC_DEP))

ifeq ($(OS),MINGW32_NT-6.2)
INC_DIRS += -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v9.2\include"
endif

INC_FILES_DIR = ./$(INC)/
INC_FILES = $(INC_FILES_DIR)rt.h $(INC_FILES_DIR)solarized.h\
			$(INC_FILES_DIR)kernel_props.h

######################### FLAGS #########################

FLAGS_DEFAULT = -Werror -Wall -Wextra
FLAGS_OBJ = $(FLAGS_DEFAULT) $(INC_DIRS) -c

ifeq ($(OS),Darwin)
FLAGS_SDL = -framework OpenGL -framework GLUT\
			-L $(BREW_LIB_PATH) -lSDL2 -lSDL2_image\
			-lSDL2_ttf
FLAGS_OCL = -framework OpenCL
else ifeq ($(OS),Linux)
FLAGS_SDL_C := $(shell sdl2-config --cflags)
FLAGS_DEFAULT += $(FLAGS_SDL_C)
FLAGS_SDL := $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image
FLAGS_OCL = -lOpenCL
else
FLAGS_SDL_C := $(shell sdl2-config --cflags)
FLAGS_DEFAULT += $(FLAGS_SDL_C)
FLAGS_SDL := $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image
FLAGS_OCL = -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v9.2\lib\Win32" -lOpenCL
endif

FLAGS_LIBFT = -L$(LIBFT_PATH) -lft
FLAGS_LIBOCL = -L$(LIBOCL_PATH) -locl
FLAGS_LIBGEO = -L$(LIBGEO_PATH) -lgeo
FLAGS_LIBPARSER = -L$(LIBPARSER_PATH) -lparser

FLAGS_DEP = $(FLAGS_LIBOCL) $(FLAGS_LIBPARSER) $(FLAGS_LIBGEO)\
			$(FLAGS_LIBFT) $(FLAGS_SDL) $(FLAGS_OCL)

ifeq ($(OS),Linux)
FLAGS_DEP += -lm
endif

###################### DEPENDENCIES #####################

ifeq ($(OS),Darwin)
DEP_SDL2 = $(BREW_LIB_PATH)libSDL2.a
DEP_SDL2_IMG = $(BREW_LIB_PATH)libSDL2_image.a
DEP_SDL2_TTF = $(BREW_LIB_PATH)libSDL2_ttf.a
else ifeq ($(OS),Linux)
DEP_SDL2 = /usr/lib/x86_64-linux-gnu/libSDL2.a
DEP_SDL2_IMG = /usr/lib/x86_64-linux-gnu/libSDL2_image.a
DEP_SDL2_TTF = /usr/lib/x86_64-linux-gnu/libSDL2_ttf.a
DEP_OCL = /usr/lib/x86_64-linux-gnu/libOpenCL.so
else
DEP_SDL2 = $(MSYS_LIB)/libSDL2.a
DEP_SDL2_IMG = $(MSYS_LIB)/libSDL2_image.a
DEP_SDL2_TTF = $(MSYS_LIB)/libSDL2_ttf.a
endif

DEP =	$(DEP_SDL2) $(DEP_SDL2_IMG) $(DEP_SDL2_TTF)\
		$(DEP_OCL) $(LIBFT) $(LIBOCL) \
		$(LIBGEO) $(LIBPARSER) $(OBJ_DIR) $(OBJS)

##################### WINDOWS DEP #######################

SDL2_FILE = SDL2-devel-2.0.8-mingw.tar.gz
SDL2_IMG_FILE = SDL2_image-devel-2.0.3-mingw.tar.gz
SDL2_TTF_FILE = SDL2_ttf-devel-2.0.14-mingw.tar.gz

SDL2_DIR = SDL2-2.0.8
SDL2_IMG_DIR = SDL2_image-2.0.3
SDL2_TTF_DIR = SDL2_ttf-2.0.14

SDL2_LINK = https://www.libsdl.org/release/SDL2-devel-2.0.8-mingw.tar.gz
SDL2_IMG_LINK = https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.3-mingw.tar.gz
SDL2_TTF_LINK = https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-mingw.tar.gz

##################### MISCELLANEOUS #####################

COUNT = 0

######################### RULES #########################

.PHONY: all re clean fclean run

all: $(NAME)

echo:
	echo $(OS)

ifeq ($(OS),Darwin)
$(DEP_SDL2):
	@ $(PRINTF) "\n %b	~ Dependencies %bdownload%b and %binstall%b...\n"\
		$(STR_SDL2) $(YELLOW) $(BLANK) $(YELLOW) $(BLANK)
	@ brew install SDL2 > .tmp
	@ $(PRINTF) " %b	~ Dependencies %binstalled%b !\n"\
		$(STR_SDL2) $(YELLOW) $(BLANK)

$(DEP_SDL2_IMG):
	@ $(PRINTF) " %b ~ Dependencies %bdownload%b and %binstall%b...\n"\
		$(STR_SDL2_I) $(YELLOW) $(BLANK) $(YELLOW) $(BLANK)
	@ brew install SDL2_image > .tmp
	@ $(PRINTF) " %b ~ Dependencies %binstalled%b !\n"\
		$(STR_SDL2_I) $(YELLOW) $(BLANK)

$(DEP_SDL2_TTF):
	@ $(PRINTF) " %b ~ Dependencies %bdownload%b and %binstall%b...\n"\
		$(STR_SDL2_T) $(YELLOW) $(BLANK) $(YELLOW) $(BLANK)
	@ brew install SDL2_ttf > .tmp
	@ $(PRINTF) " %b ~ Dependencies %binstalled%b !\n\n"\
		$(STR_SDL2_T) $(YELLOW) $(BLANK)
else ifeq ($(OS),Linux)
$(DEP_SDL2):
	@ $(PRINTF) "\n %b	~ Dependencies %bdownload%b and %binstall%b...\n"\
		$(STR_SDL2) $(YELLOW) $(BLANK) $(YELLOW) $(BLANK)
	@ sudo apt-get install -y libsdl2-dev > .tmp
	@ $(PRINTF) " %b	~ Dependencies %binstalled%b !\n"\
		$(STR_SDL2) $(YELLOW) $(BLANK)

$(DEP_SDL2_IMG):
	@ $(PRINTF) " %b ~ Dependencies %bdownload%b and %binstall%b...\n"\
		$(STR_SDL2_I) $(YELLOW) $(BLANK) $(YELLOW) $(BLANK)
	@ sudo apt-get install -y libsdl2-image-dev > .tmp
	@ $(PRINTF) " %b ~ Dependencies %binstalled%b !\n"\
		$(STR_SDL2_I) $(YELLOW) $(BLANK)

$(DEP_SDL2_TTF):
	@ $(PRINTF) " %b ~ Dependencies %bdownload%b and %binstall%b...\n"\
		$(STR_SDL2_T) $(YELLOW) $(BLANK) $(YELLOW) $(BLANK)
	@ sudo apt-get install -y libsdl2-ttf-dev > .tmp
	@ $(PRINTF) " %b ~ Dependencies %binstalled%b !\n\n"\
		$(STR_SDL2_T) $(YELLOW) $(BLANK)

$(DEP_OCL):
	@ $(PRINTF) " %b ~ Dependencies %bdownload%b and %binstall%b...\n"\
		$(STR_OCL) $(YELLOW) $(BLANK) $(YELLOW) $(BLANK)
	@ sudo apt-get install -y ocl-icd-opencl-dev > .tmp
	@ $(PRINTF) " %b ~ Dependencies %binstalled%b !\n\n"\
		$(STR_OCL) $(YELLOW) $(BLANK)
else
$(DEP_SDL2):
	@ $(PRINTF) "\n %b	~ Dependencies %bdownload%b and %binstall%b...\n"\
		$(STR_SDL2) $(YELLOW) $(BLANK) $(YELLOW) $(BLANK)
	@ curl -sLO $(SDL2_LINK) > .tmp
	@ tar -xvzf $(SDL2_FILE) > .tmp
	@ $(MAKE) -sC $(SDL2_DIR) native > .tmp
	@ $(RMR) $(SDL2_DIR) $(SDL2_FILE)
	@ $(PRINTF) " %b	~ Dependencies %binstalled%b !\n"\
		$(STR_SDL2) $(YELLOW) $(BLANK)

$(DEP_SDL2_IMG):
	@ $(PRINTF) " %b ~ Dependencies %bdownload%b and %binstall%b...\n"\
		$(STR_SDL2_I) $(YELLOW) $(BLANK) $(YELLOW) $(BLANK)
	@ curl -sLO $(SDL2_IMG_LINK) > .tmp
	@ tar -xvzf $(SDL2_IMG_FILE) > .tmp
	@ $(MAKE) -sC $(SDL2_IMG_DIR) native > .tmp
	@ $(RMR) $(SDL2_IMG_DIR) $(SDL2_IMG_FILE)
	@ $(PRINTF) " %b ~ Dependencies %binstalled%b !\n"\
		$(STR_SDL2_I) $(YELLOW) $(BLANK)

$(DEP_SDL2_TTF):
	@ $(PRINTF) " %b ~ Dependencies %bdownload%b and %binstall%b...\n"\
		$(STR_SDL2_T) $(YELLOW) $(BLANK) $(YELLOW) $(BLANK)
	@ curl -sLO $(SDL2_TTF_LINK) > .tmp
	@ tar -xvzf $(SDL2_TTF_FILE) > .tmp
	@ $(MAKE) -sC $(SDL2_TTF_DIR) native > .tmp
	@ $(RMR) $(SDL2_TTF_DIR) $(SDL2_TTF_FILE)
	@ $(PRINTF) " %b ~ Dependencies %binstalled%b !\n\n"\
		$(STR_SDL2_T) $(YELLOW) $(BLANK)
endif

$(OBJ_DIR):
	@ $(MKDIR) -p $(OBJ_DIR)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILES)
	@ $(eval COUNT = $(shell echo $$(($(COUNT)+1))))
	@ $(PRINTF) " %b	~ Compiling %bobject files%b: %b%b%b..."\
		$(CAPTION) $(YELLOW) $(BLANK) $(MAGENTA) $@ $(BLANK)
	@ $(CC) $(FLAGS_OBJ) $< -o $@
	@ $(PRINTF) $(ERASE_LINE)


$(NAME): $(DEP)
	@ $(PRINTF) "\n %b	~ Compiled %bobject files%b ! %b(%b files)%b\n"\
		$(CAPTION) $(YELLOW) $(BLANK) $(MAGENTA) $(COUNT) $(BLANK)
	@ $(CC) $(FLAGS_DEFAULT) $(OBJS) $(FLAGS_DEP) -o $@
	@ $(PRINTF) " %b	~ Successfully compiled !\n" $(CAPTION)

$(LIBFT):
	@ $(MAKE) -sC $(LIBFT_PATH)

$(LIBOCL):
	@ $(MAKE) -sC $(LIBOCL_PATH)

$(LIBGEO):
	@ $(MAKE) -sC $(LIBGEO_PATH)

$(LIBPARSER):
	@ $(MAKE) -sC $(LIBPARSER_PATH)

clean:
	@ $(MAKE) -sC $(LIBFT_PATH) clean
	@ $(MAKE) -sC $(LIBOCL_PATH) clean
	@ $(MAKE) -sC $(LIBGEO_PATH) clean
	@ $(MAKE) -sC $(LIBPARSER_PATH) clean
	@ $(PRINTF) "\n %b	~ Cleaning %bobject files%b...\n"\
		$(CAPTION) $(YELLOW) $(BLANK)
	@ $(RMR) $(OBJ_PATH)
	@ $(RM) .tmp

clean_fclean:
	@ $(MAKE) -sC $(LIBFT_PATH) fclean
	@ $(MAKE) -sC $(LIBOCL_PATH) fclean
	@ $(MAKE) -sC $(LIBGEO_PATH) fclean
	@ $(MAKE) -sC $(LIBPARSER_PATH) fclean
	@ $(PRINTF) "\n %b	~ Cleaning %bobject files%b...\n"\
		$(CAPTION) $(YELLOW) $(BLANK)
	@ $(RMR) $(OBJ_PATH)
	@ $(RM) .tmp

fclean: clean_fclean
	@ $(PRINTF) " %b	~ Cleaning %b...\n"\
	 	$(CAPTION) $(CAPTION)
	@ $(RM) $(NAME)

run: all
	@ ./rt maps/line.json

re: fclean
	@ $(PRINTF) "\n"
	@ $(MAKE) -s all
