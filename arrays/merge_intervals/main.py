def merge(intervals):
        """
        :type intervals: List[List[int]]
        :rtype: List[List[int]]
        """
        # Intervals can partially or totally overlap. For total overlaps, the smaller intervals just 
        # gets removed. Partial overlap is, given intA and intB, 
        # A.s < B.s and A.e < B.e OR A.s > B.s and A.e < B.e. The list is not sorted, 
        # so I have to check all of the intervals. It is N^2
        # I could also try sorting the list by the first element and then iterating forward until there are no
        # overlaps. That would give me sth like N + N*logn
        intervals.sort(key= lambda first : first[0])
        cur_int = 0
        possible_overlap_pos = 1
        while possible_overlap_pos < len(intervals): # takes care of len 1 array
            # overlap check
            cur = intervals[cur_int]
            while possible_overlap_pos < len(intervals) and cur[1] >= intervals[possible_overlap_pos][0]: # some sort of overlap exists
                check = intervals[possible_overlap_pos]
                if check[1] <= cur[1]: # total overlap, delete
                    intervals.pop(possible_overlap_pos)
                if cur[1] < check[1]: # partial overlap, merge
                    cur[1] = check[1]
                    intervals.pop(possible_overlap_pos)
            cur_int += 1
            possible_overlap_pos +=1
        return intervals

t1 = [[1,3],[2,6],[8,10],[15,18]]  

assert merge(t1) == [[1,6],[8,10],[15,18]]
 
