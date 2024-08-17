#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define PASS_FILE "password.dict"
#define BUFF_SIZE 1024

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
int		print_datanum(int data_num);
int	print_data(char **data);
ssize_t			file_count(void);
int		ft_abs(int nbr);
int		add_space(int space, int cursor);
int		add_space_sub1(int space);
void	add_space_sub2(int space, int *file_length, char *temp);
void	add_space_sub2(int space, int *file_length, char *temp);
void	add_space_sub3(int cursor, int *file_length, int space, char *temp);
void	add_space_sub4(int cursor, int space);
void	loop_line_strcount(int *line_num, int *data_num, int *b);
char	**malloc_get_data(int data_num);
void	free_malloc_get_data(char **data);
int		malloc_sep_front_back(char *malloc_get, char **front, char **back);
char	*malloc_front(char *malloc_get);
char	*malloc_back(char *malloc_get);
int		loop_check_strcmp_noformat(char ****dataset, char *to_find);
char	*malloc_ft_strdup(char *str);
char	**malloc_dup_data(char **data);
int		malloc_loop_check_related_noformat(char *to_find, char ****dataset);
int		find_data_noformat(char *to_find, char ****dataset);
int		find_data(char *to_find, char ****dataset);
int		print_dataset(char ***dataset);
void	free_dataset(char ***dataset);

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

int	main(int ac, char **av)
{
	char	***dataset;
	int	j;

	if (ac == 2)
	{
		j = find_data(av[1], &dataset);
		if (j == 0)
		{
			ft_putstr("There is no matching data from given string.\n");
			return (0);
		}
		else
		{
			if (j > 0)
			{
				print_dataset(dataset);
				ft_putstr("Showing ");
				ft_putnbr(j);
				ft_putstr(" matching data\n\n");
				free_dataset(dataset);
				return (0);
			}
			else if (j < 0)
			{
				print_dataset(dataset);
				ft_putstr("Showing ");
				ft_putnbr(j * -1);
				ft_putstr(" related data\n\n");
				free_dataset(dataset);
				return (0);
			}
		}
		return (0);
	}
	return (1);
}

// to find that if any data match that string
//return 0 if cannot find any data that matches
int	find_data(char *to_find, char ****dataset)
{
	char	***temp;
	int		j;

	if (check_input_format(to_find) == 0)
	{
		j = find_data_noformat(to_find, &temp);
		if (j != 0)
		{
			*dataset = temp;
			return (j);
		}
		*dataset = NULL;
		return (0);
	}
	return (0);
}

int	find_data_noformat(char *to_find, char ****dataset)
{
	char	***temp;
	int		j;

	j = loop_check_strcmp_noformat(&temp, to_find);
	if (j != 0)
	{
		*dataset = temp;
		return (j);
	}
	j = malloc_loop_check_related_noformat(to_find, &temp);
	if (j == 0)
	{
		*dataset = NULL;
		return (0);
	}
	*dataset = temp;
	return (-1 * j);
}

void	free_dataset(char ***dataset)
{
	int	index;

	if (dataset == NULL)
		return ;
	index = 0;
	while (dataset[index] != NULL)
	{
		free_malloc_get_data(dataset[index]);
		index++;
	}
	free(dataset);
	return ;
}

//Return related result count and malloc back to sum parameter
// 0 If cannot find any related result or failed
int	malloc_loop_check_related_noformat(char *to_find, char ****dataset)
{
	int		index[1];
	int		data_num;
	int		count;
	char	**temp;
	char	*front;
	char	*back;
	char	***result;

	data_num = 1;
	count = 0;
	temp = malloc_get_data(data_num);
	while (temp != NULL)
	{
		index[0] = 0;
		while (temp[index[0]] != NULL)
		{
			if (malloc_sep_front_back(temp[index[0]], &front, &back) == 0)
			{
				*dataset = NULL;
				return (0);
			}
			if (check_related(back, to_find) == 1)
			{
				count++;
				free(front);
				free(back);
				break ;
			}
			free(front);
			free(back);
			index[0]++;
		}
		data_num++;
		free_malloc_get_data(temp);
		temp = malloc_get_data(data_num);
	}
	if (count == 0)
	{
		result = NULL;
		dataset = &result;
		return (0);
	}
	result = (char ***)malloc((count + 1) * sizeof(char **));
	if (result == NULL)
	{
		*dataset = NULL;
		return (0);
	}
	if (temp != NULL)
		free_malloc_get_data(temp);
	data_num = 1;
	count = 0;
	temp = malloc_get_data(data_num);
	while (temp != NULL)
	{
		index[0] = 0;
		while (temp[index[0]] != NULL)
		{
			if (malloc_sep_front_back(temp[index[0]], &front, &back) == 0)
			{
				*dataset = NULL;
				return (0);
			}
			if (check_related(back, to_find) == 1)
			{
				result[count] = malloc_dup_data(temp);
				count++;
				free(front);
				free(back);
				break ;
			}
			free(front);
			free(back);
			index[0]++;
		}
		data_num++;
		free_malloc_get_data(temp);
		temp = malloc_get_data(data_num);
	}
	result[count] = NULL;
	*dataset = result;
	return (count);
}

char	**malloc_dup_data(char **data)
{
	int		index[2];
	char	**temp;

	if (data == NULL)
		return (NULL);
	index[0] = 0;
	while (data[index[0]] != NULL)
		index[0]++;
	temp = (char **)malloc((index[0] + 1) * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	index[1] = 0;
	while (index[1] < index[0])
	{
		temp[index[1]] = malloc_ft_strdup(data[index[1]]);
		if (temp[index[1]] == NULL)
			return (NULL);
		index[1]++;
	}
	temp[index[1]] = NULL;
	return (temp);
}

char	*malloc_ft_strdup(char *str)
{
	char	*temp;
	int		index;

	if (str == NULL)
		return (NULL);
	temp = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (temp == NULL)
		return (NULL);
	index = 0;
	while (str[index] != '\0')
	{
		temp[index] = str[index];
		index++;
	}
	temp[index] = '\0';
	return (temp);
}

int	loop_check_strcmp_noformat(char ****dataset, char *to_find)
{
	int		index[1];
	int		data_num;
	int		count;
	char	**temp;
	char	*front;
	char	*back;
	char	***result;

	data_num = 1;
	count = 0;
	temp = malloc_get_data(data_num);
	while (temp != NULL)
	{
		index[0] = 0;
		while (temp[index[0]] != NULL)
		{
			if (malloc_sep_front_back(temp[index[0]], &front, &back) == 0)
			{
				*dataset = NULL;
				return (0);
			}
			if (ft_strcmp(back, to_find) == 0)
			{
				count++;
				free(front);
				free(back);
				break ;
			}
			free(front);
			free(back);
			index[0]++;
		}
		data_num++;
		free_malloc_get_data(temp);
		temp = malloc_get_data(data_num);
	}
	if (count == 0)
	{
		result = NULL;
		dataset = NULL;
		return (0);
	}
	result = (char ***)malloc((count + 1) * sizeof(char **));
	if (result == NULL)
	{
		*dataset = NULL;
		return (0);
	}
	if (temp != NULL)
		free_malloc_get_data(temp);
	data_num = 1;
	count = 0;
	temp = malloc_get_data(data_num);
	while (temp != NULL)
	{
		index[0] = 0;
		while (temp[index[0]] != NULL)
		{
			if (malloc_sep_front_back(temp[index[0]], &front, &back) == 0)
			{
				*dataset = NULL;
				return (0);
			}
			if (ft_strcmp(back, to_find) == 0)
			{
				result[count] = malloc_dup_data(temp);
				count++;
				free(front);
				free(back);
				break ;
			}
			free(front);
			free(back);
			index[0]++;
		}
		data_num++;
		free_malloc_get_data(temp);
		temp = malloc_get_data(data_num);
	}
	result[count] = NULL;
	*dataset = result;
	return (count);
}
/*
//this function will find the line that has matching name then return that line number
int	loop_check_strcmp_noformat(char ****dataset, char *to_find)
{
	int		index[1];
	int		data_num;
	char	**temp;
	char	*front;
	char	*back;

	data_num = 1;
	temp = malloc_get_data(data_num);
	while (temp != NULL)
	{
		index[0] = 0;
		while (temp[index[0]] != NULL)
		{
			if (malloc_sep_front_back(temp[index[0]], &front, &back) == 0)
			{
				*data = NULL;
				return (0);
			}
			if (check_related("Name", front) == 1)
			{
				if (ft_strcmp(back, to_find) = 0)
				{
					free(front);
					free(back);
					data = &temp;
					return (1);
				}
			}
			free(front);
			free(back);
			index[0]++;
		}
		data_num++;
		free_malloc_get_data(temp);
		temp = malloc_get_data(data_num);
	}
	if (temp == NULL)
		*data = NULL;
	return (0);
}
*/


// separate string from malloc_get_line
int	malloc_sep_front_back(char *malloc_get, char **front, char **back)
{
	if (check_input_format(malloc_get) == 0)
		return (0);
	*front = malloc_front(malloc_get);
	*back = malloc_back(malloc_get);
	if (front == NULL || back == NULL)
		return (0);
	else
		return (1);
}

char	*malloc_front(char *malloc_get)
{
	int	index[2];
	char	*front;

	if (malloc_get == NULL)
		return (NULL);
	index[0] = 0;
	while (malloc_get[index[0]] != ':' \
	&& malloc_get[index[0]] != '\0')
	index[0]++;
	front = (char *)malloc((index[0] + 1) * sizeof(char));
	if (front == NULL)
		return (NULL);
	index[1] = 0;
	while (index[1] < index[0])
	{
		front[index[1]] = malloc_get[index[1]];
		index[1]++;
	}
	front[index[1]] = '\0';
	return (&front[0]);
}

char	*malloc_back(char *malloc_get)
{
	int		i[3];
	char	*back;

	if (malloc_get == NULL)
		return (NULL);
	i[0] = 0;
	while (malloc_get[i[0]] != ':' && malloc_get[i[0]] != '\0')
		i[0]++;
	if (malloc_get[i[0]] != '\0')
		i[0]++;
	while (malloc_get[i[0]] == ' ' && malloc_get[i[0]] != '\0')
		i[0]++;
	i[1] = 0;
	while (malloc_get[i[1] + i[0]] != '\0')
		i[1]++;
	back = (char *)malloc((i[1] + 1) * sizeof(char));
	if (back == NULL)
		return (NULL);
	i[2] = 0;
	while (i[2] < i[1])
	{
		back[i[2]] = malloc_get[i[0] + i[2]];
		i[2]++;
	}
	back[i[2]] = '\0';
	return (&back[0]);
}

int	print_dataset(char ***dataset)
{
	int	index[2];


	if (dataset == NULL)
		return (0);
	index[0] = 0;
	while(dataset[index[0]] != NULL)
	{
		index[1] = 0;
		while (dataset[index[0]][index[1]] != NULL)
		{
			ft_putstr(dataset[index[0]][index[1]]);
			ft_putstr("\n");
			index[1]++;
		}
		ft_putstr("\n");
		index[0]++;
	}
	return (1);
}

int	print_data(char **data)
{
	int	i;

	if (data == NULL)
		return (0);
	i = 0;
	while (data[i] != NULL)
	{
		ft_putstr(data[i]);
		ft_putstr("\n");
		i++;
	}
	return (1);
}
//print the set of desired data
int	print_datanum(int data_num)
{
	char	**data;
	int	i;

	data = malloc_get_data(data_num);
	if (data == NULL)
		return (0);
	i = 0;
	while (data[i] != NULL)
	{
		ft_putnbr(i);
		ft_putstr(" :");
		ft_putstr(data[i]);
		ft_putstr("\n");
		i++;
	}
	free_malloc_get_data(data);
	return (1);
}

// this function is to free the malloc_get_data(as)
void	free_malloc_get_data(char **data)
{
	int	i;

	if (data == NULL)
		return ;
	i = 0;
	while (data[i] != NULL)
	{
		free(data[i]);
		i++;
	}
	free(data);
}

//this function will return an array of strings that contain the data
char	**malloc_get_data(int data_num)
{
	char	**save;
	int		i;
	int		line_num;
	int		b;

	i = 0;
	line_num = 1;
	if (data_num < 1)
		return (NULL);
	loop_line_strcount(&line_num, &data_num, &b);
	if (line_strcount(line_num) <= 0)
		return (NULL);
	save = (char **)malloc((b + 1) * sizeof(char *));
	i = 0;
	while (i < b)
	{
		save[i] = malloc_get_line(line_num);
		i++;
		line_num++;
	}
	save[i] = NULL;
	return (&save[0]);
}

void	loop_line_strcount(int *line_num, int *data_num, int *b)
{
	while (line_strcount(*line_num) != -1 && *data_num > 0)
	{
		if (line_strcount(*line_num) > 0)
		{
			*data_num = *data_num - 1;
			*b = 0;
			while (line_strcount(*line_num + *b) > 0)
				*b = *b + 1;
			if (*data_num <= 0)
				return ;
			*line_num =  *line_num + *b;
		}
		else
			*line_num = *line_num + 1;
	}
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

int	add_space(int space, int cursor)
{
	int	file_length;
	char	*temp;

	file_length = file_count();
	if (cursor < 0 || cursor > file_length)
		return (0);
	temp = (char *)malloc((BUFF_SIZE + 1) * sizeof(char));
	if (temp == NULL)
		return (0);
	temp[BUFF_SIZE] = '\0';
	add_space_sub1(space);
	file_length -= BUFF_SIZE;
	while (file_length >= cursor) 
	{
		add_space_sub2(space, &file_length, temp);
		if (file_length == cursor)
			break ;
		file_length -= BUFF_SIZE;
	}
	if (file_length < cursor)
		add_space_sub3(cursor, &file_length, space, temp);
	add_space_sub4(cursor, space);
	free(temp);
	return (1);
}

int	add_space_sub1(int space)
{
	int	fd;
	int	i;

	fd = open(PASS_FILE, O_RDWR | O_APPEND);
	if (fd < 0)
		return (0);
	i = 0;
	while (i < space)
	{
		write(fd, " ", 1);
		i++;
	}
	close(fd);
	return (1);
}

void	add_space_sub2(int space, int *file_length, char *temp)
{
	char	c;
	int		i;
	int		fd;

	fd = open(PASS_FILE, O_RDWR);
	i = 0;
	while (i < *file_length)
	{
		read(fd, &c, 1);
		i++;
	}
	read(fd, temp, BUFF_SIZE);
	close(fd);
	fd = open(PASS_FILE, O_RDWR);
	i = 0;
	while (i < (space + *file_length))
	{
		read(fd, &c, 1);
		i++;
	}
	write(fd, temp, BUFF_SIZE);
	close(fd);
}

void	add_space_sub3(int cursor, int *file_length, int space, char *temp)
{
	int		fd;
	int		i;
	char	c;

	fd = open(PASS_FILE, O_RDWR);
	i = 0;
	while (i < cursor)
	{
		read(fd, &c, 1);
		i++;
	}
	read(fd, temp, (BUFF_SIZE - (cursor - *file_length)));
	close(fd);
	fd = open(PASS_FILE, O_RDWR);
	i = 0;
	while (i < space + cursor)
	{
		read(fd, &c, 1);
		i++;
	}
	write(fd, temp, BUFF_SIZE - ((cursor - *file_length)));
	close(fd);
}

void	add_space_sub4(int cursor, int space)
{
	int		fd;
	int 		i;
	char	c;

	fd = open(PASS_FILE, O_RDWR);
	i = 0;
	while (i < cursor)
	{
		read(fd, &c, 1);
		i++;
	}
	i = 0;
	while (i < space)
	{
		write(fd, " ", 1);
		i++;
	}
	close(fd);
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
	if (s1 == NULL || s2 == NULL)
		return (300);
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
	if (str == NULL)
		return (-1);
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
	return (1);
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
