CFILES="srcs/get_file_content.c srcs/split.c srcs/grid.c srcs/island.c srcs/initialise_grid.c srcs/deduction_solve.c srcs/bin_op.c srcs/dequeue.c srcs/bfs.c srcs/extend_islands.c srcs/backtracking.c srcs/is_position_valid.c srcs/bitset.c srcs/codingame_main.c"
cat ./includes/*.h > codingame.c
cat $CFILES | grep -v "#" >> codingame.c
