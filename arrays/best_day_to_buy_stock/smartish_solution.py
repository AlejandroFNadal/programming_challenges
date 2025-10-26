# I felt smart with this one, but still not fast enough.
# The idea here is to keep only the peaks in the data
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        max_profit = 0    
        peaks_array = []
        i = 0
        while i < len(prices):
            peaks_array.append(prices[i])
            downtrend = False
            while (i+1) < len(prices) and prices[i] > prices[i + 1]:
                # downtrend: we are not interested in these values
                downtrend = True
                i = i + 1
            if downtrend:
                peaks_array.append(prices[i])
            # end of downtrend: might have been an uptrend: 
            uptrend = False
            if downtrend == False:
                while (i+1) < len(prices) and prices[i] < prices[i + 1]:
                    uptrend=True
                    i = i + 1
            if uptrend:
                peaks_array.append(prices[i])
            # if no up or down, we are in a plateau
            i = i + 1
        i = 0
        j = 1
        while i < len(peaks_array):
            while j < len(peaks_array):
                diff = peaks_array[j] - peaks_array[i]
                if diff > max_profit:
                    max_profit = diff
                j+=1
            i+=1
            j=i+1
        return max_profit

