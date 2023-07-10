#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM_COMPANIES 6
#define NUM_STK_PRICES 3
#define STK_NAME_LEN 5

struct node {
    char name[STK_NAME_LEN];
    float average;
    struct node *next;
};

struct node *insert_node(struct node *root, struct node *curr)
{

    // Insert node in correct location
    if (root == NULL) {
        root = curr;
    }
    else if (curr->average > root->average) {
        curr->next = root;
        root = curr;
    }
    else {
        root->next = insert_node(root->next, curr);
    }

    return root;
}

/* Find Top Performers.
 * Parameters:
 * num_comp  - number of companies
 * company   - 1d character array with list of companies
 * stk_price - 2d integer array with stock prices (rows: stock prices, columns: price for given company)
 * num_stk_prices - number of stock prices per company (rows)
 * 
 * Return: node pointer to linked list of average stock prices for the period
 */
struct node *find_top_performers(int num_comp, char company[][STK_NAME_LEN],
                     float stk_price[][NUM_COMPANIES], int num_stk_prices)
{
    struct node *root = NULL, *curr = NULL;

    for (int i = 0; i < num_comp; i++) {
        // Allocate and setup node
        curr = (struct node*)malloc(1 * sizeof(struct node));
        curr->next = NULL;
        strncpy(curr->name, company[i], STK_NAME_LEN);
        for (int j = 0; j < num_stk_prices; j++)
            curr->average += stk_price[j][i];
        curr->average = curr->average/num_stk_prices;

        root = insert_node(root, curr);
    }

   return root;
}

int main()
{

    struct node *top_performers, *llist;
    char companys[][STK_NAME_LEN] = {"AMZN", "CACC", "EQIX", "GOOG", "ORLY", "ULTA"};
    float stock_prices[NUM_STK_PRICES][NUM_COMPANIES] = {
        {12.81, 11.09, 12.11, 10.93, 9.83, 8.14},
        {10.34, 10.56, 10.14, 12.17, 13.1, 11.22},
        {11.53, 10.67, 10.42, 11.88, 11.77, 10.21}
    };

    top_performers = find_top_performers(NUM_COMPANIES, companys, stock_prices, NUM_STK_PRICES);
    llist = top_performers;

    fprintf(stderr, "Top Performing Companies Stocks:\n");
    for (int i = 0; i < NUM_COMPANIES; i++) {
        fprintf(stderr, "%s: $%f\n", top_performers->name, top_performers->average);
        top_performers = top_performers->next;
    }

    free(llist);
    return 0;

}