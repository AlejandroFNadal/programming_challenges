#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;


class State{
    public:
        
};
class Solution{
    private:
        vector<string> test = {
            "/test",  "/home/./test","//test", "/test//sth", "//test/////sth", "/./", "/home/../test", "/../", "//../home/./../test//"
        };
        vector<string> test_res = {
            "/test", "/home/test", "/test", "/test/sth", "/test/sth", "/", "/test", "/", "/test"
        };
        string invert_string(string a){
            string b = "";
            for(auto it = a.rbegin(); it < a.rend(); it ++){
                b+= *it;
            }
            return b;
        }

    public:
        bool test_all(){
            for(auto it = test.begin(), it2 = test_res.begin(); it <  test.end(); it++, it2++){
                string response = simplifyPath(*it);
                cout << "Test input: " << *it << " Response: "<< response << endl;
                if(response != *it2){
                    return false;
                }
            }
            return true;
        }
        string simplifyPath(string path){
            stack<string> parser_stack;
            string canonical_path = "";
            string temp = "";
            auto it = path.begin();
            while(it < path.end()){
                //skip slashes whenever found
                while(*it == '/' && it < path.end()){
                    it++;
                }
                // process text
                while(*it != '/' && it < path.end()){
                    temp += *it;
                    it++;
                }
                if(temp == ".."){
                    if(parser_stack.size()>0){
                        parser_stack.pop(); 
                    }
                    temp="";
                } else if(temp == "."){
                    temp = "";
               }else if(temp.size() > 0) {
                    parser_stack.push(temp);
                    temp = "";
                }
                    
            }
            stack<string> inverse_stack;
            while(parser_stack.size() > 0){
                inverse_stack.push(parser_stack.top());
                parser_stack.pop();
            }
            canonical_path +="/";
            while(inverse_stack.size() >0){
                canonical_path += inverse_stack.top();
                canonical_path +="/";
                inverse_stack.pop();
            }
            if(canonical_path.size() > 1){
                canonical_path.resize(canonical_path.size()-1);
            }
            return canonical_path;
        };
};
int main(){
    Solution sol_obj;
    cout << sol_obj.test_all() << endl;
    return 0;
}
