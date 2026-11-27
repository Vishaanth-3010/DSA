int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int totalTank = 0;
    int currTank = 0;
    int startIndex = 0;

    for (int i = 0; i < gasSize; i++) {
        int net = gas[i] - cost[i];
        totalTank += net;
        currTank += net;

        // If tank goes negative at station i, no station in [startIndex..i] can reach i + 1
        if (currTank < 0) {
            startIndex = i + 1;
            currTank = 0;
        }
    }

    return (totalTank >= 0) ? startIndex : -1;
}