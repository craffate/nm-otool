ifeq ($(OS),)
	OS := $(shell uname -s)
endif

NM_NAME = ft_nm
LIBFT_NAME = libft.a

CC = clang

CFLAGS = -Wall -Wextra -Werror

NM_PATH = nm/
INCS_PATH = includes/
OBJS_PATH = objs/
SRCS_PATH = srcs/
NM_MACHO_PATH = mach-o/
LIBFT_PATH = libft/
LIBFT_INCS_PATH = $(addprefix $(LIBFT_PATH), $(INCS_PATH))
NM_INCS_PATH = $(addprefix $(NM_PATH), $(INCS_PATH))
NM_OBJS_PATH = $(addprefix $(NM_PATH), $(OBJS_PATH))
NM_SRCS_PATH = $(addprefix $(NM_PATH), $(SRCS_PATH))
NM_MACHO_OBJS_PATH = $(addprefix $(NM_OBJS_PATH), $(NM_MACHO_PATH))
NM_MACHO_SRCS_PATH = $(addprefix $(NM_SRCS_PATH), $(NM_MACHO_PATH))

NM_SRCS_FILES = main file_list
NM_MACHO_SRCS_FILES = mach-o symtab

NM_SRCS = $(addsuffix .c, $(addprefix $(NM_SRCS_PATH), $(NM_SRCS_FILES)))
NM_OBJS = $(addsuffix .o, $(addprefix $(NM_OBJS_PATH), $(NM_SRCS_FILES)))
ifneq (,$(findstring Darwin,$(OS)))
	NM_SRCS += $(addsuffix .c, $(addprefix $(NM_MACHO_SRCS_PATH), $(NM_MACHO_SRCS_FILES)))
	NM_OBJS += $(addsuffix .o, $(addprefix $(NM_MACHO_OBJS_PATH), $(NM_MACHO_SRCS_FILES)))
endif

LIBFT = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

all: $(LIBFT) $(NM_OBJS_PATH) $(NM_NAME)

$(NM_OBJS_PATH):
	mkdir $(NM_OBJS_PATH) $(NM_MACHO_OBJS_PATH)

$(NM_NAME): $(NM_OBJS)
	$(CC) -o $(NM_NAME) $(NM_OBJS) $(LFLAGS) -L$(LIBFT_PATH) -lft

$(NM_OBJS_PATH)%.o: $(NM_SRCS_PATH)%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(NM_INCS_PATH) -I$(LIBFT_INCS_PATH)

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(NM_OBJS_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NM_NAME)

re: fclean all
