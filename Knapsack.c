#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_CAPACITY 1000

/* Display DP table */
void displayTable(int dp[][MAX_CAPACITY + 1], int rows, int W)
{
    int i, w;

    printf("\nDP TABLE\n");

    printf("i/W |");
    for (w = 0; w <= W; w++)
    {
        printf("%4d", w);
    }

    printf("\n----+");
    for (w = 0; w <= W; w++)
    {
        printf("----");
    }

    printf("\n");

    for (i = 0; i <= rows; i++)
    {
        printf("%3d |", i);

        for (w = 0; w <= W; w++)
        {
            printf("%4d", dp[i][w]);
        }

        printf("\n");
    }
}

/* 0/1 Knapsack Dynamic Programming */
int knapsack(int n, int W, int weight[], int value[])
{
    static int dp[MAX_ITEMS + 1][MAX_CAPACITY + 1];

    int i, w;
    int include, exclude;

    /* Initialize DP table with 0 */
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            dp[i][w] = 0;
        }
    }

    printf("\nInitial DP Table:\n");
    displayTable(dp, 0, W);

    /* Build DP table */
    for (i = 1; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            /* If current item can fit */
            if (weight[i - 1] <= w)
            {
                include =
                    value[i - 1] +
                    dp[i - 1][w - weight[i - 1]];

                exclude =
                    dp[i - 1][w];

                if (include > exclude)
                {
                    dp[i][w] = include;
                }
                else
                {
                    dp[i][w] = exclude;
                }
            }
            else
            {
                /* Item cannot fit */
                dp[i][w] = dp[i - 1][w];
            }
        }

        printf("\n========================================\n");
        printf("After adding Item %d\n", i);
        printf("Weight = %d, Value = %d\n",
               weight[i - 1],
               value[i - 1]);
        printf("========================================\n");

        displayTable(dp, i, W);
    }

    return dp[n][W];
}

int main()
{
    FILE *input;
    FILE *output;

    char line[200];

    int n, W;
    int weight[MAX_ITEMS];
    int value[MAX_ITEMS];

    int testCase = 0;
    int result;
    int i;

    /*
       input.txt MUST be in the same folder
       from which the program is executed.
    */
    input = fopen("input.txt", "r");

    if (input == NULL)
    {
        printf("ERROR: Cannot open input.txt\n");
        printf("Make sure input.txt is in the Knapsack folder.\n");
        return 1;
    }

    /* Create result.txt */
    output = fopen("result.txt", "w");

    if (output == NULL)
    {
        printf("ERROR: Cannot create result.txt\n");
        fclose(input);
        return 1;
    }

    /* Read file line by line */
    while (fgets(line, sizeof(line), input) != NULL)
    {
        /* Check if line starts with #Test */
        if (strncmp(line, "#Test", 5) == 0)
        {
            testCase++;

            /* Read n and W */
            if (fscanf(input, "%d %d", &n, &W) != 2)
            {
                printf("Error reading n and W for Test %d\n",
                       testCase);
                break;
            }

            /* Check limits */
            if (n > MAX_ITEMS || W > MAX_CAPACITY)
            {
                printf("Test %d exceeds program limits.\n",
                       testCase);
                break;
            }

            /* Read weights and values */
            for (i = 0; i < n; i++)
            {
                if (fscanf(input,
                           "%d %d",
                           &weight[i],
                           &value[i]) != 2)
                {
                    printf("Error reading item %d\n", i + 1);

                    fclose(input);
                    fclose(output);

                    return 1;
                }
            }

            printf("\n\n");
            printf("========================================\n");
            printf("             TEST CASE %d\n", testCase);
            printf("========================================\n");

            printf("Number of Items (n) = %d\n", n);
            printf("Capacity (W)         = %d\n", W);

            printf("\nItems:\n");
            printf("--------------------------\n");
            printf("Item\tWeight\tValue\n");
            printf("--------------------------\n");

            for (i = 0; i < n; i++)
            {
                printf("%d\t%d\t%d\n",
                       i + 1,
                       weight[i],
                       value[i]);
            }

            printf("--------------------------\n");

            /* Solve Knapsack */
            result = knapsack(
                n,
                W,
                weight,
                value);

            printf("\n----------------------------------------\n");
            printf("Maximum Total Value = %d\n", result);
            printf("----------------------------------------\n");

            /* Store answer in result.txt */
            fprintf(
                output,
                "#Test %d input (%d %d) %d\n",
                testCase,
                n,
                W,
                result);
        }
    }

    fclose(input);
    fclose(output);

    printf("\n\n========================================\n");
    printf("ALL TEST CASES COMPLETED\n");
    printf("Results saved in result.txt\n");
    printf("========================================\n");

    return 0;
}