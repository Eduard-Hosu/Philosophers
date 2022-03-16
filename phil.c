/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosu <ehosu@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:28:53 by ehosu             #+#    #+#             */
/*   Updated: 2022/03/16 17:46:33 by ehosu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

t_bool is_game_over(t_config *config)
{
	t_bool	done;

	pthread_mutex_lock(&config->m_gameover);
	done = config->game_over;
	pthread_mutex_unlock(&config->m_gameover);
	return (done);
}

int	get_times_eaten(t_phil *phil)
{
	int	eaten;

	pthread_mutex_lock(&phil->config->m_gameover);
	eaten = phil->t_eaten;
	pthread_mutex_unlock(&phil->config->m_gameover);
	return (eaten);
}

long	get_death_time(t_phil *phil)
{
	long	death_time;

	pthread_mutex_lock(&phil->config->m_gameover);
	death_time = phil->die;
	pthread_mutex_unlock(&phil->config->m_gameover);
	return (death_time);
}

void	*phil_activity(void *arg)
{
	t_phil		*phil;
	t_config	*config;

	phil = (t_phil *)arg;
	config = phil->config;
	if (config->n_philo == 1)
	{
		print_activity(phil, FORK);
		usleep(config->time_to_die * 1000);
		print_activity(phil, DEAD);
		return (NULL);
	}
	//every second philosopher will wait for the rest to eat
	if (phil->id % 2)
		usleep(phil->config->time_to_eat * 1000);
	while (!is_game_over(config))
	{
		phil_eat(phil);
		phil_sleep(phil);
		phil_think(phil);
	}
	return (NULL);
}

t_bool	config_phil(t_config *config)
{
	t_phil		*phil;
	static int	i = 0;

	phil = malloc(sizeof(t_phil));
	if (!phil)
	{
		game_over(config);
		return (false);
	}
	i++;
	phil->id = i;
	phil->next = config->last;
	config->last = phil;
	phil->config = config;
	phil->t_eaten = 0;
	phil->die = get_time() + config->time_to_die;
	pthread_mutex_init(&phil->p_fork, NULL);
	pthread_create(&phil->thread, NULL, phil_activity, phil);
	return (true);
}

t_bool	configuration(t_config *config)
{
	int	i;

	config->game_over = false;
	config->last = NULL;
	config->start_game = get_time();
	pthread_mutex_init(&config->write_status, NULL);
	pthread_mutex_init(&config->m_gameover, NULL);
	i = 0;
	while (i < config->n_philo)
	{
		if (config_phil(config) == false)
			return (false);
		i++;
	}
	first_to_last(config);
	return (true);
}

int main(int argc, char **argv)
{
	t_config	config;

	// printf("here\n");
	// exit(1);
	if (argc < 5 || argc > 6 || !config_data(&config, argv))
	{
		printf("Use it like:\n");
		printf("./philo n_of_philosophers time_to_die time_to_eat \
				time_to_sleep [n_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (configuration(&config) == false)
		return (1);
	//SOLVED: Check ho dies
	check_ho_dies(&config);
	//SOLVED: End game
	game_over(&config);
	return (1);
}