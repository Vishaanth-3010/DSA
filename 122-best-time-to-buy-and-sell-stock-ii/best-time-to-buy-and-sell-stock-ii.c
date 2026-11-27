int maxProfit(int* prices, int pricesSize) {
    if (pricesSize <= 1) return 0;

    int totalProfit = 0;

    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] > prices[i - 1]) {
            totalProfit += prices[i] - prices[i - 1];
        }
    }

    return totalProfit;
}