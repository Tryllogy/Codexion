NAME := codexion
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -g3

HEADERS_DIR := coders
HEADERS := coders.h

UTILS_DIR := utils
SRC_DIR := src
THREAD_DIR := thread

SRC := main.c \
$(SRC_DIR)/errors.c \
$(SRC_DIR)/success.c \
$(UTILS_DIR)/init_data.c \
$(UTILS_DIR)/lst.c \
$(UTILS_DIR)/ft_strlen.c \
$(THREAD_DIR)/create_thread.c \


all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)


clean:
	rm -rf *.o *.d

fclean: clean
	rm -rf $(NAME)

re: fclean all

run:
	valgrind --leak-check=full ./codexion 2 1 1 1 1 1 1 fifo

.PHONY: all clean fclean re