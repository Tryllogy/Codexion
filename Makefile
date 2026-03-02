NAME := codexion
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -g3

HEADERS_DIR := coders
HEADERS := coders.h

UTILS_DIR := utils
MAIN_RETURN_DIR := main_return
THREAD_DIR := thread
ACTIONS_DIR := actions
FREE_DIR := free
MUTEX_DIR := mutex
INIT_DIR := init

SRC := main.c \
$(MAIN_RETURN_DIR)/errors.c \
$(MAIN_RETURN_DIR)/success.c \
$(UTILS_DIR)/lst.c \
$(UTILS_DIR)/ft_strlen.c \
$(UTILS_DIR)/get_time.c \
$(UTILS_DIR)/check_args.c \
$(UTILS_DIR)/check_malloc.c \
$(MUTEX_DIR)/mutex.c \
$(THREAD_DIR)/create_thread.c \
$(THREAD_DIR)/join_thread.c \
$(ACTIONS_DIR)/compile.c \
$(ACTIONS_DIR)/debug.c \
$(ACTIONS_DIR)/refactor.c \
$(FREE_DIR)/free.c \
$(INIT_DIR)/init_values.c \
$(INIT_DIR)/init_structs.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)


clean:
	rm -rf *.o *.d

fclean: clean
	rm -rf $(NAME)

re: fclean all

run: 						#N_CODER BURNOUT COMPILE DEBUG REFACTOR REQUIRED DONGLE_CD SCHEDULE
	valgrind --leak-check=full ./codexion 5 800 200 200 200 1 1 fifo

run2: 	#N_CODER BURNOUT COMPILE DEBUG REFACTOR REQUIRED DONGLE_CD SCHEDULE
	./codexion 6 800 200 200 200 1 200 fifo

.PHONY: all clean fclean re