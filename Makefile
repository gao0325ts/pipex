NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

LIB_DIR = ./lib
SRCS_DIR = ./srcs

LIB = lib.a

SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(SRCS:.c=.o)
INCLUDES = -I ./includes -I ./$(LIB_DIR)/includes

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_DIR)/$(LIB) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: all

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIB_DIR)/$(LIB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re