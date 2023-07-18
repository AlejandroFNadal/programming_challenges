#include <iostream>
#include <cassert>
#include <stack>
#include <string>

bool isValid(std::string s){
    std::stack<char> parser_stack;
    for(auto it = s.begin(); it < s.end(); it++){
        if(*it == '{' || *it == '[' || *it == '('){
            parser_stack.push(*it);
        } else if (*it == '}'){
            if(parser_stack.size() == 0 || parser_stack.top() != '{'){
                return false;
            } else{
                parser_stack.pop();
            }
        } else if(*it == ']'){
            if(parser_stack.size() == 0 || parser_stack.top() != '['){
                return false;
            } else {
                parser_stack.pop();
            }
        } else if(*it == ')'){
            if(parser_stack.size() == 0 || parser_stack.top() != '('){
                return false;
            } else{
                parser_stack.pop();
            }
        }
    }
    if(parser_stack.size() == 0){
        return true;
    }else{
        return false;
    }
}
int main(){
    std::string test1 = "{[()]}";
    std::string test2 = "{(})";
    std::string test3 = "[";
    assert(true == isValid(test1));
    assert(false == isValid(test2));
    assert(false == isValid(test3));
    return 0;
}
