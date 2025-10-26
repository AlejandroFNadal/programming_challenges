class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        max_profit = 0    
        selling_price = prices[-1]
        i = len(prices) - 2
        while i >= 0 and len(prices) >= 2:
            # we update the value first
            if selling_price < prices[i]:
                selling_price = prices[i]
            if selling_price - prices[i] > max_profit:
                max_profit = selling_price - prices[i]
            i = i - 1
        return max_profit
