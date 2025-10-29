class Solution:
    def hIndex(self, citations: List[int]) -> int:
        # I have to search for the biggest number which is yet smaller than the length of the array
        citation_tracker = [0] * 5000
        for cit in citations:
            for i in range(1, cit +1):
                citation_tracker[i]+=1
        max = 0
        for i in range(1, len(citation_tracker)):
            if citation_tracker[i] == 0:
                break
            if citation_tracker[i] >= i:
                if i > max:
                    max = i
        return max
        
