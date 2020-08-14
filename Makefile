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
MACHO_PATH = mach-o/
LIBFT_PATH = libft/
LIBFT_INCS_PATH = $(addprefix $(LIBFT_PATH), $(INCS_PATH))
NM_INCS_PATH = $(addprefix $(NM_PATH), $(INCS_PATH))
NM_OBJS_PATH = $(addprefix $(NM_PATH), $(OBJS_PATH))
NM_SRCS_PATH = $(addprefix $(NM_PATH), $(SRCS_PATH))
MACHO_OBJS_PATH = $(addprefix $(OBJS_PATH), $(MACHO_PATH))
MACHO_SRCS_PATH = $(addprefix $(SRCS_PATH), $(MACHO_PATH))

SRCS_FILES = file_list error symbol_list
NM_SRCS_FILES = main sort print
MACHO_SRCS_FILES = macho symtab

SRCS = $(addsuffix .c, $(addprefix $(SRCS_PATH), $(SRCS_FILES)))
OBJS = $(addsuffix .o, $(addprefix $(OBJS_PATH), $(SRCS_FILES)))

NM_SRCS = $(addsuffix .c, $(addprefix $(NM_SRCS_PATH), $(NM_SRCS_FILES)))
NM_OBJS = $(addsuffix .o, $(addprefix $(NM_OBJS_PATH), $(NM_SRCS_FILES)))
ifneq (,$(findstring Darwin,$(OS)))
	MACHO_SRCS += $(addsuffix .c, $(addprefix $(MACHO_SRCS_PATH), $(MACHO_SRCS_FILES)))
	MACHO_OBJS += $(addsuffix .o, $(addprefix $(MACHO_OBJS_PATH), $(MACHO_SRCS_FILES)))
endif
ifneq (,$(findstring Linux,$(OS)))
	MACHO_SRCS_FILES = macho
	MACHO_SRCS += $(addsuffix .c, $(addprefix $(MACHO_SRCS_PATH), $(MACHO_SRCS_FILES)))
	MACHO_OBJS += $(addsuffix .o, $(addprefix $(MACHO_OBJS_PATH), $(MACHO_SRCS_FILES)))
endif

LIBFT = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

all: $(LIBFT) $(OBJS_PATH) $(MACHO_OBJS_PATH) $(NM_OBJS_PATH) $(OBJS) $(MACHO_OBJS) $(NM_NAME)

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCS_PATH) -I$(LIBFT_INCS_PATH)

$(MACHO_OBJS_PATH):
	mkdir -p $(MACHO_OBJS_PATH)

$(MACHO_OBJS_PATH)%.o: $(MACHO_SRCS_PATH)%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCS_PATH) -I$(LIBFT_INCS_PATH)

$(NM_OBJS_PATH):
	mkdir $(NM_OBJS_PATH)

$(NM_OBJS_PATH)%.o: $(NM_SRCS_PATH)%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCS_PATH) -I$(NM_INCS_PATH) -I$(LIBFT_INCS_PATH)

$(NM_NAME): $(OBJS) $(MACHO_OBJS) $(NM_OBJS)
	$(CC) -o $(NM_NAME) $(OBJS) $(MACHO_OBJS) $(NM_OBJS) $(LFLAGS) -L$(LIBFT_PATH) -lft

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(OBJS_PATH) $(MACHO_OBJS_PATH) $(NM_OBJS_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NM_NAME)

re: fclean all
