NAME := codexion
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread
MODE := fifo

HEADERS_DIR := coders
HEADERS := coders.h

UTILS_DIR := utils
MAIN_RETURN_DIR := main_return
THREAD_DIR := thread
ACTIONS_DIR := actions
FREE_DIR := free
INIT_DIR := init
EDF_DIR := edf
SET_GET_DIR := set_get

SRC := main.c \
$(MAIN_RETURN_DIR)/errors.c \
$(MAIN_RETURN_DIR)/success.c \
$(UTILS_DIR)/get_time.c \
$(UTILS_DIR)/check_args.c \
$(THREAD_DIR)/create_thread.c \
$(THREAD_DIR)/join_thread.c \
$(ACTIONS_DIR)/compile.c \
$(ACTIONS_DIR)/debug.c \
$(ACTIONS_DIR)/refactor.c \
$(ACTIONS_DIR)/use_dongle.c \
$(ACTIONS_DIR)/routine.c \
$(ACTIONS_DIR)/wait_turn.c \
$(ACTIONS_DIR)/wait_turn_utils.c \
$(ACTIONS_DIR)/monitor.c \
$(FREE_DIR)/free.c \
$(INIT_DIR)/init_struct_utils.c \
$(INIT_DIR)/init_structs.c \
$(INIT_DIR)/init_values.c \
$(INIT_DIR)/init_values_utils.c \
$(INIT_DIR)/init_time.c \
$(EDF_DIR)/edf.c \
$(SET_GET_DIR)/set_get.c \

JUNKDIR := .cache
OBJDIR := $(JUNKDIR)/objs
DEPDIR := $(JUNKDIR)/deps

OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
DEPS := $(patsubst %.c,$(DEPDIR)/%.d,$(SRC))

all: $(NAME)

run: $(NAME)
	./$(NAME) 4 800 100 100 100 1 400 $(MODE)

valgrind: CFLAGS += -g
valgrind: re
	valgrind --leak-check=full --track-origins=yes --log-file=valgrind.log ./$(NAME) 4 800 200 200 200 1 100 $(MODE)

helgrind: CFLAGS += -g
helgrind: re
	valgrind --tool=helgrind --log-file=helgrind.log ./$(NAME) 4 800 200 200 200 1 100 $(MODE)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

-include $(DEPS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(patsubst $(OBJDIR)/%.o,$(DEPDIR)/%.d,$@))
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -MF $(patsubst $(OBJDIR)/%.o,$(DEPDIR)/%.d,$@)

clean:
	rm -rf *.o *.d
	rm -rf $(OBJDIR) $(DEPDIR)
	rm -rf $(JUNKDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re run