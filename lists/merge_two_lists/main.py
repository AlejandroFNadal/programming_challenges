class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        res = ListNode()
        original = res
        if list1 is None and list2 is None:
            return None
        while list1 != None or list2 != None:
            if list1 is not None and (list2 is None or list1.val <= list2.val):
                res.val = list1.val
                list1 = list1.next
            else:
                res.val = list2.val
                list2 = list2.next
            if list1 or list2:
                res.next = ListNode()
                res = res.next
        return original
