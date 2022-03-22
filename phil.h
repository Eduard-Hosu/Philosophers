/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosu <ehosu@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:39:46 by ehosu             #+#    #+#             */
/*   Updated: 2022/03/22 12:22:24 by ehosu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_action { SLEEP, EAT, THINK, DEAD, FORK}	t_action;
typedef enum e_bool { false, true}	t_bool;

//Philosopher
typedef struct s_phil
{
	size_t				id;
	pthread_t			thread;
	int					t_eaten;
	long				die;
	pthread_mutex_t		p_fork;
	struct s_phil		*next;
	struct s_config		*config;
}	t_phil;

//Philosopfer config
typedef struct s_config
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				times_to_eat;
	int				time_to_sleep;
	long int		start_game;
	pthread_mutex_t	write_status;
	pthread_mutex_t	m_gameover;
	t_phil			*last;
	volatile t_bool	game_over;
}	t_config;

void		first_to_last(t_config *config);
t_bool		number(char *str);
int			phil_atoi(const char *str);
t_bool		config_data(t_config *config, char **argv);
t_bool		is_game_over(t_config *config);
int			get_times_eaten(t_phil *phil);
long		get_death_time(t_phil *phil);
long int	get_time(void);
void		phil_eat(t_phil *phil);
void		phil_sleep(t_phil *phil);
void		phil_think(t_phil *phil);
void		print_activity(t_phil *phil, t_action action);
void		check_ho_dies(t_config *config);
void		game_over(t_config *config);

#endif