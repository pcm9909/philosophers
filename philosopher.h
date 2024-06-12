#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define INPUT_ERR_1 "Input Error : Value must more than 0\n"
# define INPUT_ERR_2 "Input Error : Value must be dight\n"
# define INPUT_ERR_3 "Input Error : Number of values must be 5 or 6\n"
# define ALLOC_ERR "Alloc Error : Fail to alloc memory\n"
# define MUTEX_ERR_1 "Mutex Error : Fail to init mutex\n"
# define MUTEX_ERR_2 "Mutex Error : Fail to destoy mutex\n"
# define CREATE_ERR "Thread Error : Fail to create thread\n"
# define JOIN_ERR "Thread Error : Fail to join thread\n"
# define TIME_ERR "Time Error : Fail to gettimeofday()\n"

# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIE "died\n"
# define FORK "has taken a fork\n"

struct s_resource;

typedef struct s_philo
{
	int id;
	int cnt_eat;
	int time_last_eat;
	int l_fork;
	int r_fork;
	pthread_t thread;
	struct s_resource *resource;
} t_philo;

typedef struct s_resource
{
	int num_philos;
	int time_eat;
	int time_sleep;
	int time_die;
	int cnt_must_eat;
	int time_stamp;
	int cmp_finish_eat;
	t_philo *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t mutex_print;
	pthread_mutex_t mutex_eat;
	pthread_mutex_t mutex_cmp_finish;
} t_resource;

void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif