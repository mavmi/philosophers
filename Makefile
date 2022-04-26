NAME		=	philo


SRCS_DIR	=	srcs
HDRS_DIR	=	include


HDRS		=	$(addprefix $(HDRS_DIR)/, philo.h utils.h data_utils.h philo_thread_funcs.h handler_thread_funcs.h input_parser.h ft_itoa.h)
SRCS		= 	$(addprefix $(SRCS_DIR)/, philo.c utils.c data_utils.c philo_thread_funcs.c handler_thread_funcs.c input_parser.c ft_itoa.c)
OBJS		=	$(SRCS:.c=.o)


FLAGS		=	-Wall -Wextra -Werror
CC			=	gcc
GCC			=	$(CC) $(FLAGS)


all:			$(NAME)

%.o:			%.c $(HDRS)
				$(GCC) -c -o $@ $<
 
$(NAME):		$(OBJS)
				$(GCC) $(OBJS) -o $(NAME)

clean:				
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
