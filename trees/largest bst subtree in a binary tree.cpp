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
        vector<int> l = preorder(root->left, m);
        vector<int> r = preorder(root->right, m);
        
        if(l.size()==0 && r.size()==0){
            l.push_back(root->data);
            return l;
        } else if(l.size()==0){
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
    int ma=1;
    for(auto i:m){
        int a = i.first.size();
        ma = max(a, ma);
    }
    return ma;
}
