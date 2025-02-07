# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        def carry_check(p):
            if p.val / 10 >=1:
                carry = 1
                p.val = p.val % 10
            else:
                carry = 0
            return carry
        
        result_list = ListNode()
        p = result_list
        carry = 0
        while l1 is not None and l2 is not None:
            p.val = l1.val + l2.val + carry
            carry = carry_check(p)
            l1 = l1.next
            l2 = l2.next
            if l1 or l2:
                p.next = ListNode()
                p = p.next
        while l1 is not None:
            p.val = l1.val + carry
            carry = carry_check(p)
            l1 = l1.next
            if l1:
                p.next = ListNode()
                p = p.next
        while l2 is not None:
            p.val = l2.val + carry
            carry = carry_check(p)
            l2 = l2.next
            if l2:
                p.next = ListNode()
                p = p.next
        if carry:
            p.next = ListNode(1)
            p = p.next
        return result_list
            
