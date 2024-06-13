#include "philosopher.h"

int print_error(char *str)
{
	ft_putstr_fd(str, 1);
	return (1);
}
int get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int check_finish(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->resource->mutex_cmp_finish);
	if (status)
	{
		philo->resource->finish = 1;
		pthread_mutex_unlock(&philo->resource->mutex_cmp_finish);
	}
	if (philo->resource->finish)
	{
		pthread_mutex_unlock(&philo->resource->mutex_cmp_finish);
		return (1);
	}
	pthread_mutex_unlock(&philo->resource->mutex_cmp_finish);
	return 0;
}

void print_status(t_philo *philo, char *str)
{
	if(check_finish(philo, 0))
		return ;
	pthread_mutex_lock(&philo->resource->mutex_print);
	ft_putnbr_fd(get_time()-philo->resource->time_stamp ,1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(str, 1);
	pthread_mutex_unlock(&philo->resource->mutex_print);
}

int init_resource(char **argv, int argc, t_resource *resource)
{
	resource->num_philos = ft_atoi(argv[1]);
	resource->time_die = ft_atoi(argv[2]);
	resource->time_eat = ft_atoi(argv[3]);
	resource->time_sleep = ft_atoi(argv[4]);
	resource->time_stamp = get_time();
	if(resource->time_stamp == 1)
	{
		return (print_error(TIME_ERR));
	}
	if(argc == 6)
	{
		resource->cnt_must_eat = ft_atoi(argv[5]);
	}
	else
	{
		resource->cnt_must_eat = -1;
	}
	return (0);
}


int alloc_resource(t_resource *resource)
{
	int num_of_philos;
	int i;

	num_of_philos = resource->num_philos;
	resource->philos = malloc(sizeof(t_philo) * num_of_philos);
	if(!resource->philos)
		return print_error(ALLOC_ERR);
	resource->forks = malloc(sizeof(pthread_mutex_t) * num_of_philos);
	if(!resource->forks)
		return print_error(ALLOC_ERR);
	resource->time_stamp = get_time();
	i = 0;
	while(i < num_of_philos)
	{
		resource->philos[i].id = i + 1;
		resource->philos[i].cnt_eat = 0;
		resource->philos[i].l_fork = i;
		resource->philos[i].r_fork = (i + 1) % num_of_philos;
		resource->philos[i].cnt_eat = 0;
		resource->philos[i].time_last_eat = resource->time_stamp;
		resource->philos[i].resource = resource;
		i++;
	}
	return (0);
}

int init_mutex(t_resource *resource)
{
	int i;

	i = 0;
	while(i < resource->num_philos)
	{
		if(pthread_mutex_init(&resource->forks[i], NULL))
		{
			return print_error(MUTEX_ERR_1);
		}
		i++;
	}
	if(pthread_mutex_init(&resource->mutex_print, NULL))
	{
		return print_error(MUTEX_ERR_1);
	}
	if(pthread_mutex_init(&resource->mutex_eat, NULL))
	{
		return print_error(MUTEX_ERR_1);
	}
	if(pthread_mutex_init(&resource->mutex_cmp_finish, NULL))
	{
		return print_error(MUTEX_ERR_1);
	}
	return (0);
}

int preprocessing(int argc, char **argv, t_resource *resource)
{
	if(init_resource(argv, argc, resource))
	{
		return (1);
	}
	if(alloc_resource(resource))
	{
		return (1);
	}
	if(init_mutex(resource))
	{
		return (1);
	}
	return (0);
}

int check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->resource->mutex_eat);
	if(get_time() - philo->time_last_eat >= philo->resource->time_die)
	{
		print_status(philo, DIE);
		check_finish(philo, 1);
		pthread_mutex_unlock(&philo->resource->mutex_eat);
		return (1);
	}
	else if(philo->resource->cnt_must_eat != -1 && philo->cnt_eat >= philo->resource->cnt_must_eat)
	{
		philo->resource->cmp_finish_eat++;
		if(philo->resource->cmp_finish_eat >= philo->resource->num_philos)
		{
			check_finish(philo, 1);
			pthread_mutex_unlock(&philo->resource->mutex_eat);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->resource->mutex_eat);
	return (0);
}

void *routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	if(philo->id % 2 == 0)
	{
		usleep(philo->resource->time_eat * 1000);
	}
	while(1)
	{
		if(check_finish(philo, 0))
			return (0);
		ft_take_forks(philo);
		ft_eat(philo);
		ft_drop_forks(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
}

int create_and_run_philos(t_resource *resource)
{
	int i;

	if(resource->num_philos == 1)
	{
		print_status(&resource->philos[0], FORK);
		usleep(resource->time_eat * 1000);
		print_status(&resource->philos[0], DIE);
		return (0);
	}
	i = 0;
	while(i < resource->num_philos)
	{
		if(pthread_create(&resource->philos[i].thread, NULL, routine, &resource->philos[i]))
		{
			return print_error(CREATE_ERR);
		}
		i++;
	}
	return (0);
}

int validate_input(char **argv)
{
	int i;
	int j;

	i = 1;
	while(argv[i])
	{
		if(ft_atoi(argv[i]) <= 0)
		{
			return print_error(INPUT_ERR_1);
		}
		j = 0;
		while(argv[i][j])
		{
			if(ft_isdigit(argv[i][j]) == 0)
			{
				return print_error(INPUT_ERR_2);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int free_resource(t_resource *resource)
{
	int i;

	i = 0;
	while(i < resource->num_philos)
	{
		pthread_mutex_destroy(&resource->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&resource->mutex_print);
	pthread_mutex_destroy(&resource->mutex_eat);
	pthread_mutex_destroy(&resource->mutex_cmp_finish);
	free(resource->philos);
	free(resource->forks);
	return (0);
}

int checker(t_resource *resource)
{
	int i;
	int status;

	status = 1;
	while(status)
	{
		i = 0;
		resource->cmp_finish_eat = 0;
		while(i < resource->num_philos)
		{
			if(check_dead(&resource->philos[i]))
			{
				status = 0;
			}
			i++;
		}
		usleep(10);
	}
	i = 0;
	while (i < resource->num_philos)
	{
		pthread_join(resource->philos[i].thread, NULL);
		i++;
	}
	return free_resource(resource);
}


int main(int argc, char **argv)
{
	t_resource resource;

	if(argc == 5 || argc == 6)
	{
		if(validate_input(argv))
		{
			return (1);
		}
		if(preprocessing(argc, argv, &resource))
		{
			return (1);
		}
		if(create_and_run_philos(&resource))
		{
			return (1);
		}
		checker(&resource);
	}
	else
	{
		print_error(INPUT_ERR_3);
	}
	return (0);
}
