NAME := codexion
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -g3

HEADERS_DIR := coders
HEADERS := coders.h

UTILS_DIR := utils
SRC_DIR := src
THREAD_DIR := thread
ACTIONS_DIR := actions
FREE_DIR := frees

SRC := main.c \
$(SRC_DIR)/errors.c \
$(SRC_DIR)/success.c \
$(UTILS_DIR)/init_data.c \
$(UTILS_DIR)/lst.c \
$(UTILS_DIR)/ft_strlen.c \
$(UTILS_DIR)/get_time.c \
$(THREAD_DIR)/create_thread.c \
$(THREAD_DIR)/join_thread.c \
$(ACTIONS_DIR)/compile.c \
$(ACTIONS_DIR)/debug.c \
$(ACTIONS_DIR)/refactor.c \
$(FREE_DIR)/free.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)


clean:
	rm -rf *.o *.d

fclean: clean
	rm -rf $(NAME)

re: fclean all

run: 						#N_CODER BURNOUT COMPILE DEBUG REFACTOR REQUIRED DONGLE_CD SCHEDULE
	valgrind --leak-check=full ./codexion 5 100 10 10 10 1 1 fifo

run2: 	#N_CODER BURNOUT COMPILE DEBUG REFACTOR REQUIRED DONGLE_CD SCHEDULE
	./codexion 3 600 200 200 200 1 1 fifo

.PHONY: all clean fclean re