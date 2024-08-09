#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define PASS_FILE "test.txt"
#define BUFF_SIZE 1

void	ft_putstr(char *str);
void	ft_putnbr(int nbr);
int		line_strcount(int line_num);
char	*malloc_get_line(int line_num);
int		open_line(int line_num, int *fd);
int		check_printable(char *str);
int		check_argv_printable(int ac, char **av);
int		check_input_format(char *str);
int		check_all_input_format(int ac, char **av);
int		ft_strlen(char *str);
char	*malloc_dup_lowercase(char *str);
int		ft_strcmp(char *s1, char *s2);
int		check_strstr(char *str, char *to_find);
int		check_related(char *str, char *to_find);
int		print_data(int linenum);
ssize_t			file_count(void);
int		ft_abs(int nbr);

/*
int	main(int ac, char **av)
{
	char	*dup;

	if (check_argv_printable(ac, av) == 0)
	{
		ft_putstr("The arguments should have only printable characters");
		return (0);
	}
	if (ac == 2)
	{
		find_data(av[1]);
	}

}
*/

int	main(void)
{
	int	j;

	j = file_count();
	ft_putnbr(j);
	ft_putstr("\n");

}

int	add_front_space(int space)
{
	int	file_length;

	file_length = file_count();

}

int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-1 * nbr);
	else
		return (nbr);
}

// count amount of characters of the file
ssize_t	file_count(void)
{
	ssize_t			count;
	int		fd;
	char	c;

	fd = open(PASS_FILE, O_RDONLY);
	count = 0;
	while (read(fd, &c, 1) != 0)
	{
		count++;
	}
	close (fd);
	return (count);
}

//print the set of desired data
int	print_data(int linenum)
{
	char	*temp;
	int		i;

	temp = malloc_get_line(linenum);
	if (temp == NULL)
		return (0);
	i = 0;
	while (temp[0] != '\0')
	{
		ft_putstr(temp);
		ft_putstr("\n");
		i++;
		free(temp);
		temp = malloc_get_line(linenum + i);
		if (temp == NULL)
			return (0);
	}
	return (1);
}

/*
// separate string from malloc_get_line
int	malloc_sep_front_back(char *malloc_get, char *front, char *back)
{
	if (check_input_format(malloc_get) == 1)
	{
		
	}
}
*/

/*
//this function will find the line that has matching name then return that line number
int	find_strcmp(char *str)
{
	int	line_num;

	line_num = 1;
}
*/


//use strstr to find related names or other data by convert both string and to_find to lowercase
//alphabet
int	check_related(char *str, char *to_find)
{
	char	*str_temp;
	char	*tofind_temp;
	int		j;

	if (str == NULL || to_find == NULL)
		return (0);
	str_temp = malloc_dup_lowercase(str);
	tofind_temp = malloc_dup_lowercase(to_find);
	j = check_strstr(str_temp, tofind_temp);
	free(str_temp);
	free(tofind_temp);
	return (j);
}

int	check_strstr(char *str, char *to_find)
{
	int	index[4];

	if (str == NULL || to_find == NULL)
		return (0);
	if (to_find[0] == '\0')
		return (1);
	index[0] = 0;
	while (str[index[0]] != '\0')
	{
		index[1] = 0;
		if (str[index[0]] == to_find[index[1]])
		{
			while (str[index[0] + index[1]] == to_find[index[1]] && to_find[index[1]])
				index[1]++;
			if (to_find[index[1]] == '\0')
				return (1);
		}
		index[0]++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

//chage the given string into lowercase and put it into malloc()
// ******* NEED   free() ***********
char	*malloc_dup_lowercase(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	temp = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			temp[i] = str[i] + 32;
		else
			temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	return (&temp[0]);
}
//count how many characters in the given string
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
// to check when having more than 3 arguments
// to formar shoult be "Name: something describe"
// this function is to determine ":" and " " is there in the arguments
int	check_all_input_format(int ac, char **av)
{
	int	i;
	if (ac < 4)
	{
		ft_putstr("The argument count is less than 4 thus should not come to check_input_format() function.\n");
		return (0);
	}
	i = 1;

	while (i < ac)
	{
		if (check_input_format(av[i]) == 0)
		{
			ft_putstr("wrong input format in argument[");
			ft_putnbr(i);
			ft_putstr("]\n");
			ft_putstr("The argument should layout as \"Name: ...description..\" \n");
			return (0);
		}
		i++;
	}
}

// sub function from check_all_input_format()
int	check_input_format(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '\0' && str[i] == ':')
		return (0);
	while (str[i] != '\0' && str[i] != ':')
		i++;
	if (str[i] == ':')
	{
		i++;
		while (str[i] != '\0' && str[i] == ' ')
			i++;
		if (str[i] != '\0' && str[i] != ' ')
			return (1);
		else
			return (0);

	}
	else
		return (0);
}

int	check_argv_printable(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (check_printable(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

// to check if string have only printable characters
int	check_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 32 || str[i] > 126)
		{
			ft_putstr("The argument must not include unprintable characters.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

// to count the string size of that line in the file
int	line_strcount(int line_num)
{
	int		fd[1];
	int		k;
	char	c;

	open_line(line_num, fd);
	if (fd[0] == -1)
		return (-1);
	k = 0;
	while (read(fd[0], &c, 1) != 0 && c != '\n')
		k++;
	close(fd[0]);
	return (k);
}

// open file then go to that line num   
// IF SUCCESS RETURN the amount that read IF FAIL RETURN -1
int	open_line(int line_num, int *fd)
{
	int		k;
	int		count;
	char	c;

	line_num--;
	if (line_num < 0)
	{
		fd[0] = -1;
		return (-1);
	}
	fd[0] = open(PASS_FILE, O_RDONLY);
	count = 0;
	while (line_num > 0)
	{
		k = read(fd[0], &c, 1);
		if (c == '\n')
			line_num--;
		if (k == 0)
		{
			close(fd[0]);
			fd[0] = -1;
			return (-1);
		}
		count++;
	}
	return (count);
}

// this  function is to malloc the str to get to 
// ******* NEED   free() ***********
char	*malloc_get_line(int line_num)
{
	int		k;
	int		fd[1];
	int		i;
	char	*str;

	k = line_strcount(line_num);
	if (k == -1)
		return (NULL);
	str = (char *)malloc((k + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	open_line(line_num, fd);
	i = 0;
	while (read(fd[0], &str[i], 1) != 0 && str[i] != '\n')
		i++;
	str[i] = '\0';
	return (&str[0]);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_putnbr(int nbr)
{
	char	c;

	if (nbr < -2147483647)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nbr < 0)
	{
		nbr = nbr * -1;
		write(1, "-", 1);
	}
	if (nbr / 10 != 0)
	{
		ft_putnbr(nbr / 10);
	}
	c = (nbr % 10) + 48;
	write(1, &c, 1);
}
