
NAME		=	philo_one

CC			=	gcc

FLAGS		=	-Wall -Werror -Wextra

SRC			=	$(addprefix $(SRC_PATH)/,$(SOURCE)) main.c

SRC_PATH	=	src

SOURCE		=	tools.c launch_threads.c management_var.c cycle_thread.c monitoring_threads.c

HEADER		=	$(addprefix $(INC_PATH)/,$(INCLUDE))

INCLUDE		=	philo_one.h

INC_PATH	=	headers

OBJ			=	$(SRC:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJ)
				$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lpthread

debug		:	$(OBJ)
				make $(NAME)
				$(CC) -g3 -fno-omit-frame-pointer -fsanitize=address $(FLAGS) $(OBJ) -o debug -lpthread

%.o			:	%.c $(HEADER)
				$(CC) $(FLAGS) -I headers -c $< -o $@

clean		:
				rm -rf $(OBJ)

fclean		:	clean
				rm -f $(NAME)
				rm -f debug
re			:	fclean all