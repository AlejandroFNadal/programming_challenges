#include <iostream>
#include <cassert>

using namespace std;

class Node{
    public:
        int data;
        Node* next;
    Node(int data){
        this->data = data;
        this->next = NULL;
    }
    bool detectCycle(){
        Node* slow = this;
        Node* fast = this;
        int i = 0;
        if(this->next == this){
            return true;
        }
        while(slow->next != NULL && fast->next != NULL && fast->next->next != NULL){
            slow =  slow->next;
            fast = fast->next->next;
            cout << "slow: "<< slow->data << " fast " << fast->data << endl;
            if(slow == fast){
                break;
            }
            i++;
        }
        if(slow == fast && i != 0){
            return true;
        }else{
            return false;
        }
    }
};

int main()
{
    
    Node head(1);
    Node second(2);
    Node third(3);
    Node fourth(4);
    head.next = &second;
    second.next = &third;
    third.next = &fourth;
    fourth.next = &second;
    assert(head.detectCycle() == true);
    return 0;
}
