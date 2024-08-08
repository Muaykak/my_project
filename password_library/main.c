#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define PASS_FILE "password.dict"

void	ft_putstr(char *str);
void	ft_putnbr(int nbr);
int		line_strcount(int line_num);
char	*malloc_get_line(int line_num);
int		open_line(int line_num);
int		check_printable(char *str);
int		check_argv_printable(int ac, char **av);
int		check_input_format(char *str);
int		check_all_input_format(int ac, char **av);
int		ft_strlen(char *str);
char	*malloc_dup_lowercase(char *str);

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
		dup = malloc_dup_lowercase(av[1]);
		ft_putstr(dup);
		ft_putstr("\n");
		free(dup);
	}

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
	int		fd;
	int		k;
	char	c;

	fd = open_line(line_num);
	if (fd == -1)
		return (-1);
	k = 0;
	while (read(fd, &c, 1) != 0 && c != '\n')
		k++;
	close(fd);
	return (k);
}

// open file then go to that line num   
// IF SUCCESS RETURN fd  IF FAIL RETURN -1
int	open_line(int line_num)
{
	int		fd;
	int		k;
	char	c;

	line_num--;
	if (line_num < 0)
		return (-1);
	fd = open(PASS_FILE, O_RDONLY);
	while (line_num > 0)
	{
		k = read(fd, &c, 1);
		if (c == '\n')
			line_num--;
		if (k == 0)
		{
			close(fd);
			return (-1);
		}
	}
	return (fd);
}

// this  function is to malloc the str to get to 
// ******* NEED   free() ***********
char	*malloc_get_line(int line_num)
{
	int		k;
	int		fd;
	int		i;
	char	*str;

	k = line_strcount(line_num);
	if (k == -1)
		return (NULL);
	str = (char *)malloc((k + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	fd = open_line(line_num);
	i = 0;
	while (read(fd, &str[i], 1) != 0 && str[i] != '\n')
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
