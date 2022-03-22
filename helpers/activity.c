/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosu <ehosu@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:37:20 by ehosu             #+#    #+#             */
/*   Updated: 2022/03/22 12:11:09 by ehosu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phil.h"

void	activity_time(t_config *config, int m_sec)
{
	long int	current_time;

	current_time = get_time();
	while (!is_game_over(config))
	{
		if (get_time() > current_time + m_sec)
			return ;
		usleep(1000);
	}
}

void	phil_eat(t_phil *phil)
{
	pthread_mutex_lock(&phil->p_fork);
	print_activity(phil, FORK);
	pthread_mutex_lock(&phil->next->p_fork);
	print_activity(phil, FORK);
	print_activity(phil, EAT);
	pthread_mutex_lock(&phil->config->m_gameover);
	phil->t_eaten++;
	phil->die = get_time() + phil->config->time_to_die;
	pthread_mutex_unlock(&phil->config->m_gameover);
	activity_time(phil->config, phil->config->time_to_eat);
	pthread_mutex_unlock(&phil->next->p_fork);
	pthread_mutex_unlock(&phil->p_fork);
}

void	phil_sleep(t_phil *phil)
{
	print_activity(phil, SLEEP);
	activity_time(phil->config, phil->config->time_to_sleep);
}

void	phil_think(t_phil *phil)
{
	print_activity(phil, THINK);
}

void	game_over(t_config *config)
{
	t_phil	*phil_pointer;
	t_phil	*kill_this_one;

	phil_pointer = config->last->next;
	pthread_join(config->last->thread, NULL);
	while (phil_pointer != config->last)
	{
		pthread_join(phil_pointer->thread, NULL);
		phil_pointer = phil_pointer->next;
	}
	phil_pointer = phil_pointer->next;
	pthread_mutex_destroy(&config->last->p_fork);
	free(config->last);
	while (phil_pointer != config->last)
	{
		kill_this_one = phil_pointer;
		phil_pointer = phil_pointer->next;
		pthread_mutex_destroy(&kill_this_one->p_fork);
		free(kill_this_one);
	}
	pthread_mutex_destroy(&config->write_status);
}
