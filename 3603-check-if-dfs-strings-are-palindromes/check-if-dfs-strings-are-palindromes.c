#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool* findAnswer(int* parent, int parentSize, char* s, int* returnSize) {
    int n = parentSize;
    *returnSize = n;

  
    int* head = (int*)malloc(n * sizeof(int));
    int* next = (int*)malloc(n * sizeof(int));
    memset(head, -1, n * sizeof(int));

    for (int i = n - 1; i >= 1; i--) {
        int p = parent[i];
        next[i] = head[p];
        head[p] = i;
    }


    char* dfsStr = (char*)malloc((n + 1) * sizeof(char));
    int* in = (int*)malloc(n * sizeof(int));
    int* out = (int*)malloc(n * sizeof(int));

    int* stackNode = (int*)malloc(n * sizeof(int));
    int* stackEdge = (int*)malloc(n * sizeof(int));
    int top = 0, timer = 0;

    stackNode[top] = 0;
    stackEdge[top] = head[0];
    in[0] = 0;

    while (top >= 0) {
        int u = stackNode[top];
        int e = stackEdge[top];

        if (e != -1) {
            stackEdge[top] = next[e];
            top++;
            stackNode[top] = e;
            stackEdge[top] = head[e];
            in[e] = timer;
        } else {
            dfsStr[timer] = s[u];
            out[u] = timer;
            timer++;
            top--;
        }
    }
    dfsStr[n] = '\0';

  
    int m = 2 * n + 3;
    char* t = (char*)malloc(m * sizeof(char));
    int* p = (int*)calloc(m, sizeof(int));

    t[0] = '^';
    t[1] = '#';
    for (int i = 0; i < n; i++) {
        t[2 * i + 2] = dfsStr[i];
        t[2 * i + 3] = '#';
    }
    t[m - 1] = '$';

    int center = 0, right = 0;
    for (int i = 1; i < m - 1; i++) {
        int mirror = 2 * center - i;
        if (i < right) {
            int rem = right - i;
            p[i] = p[mirror] < rem ? p[mirror] : rem;
        }
        while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) {
            p[i]++;
        }
        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }

    bool* ans = (bool*)malloc(n * sizeof(bool));
    for (int i = 0; i < n; i++) {
        int l = in[i], r = out[i];
        ans[i] = p[l + r + 2] >= (r - l + 1);
    }

    free(head);
    free(next);
    free(dfsStr);
    free(in);
    free(out);
    free(stackNode);
    free(stackEdge);
    free(t);
    free(p);

    return ans;
}