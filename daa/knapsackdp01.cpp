#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int knapsack(int capacity, vector<int> &profit, vector<int> &weight, vector<int> &includedItems)
{
    int n = weight.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0)); //(n+1) is number of rows 
    // Fill dp table
    //i is no. of items, w is capacity
    for (int i = 1; i <= n; i++)
    {
        for (int w = 1; w <= capacity; w++)
        {
            if (weight[i - 1] <= w)
            {
                dp[i][w] = max(dp[i - 1][w], profit[i - 1] + dp[i - 1][w - weight[i - 1]]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w]; //carry over from previous row
            }
        }
    }
    // Track which items are included
    int w = capacity;
    for (int i = n; i > 0; i--)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            includedItems[i - 1] = 1;
            w -= weight[i - 1];
        }
        else
        {
            includedItems[i - 1] = 0;
        }
    }
    return dp[n][capacity]; // returns last item at bottom right
}
int main()
{

    // int capacity = 5;
    // vector<int> weight = {2, 3, 4, 5};
    // vector<int> profit = {3, 4, 5, 6};
    

    int n,capacity;

    cout<<"Enter the capacity of knapsack:";
    cin>>capacity;

    cout<<"Enter number of items:";
    cin>>n;

    vector<int> weight(n);
    vector<int> profit(n);

    for(int i=0;i<n;i++)
    {
        cout<<"Enter weight and value for item"<<i+1<<": ";
        cin>>weight[i]>>profit[i];
    }

    vector<int> includedItems(n, 0); //each element is set to zero
    int maxProfit = knapsack(capacity, profit, weight,includedItems);


    cout<<"Profit\tWeight"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout << profit[i] << "\t" << weight[i] << endl;
    }
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << includedItems[i] << " ";
    }
    cout << "\nOutput: " << maxProfit << endl;
    return 0;
}