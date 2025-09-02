NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

SRCS = ft_allocate_large_zone.c \
       ft_allocate_new_page.c \
       ft_choose_zone.c \
       ft_allocate_block.c \
       ft_free.c \
       ft_malloc.c \
       ft_realloc.c \
       ft_realloc_utils.c \
       ft_show_alloc_mem.c \
       ft_printf.c \
       ft_printf_utils.c \
       ft_map.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: $(NAME) $(LINK)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS)

$(LINK): $(NAME)
	ln -sf $(NAME) $(LINK)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LINK)

re: fclean all

