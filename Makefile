NAME			=	cub3D
MLX_FOLDER 		=	./mlx
MLX				= 	mlx/libmlx.a
GNL				=	utils/get_next_line/get_next_line.a
LIBFT			=	utils/libft/libft.a
CC 				= 	cc
SRCS 			= 	src/0_parsing/0_check_map.c \
					src/0_parsing/1_parsing.c \
					src/0_parsing/2_get_info_map.c \
					src/0_parsing/3_init_texture.c \
					src/0_parsing/4_parse_wall.c \
					src/0_parsing/color_handling.c \
					src/0_parsing/line_handling.c \
					src/0_parsing/flood_fill.c \
					src/0_parsing/flood_fill_utils.c \
					src/0_parsing/char_checks.c \
					src/1_input_handling/input.c \
					src/2_engine_core/raycaster.c \
					src/3_rendering/0_renderer.c \
					src/3_rendering/1_3D.c \
					src/3_rendering/1_3D_utils.c \
					src/3_rendering/2_minimap.c \
					src/3_rendering/3_ray_debug.c \
					src/4_game_loop/loop.c \
					src/4_game_loop/mouse_handler.c \
					src/error_handling.c \
					src/main.c \

BONUS			=	0
# Change object files location
OBJDIR			=	obj/$(BONUS)
CONFIG			=	obj/.bonus_$(BONUS)
OBJS			=	$(SRCS:%.c=$(OBJDIR)/%.o)
LFLAGS			=	-L. -lXext -L. -lX11 -lm
CFLAGS			=	-I include -I utils/libft -std=gnu17 -Wall -Werror -Wextra -DBONUS=${BONUS} -O2 -g3

all					:	$(OBJDIR) $(CONFIG) ${NAME}

$(MLX_FOLDER):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_FOLDER)
	$(MAKE) -C $(MLX_FOLDER)

$(MLX): $(MLX_FOLDER)

# Create obj directory and flag the build variant
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(CONFIG): $(OBJDIR)
	@rm -f obj/.bonus_0 obj/.bonus_1
	@touch $(CONFIG)

$(NAME) : $(OBJS) $(CONFIG) $(MLX) $(GNL) $(LIBFT)
	@${CC} ${OBJS} $(LIBFT) ${MLX} ${GNL} ${LFLAGS} -o $(NAME) 

$(GNL):
	@make -C utils/get_next_line/

$(LIBFT):
	@make -C utils/libft/

bonus:
	@$(MAKE) BONUS=1 all

$(OBJDIR)/%.o : %.c | $(MLX)
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
