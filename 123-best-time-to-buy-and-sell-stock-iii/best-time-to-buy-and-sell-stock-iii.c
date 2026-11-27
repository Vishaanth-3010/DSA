#include <limits.h>

static inline int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize <= 1) return 0;

    int buy1 = INT_MIN;
    int sell1 = 0;
    int buy2 = INT_MIN;
    int sell2 = 0;

    for (int i = 0; i < pricesSize; i++) {
        int price = prices[i];
        buy1  = max(buy1, -price);          // Best cash balance after 1st buy
        sell1 = max(sell1, buy1 + price);   // Best profit after 1st sell
        buy2  = max(buy2, sell1 - price);   // Best net balance after 2nd buy (reinvesting sell1)
        sell2 = max(sell2, buy2 + price);   // Best total profit after 2nd sell
    }

    return sell2;
}