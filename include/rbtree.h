#include <memory>
#include <stack>
#include <algorithm>
#include <iostream> //TODO make function template or lambda for printing function
//red search tree
namespace forest {
namespace rbtree {
    template <typename key_t>
    class tree {

        struct node {

            key_t key;     ///< The key of the node
            enum { red, black } color;
            std::weak_ptr<node> parent;    ///< The parent of the node
            std::shared_ptr<node> left;    ///< The left child of the node
            std::shared_ptr<node> right;   ///< The right child of the node
            /**
             * @brief Constructor of a red black tree node
             */
            node(const key_t key) {
                this->key = key;
                //this->color = node::color::black;
                this->left = nullptr;
                this->right = nullptr;
            }
        };
    
    public:
        //insertion with balancing
        bool insert_root(key_t key)
        {
            if (this->root != nullptr) {
                this->root = std::shared_ptr<node>(new node(key));
                this->root->color = node::color::black;
            }                            
            return true;
        }

        bool insert(key_t key) {
            std::shared_ptr<node> current = std::shared_ptr<node>(new node(key)); //= root; //new node is always red by default            
            current->color = node::color::red;

            std::shared_ptr<node> parent = nullptr;
            std::shared_ptr<node> uncle;
            std::shared_ptr<node> sibling;
            //current->parent = nullptr for root
            //resolving here all cases
            //rebalancing
            while (current->parent->color == node::color::red) {
                //how to mark all cases better ?
                if (current->parent == current->parent->parent->right) {
                    // uncle
                    if (uncle->color == node::color::red)
                    {
                        
                    }
                }
            }
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
            current = std::make_shared<node>(key); //create a temp pointer for a current
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
            return false;
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

        void rotateLeft(std::unique_ptr<node> root, std::shared_ptr<node> pt) {
            node *pt_right = pt->right;
            //std::copy();

            pt->right = pt_right->left;
  
            if (pt->right != NULL)
                pt->right->parent = pt;
        
            pt_right->parent = pt->parent;
        
            if (pt->parent == NULL)
                root = pt_right;
        
            else if (pt == pt->parent->left)
                pt->parent->left = pt_right;
        
            else
                pt->parent->right = pt_right;
        
            pt_right->left = pt;
            pt->parent = pt_right;
        }

        void rotateRight() {
            
        }


    private:
        std::shared_ptr<node> root;
        std::stack<node> tree_stack;
    };
}
}