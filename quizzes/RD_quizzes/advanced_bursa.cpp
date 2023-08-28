#include <bits/stdc++.h>
using namespace std;
 
long long maximumProfit(vector<int>& v, int n)
{
    vector<vector<long long> > dp(v.size() + 1,
                                  vector<long long>(3));
    dp[0][0] = -v[0];
    for (int i = 1; i <= n; i++)
    {
        // Maximum of buy state profit till previous day or
        // buying a new stock with cooldown state of previous day
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][2] - v[i]);
        // Maximum of sold state profit till previous day or
        // selling the stock on current day with buy state of previous day
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + v[i]);
          // Sold state of previous day
        dp[i][2] = dp[i - 1][1];
    }
      // return Sold state profit of final day
    return dp[n - 1][1];          
}
 
int main()
{
    vector<int> prices = {1, 2, 3, 0, 2};
    vector<int> prices2 = {2, 6, 2, 6};
    vector<int> prices3 = {8, 2, 6, 2, 6, 3, 7};

    cout << maximumProfit(prices, prices.size()) << endl;
    cout << maximumProfit(prices2, prices2.size()) << endl;
    cout << maximumProfit(prices3, prices3.size()) << endl;

    return 0;
} 