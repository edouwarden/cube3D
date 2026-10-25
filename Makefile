NAME			=	cub3D
MLX_FOLDER 		=	./mlx
MLX				= 	mlx/libmlx.a
GNL				=	utils/get_next_line/get_next_line.a
LIBFT			=	utils/libft/libft.a
CC 				= 	cc
SRCS 			= 	src/parsing/check_map.c \
					src/parsing/color_handling.c \
					src/parsing/line_handling.c \
					src/parsing/flood_fill.c \
					src/parsing/flood_fill_utils.c \
					src/parsing/char_checks.c \
					src/parsing/get_info_map.c \
					src/parsing/parsing.c \
					src/parsing/init_texture.c \
					src/parsing/parse_wall.c \
					src/input/input.c \
					src/engine/raycaster.c \
					src/rendering/renderer.c \
					src/rendering/render_3d.c \
					src/rendering/render_3d_utils.c \
					src/rendering/minimap.c \
					src/game_loop/loop.c \
					src/game_loop/mouse_handler.c \
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

# Create obj directory
obj:
	@mkdir -p obj

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
