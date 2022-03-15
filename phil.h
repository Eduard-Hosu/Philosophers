/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosu <ehosu@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:39:46 by ehosu             #+#    #+#             */
/*   Updated: 2022/03/15 17:10:00 by ehosu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum {SLEEP, EAT, THINK, DEAD, FORK}	t_action;
typedef enum {false, true}	t_bool;

//Philosopher
typedef struct s_phil
{
	size_t				id;
	pthread_t			thread;
	int					t_eaten;
	int					die;
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
	t_phil			*last;
	volatile t_bool	game_over;
}	t_config;

void		first_to_last(t_config *config);
t_bool		number(char *str);
int			phil_atoi(const char *str);
t_bool		config_data(t_config *config, char **argv);
long int	get_time();
void		phil_eat(t_phil *phil);
void		phil_sleep(t_phil *phil);
void		phil_think(t_phil *phil);
void		print_activity(t_phil *phil, t_action action);
void		check_ho_dies(t_config *config);
void		game_over(t_config *config);

#endif