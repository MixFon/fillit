#ifndef FILLiT_H
#define FILLiT_H

typedef struct			s_tetr
{
	int					tetr_x[4];
	int					tetr_y[4];
	struct s_tetr		*next;
	char				ch;
}						t_tetr;

#endif
