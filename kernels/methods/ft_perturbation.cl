#ifndef FT_PERTURBATION_CL
# define FT_PERTURBATION_CL

# include "../kernel.h"

float                   ft_2D_perlin_noise(const float2 xy, const float res);
void                    ft_apply_normal_perturbation(t_vec3 pert, t_ray *ray);
void                    ft_apply_sin_to_norm(t_ray *ray);
t_vec3                  ft_rotate_from_dir(t_vec3 v, t_vec3 dir, t_vec3 up);
void                    ft_apply_noise_to_norm(t_ray *ray, const __constant t_obj *obj);

# include "./kernels/methods/ft_textures.cl"

float					ft_2D_perlin_noise(const float2 xy, const float res) //to make in 3D and opti memory
{
	//Adapter pour la résolution
	const float2		xy_cpy = xy / res;
	//On récupère les positions de la grille associée à (x,y)
	const int2			xy0 = convert_int2(xy_cpy);
	const int2			ij = xy0 & 255;
	const float2		tmp_xy = xy_cpy - convert_float2(xy0);
	const float2		C = 3 * tmp_xy * tmp_xy - 2 * tmp_xy * tmp_xy * tmp_xy;
    const float			unit = 1.0f / sqrt((t_dec)2);
   	const float			gradient2[][2] = {{unit,unit},{-unit,unit},{unit,-unit},
							{-unit,-unit},{1,0},{-1,0},{0,1},{0,-1}};
    const unsigned int	perm[] =
       {151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,
        142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,
        203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,
        74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,
        105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,
        187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,
        64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,
        47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,
        153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,
        112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,
        235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,
        127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,
        156,180};
	float s,t,u,v,Li1,Li2;
	int gi0,gi1,gi2,gi3;
    //Pour récupérer les vecteurs
    gi0 = perm[ij.x + perm[ij.y]] % 8;
    gi1 = perm[ij.x + 1 + perm[ij.y]] % 8;
    gi2 = perm[ij.x + perm[ij.y + 1]] % 8;
    gi3 = perm[ij.x + 1 + perm[ij.y + 1]] % 8;
    //on récupère les vecteurs et on pondère
    s = gradient2[gi0][0] * tmp_xy.x + gradient2[gi0][1] * tmp_xy.y;
    t = gradient2[gi1][0] * (tmp_xy.x - 1) + gradient2[gi1][1] * tmp_xy.y;
    u = gradient2[gi2][0] * tmp_xy.x + gradient2[gi2][1] * (tmp_xy.y - 1);
    v = gradient2[gi3][0] * (tmp_xy.x - 1) + gradient2[gi3][1] * (tmp_xy.y - 1);
    //Lissage
    Li1 = s + C.x * (t-s);
    Li2 = u + C.x * (v-u);
    return (Li1 + C.y * (Li2 - Li1));
}

void					ft_apply_normal_perturbation(__private t_vec3 pert, __private t_ray *ray)
{
	t_quat				q;

	q = 0;
	q.yzw = ray->normal.xyz;
	pert = cross(q.yzw, pert) * 2;
	ray->normal += pert * q.x + cross(q.yzw, pert);
}

void					ft_apply_sin_to_norm(__private t_ray *ray)
{
	ft_apply_normal_perturbation(sin(ray->p * 10) / 50, ray);
}

void                    ft_apply_noise_to_norm(__private t_ray *ray, const __constant t_obj *obj)
{
    t_vec2              t;

    if (obj->texture_mode == 0)
        t = ft_spheric_pos(ray->p, obj, 2048, 2048);
    else if (obj->texture_mode == 1)
        t = ft_cylindric_pos(ray->p, obj, 2048, 2048);
    else if (obj->texture_mode == 2)
        t = ft_planar_pos(ray->p, obj, 2048, 2048);
    else
        return ;

    ft_apply_normal_perturbation((t_vec3){0, 0, ft_2D_perlin_noise(t, 20) / 14}, ray);
}

t_vec3                  ft_rotate_from_dir(t_vec3 v, t_vec3 dir, t_vec3 up)
{
    __private t_quat        rotation;
    __private t_vec3        tmp;

    tmp = cross(up, dir);
    rotation.zyx = tmp;
    rotation.z *= -1;
    rotation.w = sqrt(sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z)) + dot(up, dir);
    rotation = fast_normalize(rotation);

    tmp = cross(rotation.yzw, v) * 2;
    return(v + (tmp * rotation.x + cross(rotation.yzw, tmp)));
}

#endif
