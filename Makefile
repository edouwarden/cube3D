NAME			=	cub3D
MLX_FOLDER 		=	./mlx
MLX				= 	mlx/libmlx.a
GNL				=	utils/get_next_line/get_next_line.a
LIBFT			=	utils/libft/libft.a
CC 				= 	cc
SRCS 			= 	src/0_parsing/0_check_map.c \
					src/0_parsing/color_handling.c \
					src/0_parsing/line_handling.c \
					src/0_parsing/fraud_fill.c \
					src/0_parsing/fraud_fill_utils.c \
					src/0_parsing/is_something.c \
					src/0_parsing/2_get_info_map.c \
					src/0_parsing/1_parsing.c \
					src/0_parsing/3_init_texture.c \
					src/0_parsing/4_parse_wall.c \
					src/1_input_handling/input.c \
					src/2_engine_core/raycaster.c \
					src/3_rendering/0_renderer.c \
					src/3_rendering/1_3D.c \
					src/3_rendering/1_3D_utils.c \
					src/3_rendering/2_minimap.c \
					src/4_game_loop/loop.c \
					src/4_game_loop/mouse_handler.c \
					src/error_handling.c \
					src/main.c \

BONUS			=	0
# Change object files location
OBJS			=	$(SRCS:%.c=obj/%.o)
LFLAGS			=	-L. -lXext -L. -lX11 -lm
CFLAGS			=	-I include -I utils/libft -Wall -Werror -Wextra -DBONUS=${BONUS} -g3

all					:	obj ${NAME}

$(MLX_FOLDER):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_FOLDER)
	$(MAKE) -C $(MLX_FOLDER)

$(MLX): $(MLX_FOLDER)

# Create obj directories
obj:
	@mkdir -p obj/0_init
	@mkdir -p obj/1_input_handling
	@mkdir -p obj/2_engine_core
	@mkdir -p obj/3_rendering
	@mkdir -p obj/4_game_loop

$(NAME) : $(OBJS) $(MLX) $(GNL) $(LIBFT)
	@${CC} ${OBJS} $(LIBFT) ${MLX} ${GNL} ${LFLAGS} -o $(NAME) 

$(GNL):
	@make -C utils/get_next_line/

$(LIBFT):
	@make -C utils/libft/

bonus:
	@$(MAKE) BONUS=1 all

obj/%.o : %.c | $(MLX)
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -c $< -o $@

clean			:
					@rm -rf $(MLX_FOLDER)
					@make clean -C utils/get_next_line/
					@make clean -C utils/libft/
					@rm -rf obj

fclean			:	clean
					@rm -rf ${MLX}
					@rm -rf /mlx
					@rm -rf ${GNL}
					@rm -rf ${LIBFT}
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re bonus
