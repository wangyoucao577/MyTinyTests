#include <iostream>
#include <stack>
using namespace std;

/* you only have to complete the function given below.  
 * Node is defined as  
 */
struct node
{
    int data;
    node* left;
    node* right;
};

void preOrder(node *root) {

    node *curr = root;

    stack<node*> st;
    node* pre = nullptr;
    
    while (curr){
            
        //if not printed before, print it
        if (pre != curr->left && pre != curr->right){
            cout << curr->data << " ";    
        }

        //if any child not entered before, try enter it
        if (curr->left && pre != curr->left && pre != curr->right){
            st.push(curr);
            pre = curr;
            curr = curr->left;
        }else if (curr->right && pre != curr->right){
            st.push(curr);
            pre = curr; 
            curr = curr->right;
        }else{
            if (st.empty()){
                curr = nullptr;
            }else{
                pre = curr;
                curr = st.top();
                st.pop();
            }
            
        }
    }
    
}

    
int main(){

    // I won't run this program in my own envrioment
    // So just leave main as empty
    // Run this preOrder function on hankerrank 
    return 0;
}
