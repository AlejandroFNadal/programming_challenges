class Solution:
    def hIndex(self, citations: List[int]) -> int:
        # I have to search for the biggest number which is yet smaller than the length of the array
        citations.sort(reverse=True)
        maxval = 0
        if len(citations) == 1:
            if citations[0] > 0:
                return 1
            else:
                return 0
        for i in range(0, len(citations)):
            # i is the amount of papers I have
            # citations[i] are papers with that amount of citations already
            # the biggest, of the smallest of both numers, wins
            minval = min(citations[i],i +1)
            if minval > maxval:
                maxval = minval
        return maxval
        
