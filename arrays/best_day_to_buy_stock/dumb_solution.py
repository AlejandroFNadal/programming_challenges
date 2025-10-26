# Way too slow
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        max_profit = 0    
        i = 0
        j = 1
        while i < len(prices):
            while j < len(prices):
                diff = prices[j] - prices[i]
                if diff > max_profit:
                    max_profit = diff
                j+=1
            i+=1
            j=i+1
        return max_profit
