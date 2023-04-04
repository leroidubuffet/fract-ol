NAME		= 	fractol

CC			= 	gcc
CFLAGS		= 	-Wall -Wextra -Werror -std=c89 -Imlx -march=native -O3
CFLAGS2		=	-lmlx -Imlx -framework OpenGL -framework AppKit -o

INCLUDES	= 	include/

SRC_DIR		=	sources/
SRC			= 	message_utils.c \
				args_utils.c \
				main.c \
				screen_utils.c \
				fractol_utils.c \
				img_utils.c \
				num_utils.c \
				key_utils.c \
				fractals.c 

SRCS		=	$(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR	=	objects/
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJS): $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(NAME): $(OBJS)
	@echo "Compiling fract'ol"
	@$(CC) $(CFLAGS2) $(NAME) $(OBJS) $(INC)
	@echo "Fract'ol is ready"

bonus: all

clean:
	@echo "Cleaning object files"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Cleaning fract'ol"
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean