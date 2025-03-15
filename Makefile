NAME = ./philo


# ************************************
# Sources                            *
# ************************************

C_DIR = src

C_FILES = main.c \
	init.c \
	routine/routine.c \
	routine/routine_state.c \
	routine/routine_wait.c \
	routine/action.c \
	routine/action_put.c \
	routine/action_utils.c \
	routine/fairness.c \
	utils/exit.c \
	utils/free.c \
	utils/number.c \
	utils/time.c \
	utils/mutex.c \
	utils/thread.c \
	utils/get.c \
	utils/set.c \

SRCS = $(addprefix $(C_DIR)/,$(C_FILES))


# ************************************
# Objects                            *
# ************************************

O_DIR = src/_obj

OBJS = $(addprefix $(O_DIR)/,$(C_FILES:.c=.o))


# ************************************
# Headers                            *
# ************************************

H_DIR = inc

H_FILES = philo.h \

HEADERS = $(addprefix $(H_DIR)/,$(H_FILES))


# ************************************
# Flags                              *
# ************************************

CFLAGS = -Wall -Wextra -Werror


# ************************************
# Includes                           *
# ************************************

INCLUDES = -I$(H_DIR)


# ************************************
# Rules                              *
# ************************************

all: $(NAME)

$(O_DIR)/%.o: $(C_DIR)/%.c Makefile $(HEADERS)
	@mkdir -p $(@D)
	cc -c -o $@ $< $(INCLUDES) $(CFLAGS)

$(NAME): $(OBJS)
	cc -o $@ $^

clean:
	rm -rf $(O_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# ************************************
# Phony                              *
# ************************************

.PHONY: all clean fclean re
