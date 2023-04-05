CC=gcc
CFLAGS=-Wall -Wextra -pedantic -g # <-- '-g' parameter needed for including debug symbols
LDFLAGS=-lpthread 			      # <-- variable set/needed for pthreads library

.PHONY: all
all:
	
	$(CC) $(CFLAGS) -o balanced_array balanced_array.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o balanced_paren balanced_paren.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o balanced_paren2 balanced_paren2.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_reordering array_reordering.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_reordering_using_linked_list array_reordering_using_linked_list.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_equal_stacks array_equal_stacks.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_game_of_two_stacks array_game_of_two_stacks.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o binary_tree_level_order binary_tree_level_order.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o binary_tree_top_view binary_tree_top_view.c $(LDFLAGS)

clean:
	rm  balanced_array balanced_paren balanced_paren2 array_manipulation\
		array_reordering array_reordering_using_linked_list array_equal_stacks array_game_of_two_stacks\
		binary_tree_level_order binary_tree_top_view