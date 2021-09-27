#include <memory>
#include <stack>
#include <algorithm>
#include <iostream> //TODO make function template or lambda for printing function
//binary search tree
namespace forest {
namespace avltree {
    template <typename key_t>
    class tree {

        struct node {

            key_t key;     ///< The key of the node
            //std::weak_ptr<node> parent;    ///< The parent of the node. weak_ptr can point to a data without holding an ownership
            std::shared_ptr<node> left;    ///< The left child of the node
            std::shared_ptr<node> right;   ///< The right child of the node
            int height;
            int balance;
            /**
             * @brief Copy Constructor of a binary search tree node
             */
            node(const key_t key) {
                this->key = key;
                // this->parent.reset(); //not sure about it
                this->left = nullptr;
                this->right = nullptr;
                this->balance = 0;
            }

            node& this_Node() {
                return *this;
            }
        };
    
    public:
    //TODO - subtrees rotation
    // share
        bool insert_root(key_t key) {         
            this->root = std::shared_ptr<node>(new node(key));       
        }
        //should we pass a reference to a root ptr during every insert?    
        bool insert(key_t key) {
            //we are having a root already. Maybe we need to make 
            //an arg after which node we shall insert
            std::shared_ptr<node> current = std::shared_ptr<node>(new node(key));
            int balance = getBalance(current);
            //while (balance != 0) { // change condition
                path_stack.push(current);
                /* 2. Update height of this ancestor node */
                // check if tree is balanced?
                 //balance will be always 0  for now
                current->balance = balance;
                if (current->key < root->key)
                {
                    std::cout << "turn left" << std::endl;
                    std::cout << "Tree Balance is: " << balance << std::endl;
                    // If this node becomes unbalanced, then
                    // there are 4 cases
                    // Left Left Case
                    //   
                    if (balance > 1 && key < current->left->key) {
                        //left child of current node is empty at first iteration
                        //so we rotate current's parent node to a current's left child position
                        ll_rotation(current);
                        //check balance and if it is 0 then return true
                        if (balance == 0) return true; 
                    } 
                }
                else if (current->key > root->key) 
                {
                    std::cout << "turn right";
                    //turn right and rotate subtree
                    // current->right = insert(node->right, key); 
                }
                else 
                    return false;     
            //}
            // while (current != nullptr)
            // {
            //     parent = current;//?
            //     if (key > current->key) {
            //         current = current->right;                     
            //     } else if (key < current->key) {
            //         current = current->left;
            //     } else {
            //         return false;
            //     }               
            // }
            // current = std::make_shared<node>(key); //create a temp pointer for a current
            // current->parent = parent;
            // if(parent == nullptr) {
            //     root = current;
            // } else if (current->key > parent->key) {
            //     parent->right = current;
            // } else if (current->key < parent->key) {
            //     parent->left = current;
            // }
        }

        std::unique_ptr<node> find(key_t key) {
            std::unique_ptr<node> x = root;
            while (x != nullptr)
            {
                if (key > x->key) {
                    x = x->right;
                } else if (key < x->key) {
                    x = x->left;
                } else {
                    return x;
                }                
            }
            //return false;
        }

        bool remove(key_t key) {
            std::shared_ptr<node> parent = root; //point to a root node
            std::shared_ptr<node> x = root; //node to delete
            while (x != nullptr && x->key != key)
            {
                parent = x;
                if (key > x->key) {                    
                    //parent->right = x; // move through a right side of a tree 
                    x = x->right;      // currently it is nullptr               
                    //found node to delete ?                    
                } else if (key < x->key) {
                    parent = x;
                    x = x->left;                   
                } else {
                    //root is detected

                }
            }
                //we found our Node with key to remove
                // check if we have children of node to delete
                // parent = x;
            if (x->left == nullptr || x->right == nullptr) {
                std::shared_ptr<node> child;
                if (x->left == nullptr)
                    child = x->right;
                else 
                    child = x->left;

                // check if the node to
                // be deleted is the root.    
                //if (parent == nullptr) 
                if (x == parent->left)
                    parent->left = child;
                else
                    parent->right = child;
                x = nullptr;
            }
            else {
                //we have both child nodes
                std::shared_ptr<node> temp;
                // Compute the inorder successor
                temp = x->right;
                while (temp->left != nullptr) {
                    parent = temp;
                    temp = temp->left;
                }
                }
        }
        //inorder traversal
        void traverse() {
            std::stack< std::shared_ptr<node> > s;
            std::shared_ptr<node> current = root;
            while (current != nullptr || !s.empty()) {
                while (current != nullptr){
                /* Reach the left most Node of the
                    curr Node */
                    s.push(current);
                    current = current->left;                    
                }
                  /* Current must be NULL at this point */
                current = s.top();
                s.pop();
                std::cout << "key = " << current->key << std::endl;
                current = current->right;
            }            
        }



        int height (std::shared_ptr<node> nd) {
            if (nd == nullptr)
                return 0;
            return nd->height;
        }
        //TODO - remove
        int getBalance(std::shared_ptr<node> nd) {
            return height(nd->left) -
                    height(nd->right);
        }

    private:
        std::shared_ptr<node> root; // how to init root with values ?
        std::stack< std::shared_ptr<node> > path_stack;
        //we can move here a node which we want to rotate

        /* In LL Rotation, every node moves one position 
           to left from the current position */
           //it seems it should make increment of balance until zero
        std::shared_ptr<node> ll_rotation(std::shared_ptr<node> p) 
        {
            std::shared_ptr<node> tempNode = p; // tempNode is a location for rotating node
	        p = tempNode->left; // 3
	        tempNode->left = p->right;
	        p->right = tempNode;
	        //tempNode->balance = -(p->balance); // -1
            /*
             * optional: do a getBalance() here and check if it became zero
             */
        }

        std::shared_ptr<node> rr_rotation(std::shared_ptr<node> p) 
        {
            std::shared_ptr<node> tempNode = p;
	        p = tempNode->right;
	        tempNode->right = p->left;
	        p->left = tempNode;
	        // tempNode->balance = //-(++(p.unique())->balance); // -1
        }
        
        // std::shared_ptr<node> right_rotation(std::shared_ptr<node> p)
        // {
        //     //AVLNode* new_p = p->left_node_;
        //     std::shared_ptr<node> new_p = p->left_node_;
        //     p->left_node_ = new_p->right_node_;
        //     new_p->right_node_ = p;

        //     p->height_ = max(sub_tree_height(p->left_node_), sub_tree_height(p->right_node_));
        //     new_p->height_ = max(sub_tree_height(new_p->left_node_), sub_tree_height(new_p->right_node_));

        //     return new_p;
        // }
        // //we can move here a node which we want to rotate
        // std::unique_ptr<node> left_rotation(std::unique_ptr<node>  p)
        // {
        //     std::unique_ptr<node> new_p = p->right_node_;
        //     p->right_node_ = new_p->left_node_;
        //     new_p->left_node_ = p;

        //     p->height_ = max(sub_tree_height(p->left_node_), sub_tree_height(p->right_node_));
        //     new_p->height_ = max(sub_tree_height(new_p->left_node_), sub_tree_height(new_p->right_node_));

        //     return new_p;
        // }
    };
}
}