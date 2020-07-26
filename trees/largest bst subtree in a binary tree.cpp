// the idea is simple just store the values in the sequence (left-root-right) and return them as a vector 
// put them inside a map and check for the largest size

/* Tree node structure  used in the program

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};*/

vector<int> preorder(Node *root, map<vector<int>, int> &m){
    if(root){
        
        // it will give me the sequence for the left tree and for the right tree in some order
        vector<int> l = preorder(root->left, m);
        vector<int> r = preorder(root->right, m);
        
        // if both the vectors's size are zero that means we have the current node as leaf node so we will return only this particular node
        if(l.size()==0 && r.size()==0){
            l.push_back(root->data);
            return l;
        } 
        
        // if any one of the vector is empty then we will check for the condition
        // if other vector's first element is -1 or not which means that it can't form bst for the rest of it parent nodes
        // if its not -1 then we will check for the sorted conditon which is if left is empty then root->data must be smaller than right sequence first element
        // if right is emepty then root->data must be greater than left sequence last element 
        // if the condition is true then we will push the root->data according and mark its presence inside our map and return that particular vector
        // if the condition fails then we will push -1 inside the vector and return that vector
        else if(l.size()==0){
            if(r[0]!=-1){
                if(root->data < r[0]){
                    r.insert(r.begin(), root->data);
                    m[r]=1;
                } else{
                    r.insert(r.begin(), -1);
                }
            }
            return r;
            
        } else if(r.size()==0){
            if(l[0]!=-1){
                if(root->data > l[l.size()-1]){
                    l.push_back(root->data);
                    m[l]=1;
                } else{
                    l.insert(l.begin(), -1);
                }
            }
            return l;
        } else{
            if(r[0]==-1){
                return r;
            } else if(l[0]==-1){
                return l;
            } else{
                if(l[l.size()-1] < root->data && root->data < r[0]){
                    l.push_back(root->data);
                    r.insert(r.begin(), l.begin(), l.end());
                    m[r]=1;
                    return r;
                }
                r.insert(r.begin(), -1);
                return r;
            }
        }
    }
    return {};
}

/*You are required to complete this method */
// Return the size of the largest sub-tree which is also a BST
int largestBst(Node *root){
    
    map< vector<int>, int> m;
    preorder(root, m);
    
    // here we find the largest size vector which will be our answer
    int ma=1;
    for(auto i:m){
        int a = i.first.size();
        ma = max(a, ma);
    }
    return ma;
}
