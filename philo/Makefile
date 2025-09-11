NAME = philo
CC = cc
CFLAGS = -pthread -Wall -Wextra -Werror -O3 -Wno-unused-result -march=native -funroll-loops -g
SRC_DIR = src
INC_DIR = include
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/args.c \
      $(SRC_DIR)/init.c \
      $(SRC_DIR)/libft.c \
      $(SRC_DIR)/monitor.c \
      $(SRC_DIR)/print.c \
      $(SRC_DIR)/routine.c \
      $(SRC_DIR)/threads.c \
      $(SRC_DIR)/utils.c
OBJ = $(SRC:.c=.o)

ifeq ($(VALGRIND),1)
	CFLAGS += -DVALGRIND=1
endif

all: $(NAME)

val:
	@$(MAKE) fclean
	@$(MAKE) VALGRIND=1 all

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -I$(INC_DIR) -o $(NAME)
	@echo "Eseguibile philo creato con successo!"

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re