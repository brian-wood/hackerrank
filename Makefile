CC=gcc
CFLAGS=-Wall -Wextra -pedantic -g # <-- '-g' parameter needed for including debug symbols
LDFLAGS=-lpthread 			      # <-- variable set/needed for pthreads library

.PHONY: all
all:
	# GCC programs	
	$(CC) $(CFLAGS) -o balanced_array balanced_array.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o balanced_paren balanced_paren.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o balanced_paren2 balanced_paren2.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_reordering array_reordering.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_reordering_using_linked_list array_reordering_using_linked_list.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_equal_stacks array_equal_stacks.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_game_of_two_stacks array_game_of_two_stacks.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o binary_tree_level_order binary_tree_level_order.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o binary_tree_top_view binary_tree_top_view.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o hash_table_ransom_note hash_table_ransom_note.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o hash_table_ransom_note_fast hash_table_ransom_note_fast.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_ranked_player array_ranked_player.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_ranked_player_recursive array_ranked_player_recursive.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_ranked_player_v3 array_ranked_player_v3.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o search_bsearch_examples search_bsearch_examples.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o search_qsort_examples search_qsort_examples.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o sum_multiples_3_5_7_to_n sum_multiples_3_5_7_to_n.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_single_to_double array_single_to_double.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o pointer_comparison pointer_comparison.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o array_find_stock_price_average array_find_stock_price_average.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o utopian_tree utopian_tree.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o angry_professor angry_professor.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o beautiful_days_at_the_movies beautiful_days_at_the_movies.c $(LDFLAGS)
	$(CC) $(CFLAGS) -o viral_advertising viral_advertising.c $(LDFLAGS)

clean:
	rm  balanced_array balanced_paren balanced_paren2 array_reordering\
		array_reordering_using_linked_list array_equal_stacks array_game_of_two_stacks\
		binary_tree_level_order binary_tree_top_view hash_table_ransom_note hash_table_ransom_note_fast\
		array_ranked_player array_ranked_player_recursive array_ranked_player_v3\
		search_bsearch_examples search_qsort_examples sum_multiples_3_5_7_to_n\
		array_single_to_double pointer_comparison array_find_stock_price_average utopian_tree\
		angry_professor beautiful_days_at_the_movies viral_advertising