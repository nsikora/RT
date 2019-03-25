/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 14:39:08 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 14:39:10 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

/*
** INCLUDE
*/

# if defined __APPLE__ || defined __linux__

#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
#  include <SDL2/SDL_ttf.h>
#  include <time.h>

#  ifndef CLOCK_MONOTONIC
#   ifdef __MACH__
#    include <mach/clock.h>
#    include <mach/mach.h>
#   endif
#  endif

# else

#  include <SDL.h>
#  include <SDL_image.h>
#  include <SDL_ttf.h>
#  include <Windows.h>
#  include <sys/stat.h>

# endif

# include <stdbool.h>
# include <errno.h>

# include "solarized.h"
# include "kernel_props.h"

# include "geometry.h"
# include "libft.h"
# include "parse.h"
# include "ocl_framework.h"

/*
** DEFINE PARAM
*/

# define DEFAULT_STEP	1.5
# define DEFAULT_FOV	31.26
# define DEFAULT_FPS	60

/*
** DEFINE COLOR
*/

# define WHITE				0xffffffff
# define MENU_DARK_BLUE		SOLARIZED_BF02_DARK_BLUE
# define MENU_LIGHT_BLUE	SOLARIZED_BF02_LIGHT_BLUE
# define HIGHLIGHT_BLUE		SOLARIZED_CONTENT_BLUE

/*
** DEFINE SDL
*/

# undef main

# define WIDTH_MIN	640
# define HEIGHT_MIN	360
# define WIDTH		1280
# define HEIGHT		720

# define DEPTH	32

# if SDL_BYTEORDER == SDL_BIG_ENDIAN
#  define RMASK 0xff000000
#  define GMASK 0x00ff0000
#  define BMASK 0x0000ff00
#  define AMASK 0x000000ff
# else
#  define RMASK 0x000000ff
#  define GMASK 0x0000ff00
#  define BMASK 0x00ff0000
#  define AMASK 0xff000000
# endif

# define RED	2
# define GREEN	1
# define BLUE	0
# define ALPHA	3

# define PT_MONO_PATH "./assets/fonts/pt_mono/PTMONO.ttf"

/*
** DEFINE RAY_TRACING
*/

# define ID_SPHERE			0
# define ID_CONE			1
# define ID_PLANE			2
# define ID_CYLINDER		3
# define ID_CUBE			4

# define BILLION			1000000000.0
# define RAY_SIZE			80

/*
** DEFINE POSTPROCESS
*/

# define P_BLUR 1
# define P_GREY 2
# define P_COLOR 3
# define P_CYAN 4
# define P_NEG 5

# define F_RED 0
# define F_GREEN 1
# define F_BLUE 2
# define F_HALF 3
# define F_FULL 4

# define CELL_SHADING 1
# define ANTI_ALIASING 2

# define STEREO1 1
# define STEREO2 2

/*
** DEFINE MENU
*/

# define STR_LOAD	"LOADING..."
# define LOAD_FILE	"./assets/loading_messages.txt"

# define LOGO_INFO	"./assets/logo/document-page-with-text-lines.png"
# define LOGO_POST	"./assets/logo/screwdriver-and-wrench-crossed.png"
# define LOGO_EDIT	"./assets/logo/edition-box.png"
# define LOGO_PARA	"./assets/logo/bolt-silhouette.png"
# define LOGO_SHOT	"./assets/logo/old-camera-.png"
# define LOGO_CANC	"./assets/logo/access-denied.png"
# define LOGO_APPL	"./assets/logo/checked-box.png"

# define STR_INFO	"INFO"
# define STR_POST	"POST PROCESS"
# define STR_EDIT	"EDITOR"
# define STR_PARAM	"PARAMETERS"

/*
** TYPEDEF
*/

typedef char			t_bmp[3];
typedef t_dec			t_vec_ocl[4];

/*
** STRUCTURE
*/

typedef	union			u_color
{
	int					rgb;
	unsigned int		urgb;
	unsigned char		byte[4];
}						t_color;

typedef struct			s_tex
{
	t_color				*pixels;
	int					width;
	int					height;
	char				*name;
	SDL_Surface			*surface;
}						t_tex;

typedef struct			s_slider
{
	size_t				coor[2];
	size_t				length;
	size_t				thick;

	t_color				fill;
	t_color				empty;

	float				min;
	float				max;

	float				val;
}						t_slider;

typedef struct			s_menu
{
	int					selected_obj;
	int					move_or_rot;
	t_color				last_color;
	int					last_tex;

	size_t				info_coor[4];
	size_t				preview_coor[4];
	size_t				menu_coor[4];
	size_t				sub_menu_coor[4];

	SDL_Rect			button_coor[7];
	SDL_Rect			logo_coor[7];
	SDL_Rect			str_rect[7];
	SDL_Rect			option_rect[7];
	SDL_Rect			fps_rect;

	int					editor_switch;
	int					tex_switch;
	int					tex_mode_switch;
	int					type_switch;

	char				*width_val;
	SDL_Rect			width_rect;
	char				*height_val;
	SDL_Rect			height_rect;
	char				*objects_val;
	SDL_Rect			objects_rect;
	char				*lights_val;
	SDL_Rect			lights_rect;
	char				*limit_val;
	SDL_Rect			limit_rect;

	char				*fov_val;
	SDL_Rect			fov_rect;
	char				*trans_val;
	SDL_Rect			trans_rect;
	char				*refract_val;
	SDL_Rect			refract_rect;
	char				*reflect_val;
	SDL_Rect			reflect_rect;
	char				*spec_val;
	SDL_Rect			spec_rect;
	char				*ambient_val;
	SDL_Rect			ambient_rect;
	char				*tex_val;
	SDL_Rect			tex_rect;
	char				*tex_scl_val;
	SDL_Rect			tex_scl_rect;

	t_slider			color[3];
	size_t				color_coor[4];
	t_slider			trans;
	t_slider			reflection;
	t_slider			refraction;
	t_slider			fov;
	t_slider			spec;
	t_slider			ambient;
	t_slider			tex;
	t_slider			tex_scl;

	SDL_Rect			rt_rect;
	SDL_Rect			preview_rect;

	int					titles_pos[4][2];
	int					loading_pos[2];

	SDL_Rect			menu_info;
	SDL_Rect			menu_pp;
	SDL_Rect			menu_editor;
	SDL_Rect			menu_param;

	SDL_Rect			letter_rect[7];

	SDL_Surface			*lay_base;
	SDL_Surface			*lay_event;
	SDL_Surface			*lay_logo;

	SDL_Surface			*lay_logo_info;
	SDL_Surface			*lay_logo_post;
	SDL_Surface			*lay_logo_edit;
	SDL_Surface			*lay_logo_para;
	SDL_Surface			*lay_logo_shot;
	SDL_Surface			*lay_logo_canc;
	SDL_Surface			*lay_logo_appl;

	SDL_Surface			*select_option;
	SDL_Surface			*highlight_option;
	SDL_Surface			*select_square;
	SDL_Surface			*highlight_square;
	SDL_Surface			*menu_square;

	SDL_Color			white;
	SDL_Color			orange;
	SDL_Color			red;
	SDL_Color			green;
	SDL_Color			cyan;
	SDL_Color			blue;
	SDL_Color			violet;
	SDL_Color			grey;

	char				**loading_msg;
	size_t				loading_msg_size;

	SDL_Color			filter_color[3];

	int					size_of_char[2];

	t_vec_ocl			cam_pos;
	t_quat				cam_rot;

	char				menu;
	char				tmp_menu;

	char				redraw;
	char				event;
	char				str;

	char				menu_quit;
}						t_menu;

typedef struct			s_light
{
	t_vec_ocl			pos;
	t_vec_ocl			dir;

	t_dec				intensity;
	t_color				color;
	char				bytes[8];
}						t_light;

typedef struct			s_obj
{
	t_vec_ocl			pos;
	t_vec_ocl			scl;
	t_vec_ocl			dir;
	int					type;

	t_dec				spec;
	t_dec				trans;
	t_dec				refract;
	t_dec				reflect;
	char				texture;
	size_t				texture_scl;
	char				texture_norm;
	char				texture_spec;

	char				texture_mode;
	int					texture_xoff;
	int					texture_yoff;
	t_color				color;
	char				bytes[16];
}						t_obj;

typedef struct			s_rt
{
	t_vec_ocl			cam_pos;
	t_quat				cam_rot;
	t_obj				*objs;
	t_light				*lights;
	t_tex				*textures;
}						t_rt;

typedef struct			s_param
{
	char				quit;
	int					max_fps;
	int					fps;
	t_dec				step;

	char				mouse_right_button;

	int					rot;
	int					mouse_pos_x;
	int					mouse_pos_y;
	int					tmp_x;
	int					tmp_y;
	int					x_gap;
	int					y_gap;

	int					width;
	int					height;
	char				fullscreen;

	char				change;
	char				menu_change;
	char				merge_layers;
}						t_param;

typedef struct			s_ocl_rt
{
	cl_context			context;
	cl_kernel			*kernel;
	cl_command_queue	*queue;
}						t_ocl_rt;

typedef struct			s_mem_objs
{
	size_t				size;

	int					nb_obj;
	int					nb_light;
	int					nb_tex;
	cl_mem				mem_obj;
	cl_mem				mem_light;
	cl_mem				mem_tex;

	cl_mem				mem_tab;
	cl_mem				mem_border;
	cl_mem				mem_dir;
	cl_mem				mem_post;

	cl_mem				mem_ray;

	cl_mem				source;
	cl_mem				result;
}						t_mem_objs;

typedef struct			s_rt_param
{
	char				border;
	char				post;
	char				color;
	char				stereo;

	int					width;
	int					height;

	t_dec				fov;
	t_dec				scale;

	t_dec				ambient;

	size_t				r_limit;

	t_mem_objs			mem_objs;

	SDL_Surface			*lay_rt;
	SDL_Surface			*lay_stereo;
	SDL_Surface			*lay_post;
	SDL_Surface			*lay_border;

	SDL_Surface			*lay_dest;

	char				compute;
}						t_rt_param;

typedef struct			s_env
{
	t_ocl_rt			ocl_rt;
	t_param				param;
	t_rt				rt;
	t_menu				menu;

	t_rt_param			rt_param;
	t_rt_param			preview_param;

	SDL_Window			*win;
	SDL_Surface			*screen;

	SDL_Surface			*lay_menu;
	SDL_Event			event;

	TTF_Font			*pt_mono;
}						t_env;

/*
** PROTOTYPE
*/

void					ft_malloc_error(t_env *env);

void					ft_sdl_error(const char *error);
void					ft_sdl_init(t_env *env, const int width,
							const int height);
void					ft_sdl_destroy_win(SDL_Window **win);

void					ft_sdl_load_img(SDL_Surface **img,
							const char *img_path);
void					ft_sdl_load_bmp(SDL_Surface **img,
							const char *img_path);
void					ft_sdl_create_surface(SDL_Surface **surf,
							const int width, const int height);
void					ft_sdl_free_surface(SDL_Surface **surf);

void					ft_sdl_merge_layers(t_env *env);

void					ft_ttf_error(const char *error);
void					ft_ttf_close_font(TTF_Font **font);
void					ft_ttf_open_font(TTF_Font **font,
							const char *path, const int size);
void					ft_ttf_init(void);

SDL_Surface				*ft_ttf_render_txt_b(TTF_Font *font, const char *str,
							const SDL_Color color);
void					ft_ttf_render_txt_b_menu(t_env *env, const char *str,
							const SDL_Color color, const SDL_Rect rect);
void					ft_ttf_render_txt_b_screen(t_env *env, const char *str,
							const SDL_Color color, SDL_Rect rect);

void					ft_init_rt_param(t_env *env);
void					ft_compute_menu_pos(t_env *env);
void					ft_init_sdl(t_env *env);

void					ft_init_ocl_param(t_env *env);

t_tex					ft_texture_load(const char *file);

void					fake_parser(t_rt *rt);

void					ft_core(t_env *env);

void					ft_event_keydown(t_env *env);
void					ft_event_mousemotion(t_env *env);
void					ft_event_keyup(t_env *env);
void					ft_event_scroll(t_env *env);

char					*ft_str_percentage(t_dec val);

void					ft_event_buttonup(t_env *env);
void					ft_event_menu_editor3(t_env *env);
void					ft_event_menu_editor2(t_env *env);
void					ft_copy_param_content(t_rt_param *src,
							t_rt_param *dest);

int						ft_event_fps_limiter(t_env *env);

void					ft_update_win_specs(t_env *env);
void					ft_event_win(t_env *env);

void					ft_event_get_changes(t_env *env);
void					ft_move(t_env *env, t_vec move);
void					ft_compute_rt(t_env *env, t_rt_param *param);

void					ft_draw_menu(t_env *env);

void					ft_draw_event(t_env *env);

void					ft_draw_upleft_angle(const size_t *coor, int *img,
							const size_t width, const int color);
void					ft_draw_upright_angle(const size_t *coor, int *img,
							const size_t width, const int color);
void					ft_draw_downleft_angle(const size_t *coor, int *img,
							const size_t width, const int color);
void					ft_draw_downright_angle(const size_t *coor, int *img,
							const size_t width, const int color);

void					ft_draw_upleft_angle_out(const size_t *coor, int *img,
							const size_t width, const int color);

void					ft_draw_slider(t_menu *menu, t_slider *s);
void					ft_draw_slider_color(t_menu *menu);
void					ft_draw_slider_trans(t_env *env);
void					ft_draw_slider_reflect(t_env *env);
void					ft_draw_slider_refract(t_env *env);
void					ft_draw_slider_spec(t_env *env);
void					ft_draw_slider_ambient(t_env *env);
void					ft_draw_slider_fov(t_env *env);
void					ft_draw_slider_tex(t_env *env);
void					ft_draw_slider_tex_scl(t_env *env);

void					ft_compute_str_ambient(t_env *env);
void					ft_compute_str_fov(t_env *env);
void					ft_compute_str_reflect(t_env *env);
void					ft_compute_str_refract(t_env *env);
void					ft_compute_str_trans(t_env *env);
void					ft_compute_str_spec(t_env *env);
char					*ft_name_slider_tex(t_env *env);
void					ft_compute_str_tex(t_env *env);
void					ft_compute_str_tex_scl(t_env *env);

void					ft_update_slider_color(t_menu *menu);
void					ft_update_slider(t_menu *menu, t_slider *s,
							SDL_Rect rect, size_t pos);
void					ft_update_all_sliders(t_menu *menu);
void					ft_init_all_sliders(t_env *env);

void					ft_init_slider_color(t_menu *menu);
void					ft_init_slider_fov(t_menu *menu);
void					ft_init_slider_trans(t_menu *menu);
void					ft_init_slider_reflect(t_menu *menu);
void					ft_init_slider_refract(t_menu *menu);
void					ft_init_slider_spec(t_menu *menu);
void					ft_init_slider_ambient(t_env *env, t_menu *menu);
void					ft_init_slider_tex(t_env *env, t_menu *menu);
void					ft_init_slider_tex_scl(t_menu *menu);

int						ft_event_slider_trans(t_env *env);
int						ft_event_slider_reflect(t_env *env);
int						ft_event_slider_refract(t_env *env);
int						ft_event_slider_spec(t_env *env);
int						ft_event_slider_ambient(t_env *env);
int						ft_event_slider_fov(t_env *env);
int						ft_event_slider_tex(t_env *env);
void					ft_event_slider_tex2(t_env *env);
int						ft_event_slider_tex_scl(t_env *env);
int						ft_event_slider_color(t_env *env);
int						ft_event_slider(t_env *env, t_slider *slider,
							size_t x, size_t y);

void					rt_info(char *path, t_env *env);
void					init_env_info(int nb_obj, int nb_light, t_rt *rt);
void					init_env_ui(t_env *env);
void					fill_tab_obj(t_json_obj *j_obj, t_rt *rt, int i);
void					fill_tab_info(t_json_obj *j_obj, t_rt *rt, int i);
void					fill_texture(t_json_obj *j_obj, t_rt *rt);
void					fill_filter(t_json_obj *j_obj, t_env *env);
void					fill_ui(t_json_obj *j_obj, t_env *env);
void					ft_init_param(t_env *env);
void					get_env_obj_type(t_json_obj *j_obj, t_rt *rt, int i);
void					fill_object(t_json_obj *j_obj, t_rt_param *param,
							t_rt *rt, int i);
int						check_object(t_json_obj *obj, t_env *env, int nb_obj);
void					fill_texture_mode(t_json_obj *j_obj, t_rt *rt, int i);

void					ft_free_temp(t_info *temp);

void					ft_draw_all_angles(t_env *env);

void					ft_draw_square(const size_t *coor, int *img,
							const size_t width, const int color);

void					ft_draw_up_gradient(const size_t *coor, int *img,
							const size_t width);
void					ft_draw_left_gradient(const size_t *coor, int *img,
							const size_t width);
void					ft_draw_right_gradient(const size_t *coor, int *img,
							const size_t width);
void					ft_draw_down_gradient(const size_t *coor, int *img,
							const size_t width);

void					ft_bresenham(const size_t *coor, int *img,
							const size_t width, const int color);

void					ft_draw_all_gradients(t_env *env);

void					ft_draw_menu_str(t_env *env);
void					ft_draw_menu_str_editor(t_env *env);

void					ft_draw_ortho(t_env *env);

void					ft_display_load(t_env *env);
void					ft_load_msg(t_menu *menu);

void					ft_selector(t_env *env);
void					ft_selector_sliders2(t_env *env);

void					ft_compute_rt_blur(t_env *env, t_rt_param *param);
void					ft_compute_rt_greyscale(t_env *env, t_rt_param *param);
void					ft_compute_rt_sobel(t_env *env, t_rt_param *param);
void					ft_compute_rt_postprocess(t_env *env,
							t_rt_param *param);

void					ft_compute_rt_blur(t_env *env, t_rt_param *param);
void					ft_compute_rt_greyscale(t_env *env, t_rt_param *param);
void					ft_compute_rt_negative(t_env *env, t_rt_param *param);
void					ft_compute_rt_color_filter(t_env *env,
							t_rt_param *param);
void					ft_compute_rt_cyan_filter(t_env *env,
							t_rt_param *param);

void					ft_set_arg_base(t_env *env, t_rt_param *param);
void					ft_set_arg_selector(t_env *env,
						t_rt_param *param, cl_mem *id);
void					ft_set_arg_ref(t_env *env, t_rt_param *param);
void					ft_set_arg_light(t_env *env, t_rt_param *param);
void					ft_set_arg_ref_light(t_env *env);

void					ft_build_obj_postprocess(t_env *env);
void					ft_set_arg_blur(t_env *env, t_rt_param *param);
void					ft_set_arg_greyscale(t_env *env, t_rt_param *param);
void					ft_set_arg_sobel(t_env *env, t_rt_param *param);
void					ft_init_postprocess(t_env *env, t_rt_param *param);

void					ft_release_all(t_rt_param *param);

void					ft_compute_rt_border(t_env *env, t_rt_param *param);
void					ft_init_border(t_env *env, t_rt_param *param);

void					ft_compute_rt_antialiasing(t_env *env,
							t_rt_param *param);
void					ft_init_antialiasing(t_env *env, t_rt_param *param);
void					ft_set_arg_antialiasing(t_env *env, t_rt_param *param);

void					ft_screenshot(t_env *env);

void					ft_edit_obj_pos(t_obj *obj, t_vec_ocl new_pos);
void					ft_edit_obj_scl(t_obj *obj, t_vec_ocl new_scl);
void					ft_edit_obj_dir(t_obj *obj, t_vec_ocl new_dir);
void					ft_edit_obj_type(t_obj *obj, int new_type);

void					ft_edit_obj_spec(t_obj *obj, t_dec new_spec);
void					ft_edit_obj_trans(t_obj *obj, t_dec new_trans);
void					ft_edit_obj_refract(t_obj *obj, t_dec new_refract);
void					ft_edit_obj_reflect(t_obj *obj, t_dec new_reflect);

void					ft_set_arg_blur(t_env *env, t_rt_param *param);
void					ft_set_arg_greyscale(t_env *env, t_rt_param *param);
void					ft_set_arg_cyan_filter(t_env *env, t_rt_param *param);
void					ft_set_arg_color_filter(t_env *env, t_rt_param *param);
void					ft_set_arg_negative(t_env *env, t_rt_param *param);

void					ft_build_mem_obj(t_env *env, t_rt_param *param);
void					ft_build_mem_light(t_env *env, t_rt_param *param);
void					ft_build_mem_tex(t_env *env, t_rt_param *param);
void					ft_build_obj_rt(t_env *env, t_rt_param *param);
void					ft_rebuild_objs(t_env *env);

void					ft_init_rt(t_env *env, t_rt_param *param);
void					ft_check_stereo(t_rt_param *param);
void					ft_stereo(t_env *env, t_rt_param *param);
void					ft_compute_ref(t_env *env,
						t_rt_param *param, bool time_test);
void					ft_compute_rt_light(t_env *env, t_rt_param *param);
void					ft_compute_rt_ref(t_env *env, t_rt_param *param);

void					ft_event_sdl_kp_minus(t_env *env);
void					ft_event_sdlk_u(t_env *env);

void					ft_event_menu_postp(t_env *env);

void					ft_event_screenshot(t_env *env);

void					ft_event_fullscreen(t_env *env);

void					ft_compute_menu_str_pos_part4(t_env *env,
							int width, int height);
void					ft_draw_menu_str_info2(t_env *env);
void					ft_draw_menu_str_filter(t_env *env);

void					ft_menu_create_surf(SDL_Surface **surf,
							int width, int height, int color);
void					ft_draw_angle_option(SDL_Surface *surf);

int						get_obj_nb(t_json_obj *obj);
int						get_light_nb(t_json_obj *obj);
int						get_texture_nb(t_json_obj *obj);

void					ft_draw_option_selection(t_env *env);

void					ft_tex_pixels_4(t_tex *tex);

void					ft_add_obj(t_env *env);
t_obj					ft_new_obj(void);

void					put_nb_error(t_env *env);

void					ft_free_logo_surf(t_env *env);
void					ft_load_logo_surf(t_env *env);
void					ft_create_lay_logo(t_env *env);
void					ft_init_img(void);

#endif
