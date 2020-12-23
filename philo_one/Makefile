
NAME		=	philo_one

CC			=	gcc

FLAGS		=	-Wall -Werror -Wextra

SRC			=	$(addprefix $(SRC_PATH)/,$(SOURCE)) main.c

SRC_PATH	=	src

SOURCE		=	tools.c

HEADER		=	$(addprefix $(INC_PATH)/,$(INCLUDE))

INCLUDE		=	philo_one.h

INC_PATH	=	headers

OBJ			=	$(SRC:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJ)
				$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lpthread

%.o			:	%.c $(HEADER)
				$(CC) $(FLAGS) -c $< -o $@

clean		:
				rm -rf $(OBJ) main.o

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all