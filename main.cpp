#include <iostream>
#include<string>
using namespace std;

struct node {
    int value;
    struct node *rightChild;
    struct node *leftChild;
    int height;
    int count;
};

class AVLTree {
private:
    node *root;
public:
    AVLTree();
    void InsertElement(int key);
    pair<int*,int*> getChildrenNodesValues(int *key);
    int *getRootNode();
    string PreOrderTraversal();
    string PostOrderTraversal();
};

//initialize AVLTree
AVLTree::AVLTree(){
    root = NULL;
}

int *AVLTree::getRootNode() {
    return &root->value;
}

string printPreOrder(struct node *node, string s){
    if (node == NULL) {
        return s;
    }
    s += std::to_string(node->value) + " ";
    if (node->leftChild != NULL){
        s = printPreOrder(node->leftChild, s);
    }
    if (node->rightChild != NULL){
        s = printPreOrder(node->rightChild, s);
    }
    return s;
}

string AVLTree::PreOrderTraversal() {
    string s = "";
    return printPreOrder(root, s);
}

string printPostOrder(struct node *node, string s){
    if (node == NULL){
        return s;
    }

    if (node->leftChild != NULL){
        s = printPostOrder(node->leftChild, s);

    }
    if (node->rightChild != NULL){
        s = printPostOrder(node->rightChild, s);
    }
    s += std::to_string(node->value) + " ";
    return s;
}

string AVLTree::PostOrderTraversal(){
    string s = "";
    return printPostOrder(root, s);
}

int max (int h1, int h2){
    if (h1 > h2){
        return h1;
    } else {
        return h2;
    }
}

int nodeHeight (struct node *node){
    if (node == NULL){
        return 0;
    } else {
        return node->height;
    }
}

int nodeBF (struct node *node){
    if (node == NULL){
        return 0;
    } else {
        return nodeHeight(node->rightChild) - nodeHeight(node->leftChild);
    }
}

//        X									  Y
//      /	\								/   \
//    c1     Y         --->                X    c2
//	        /  \						 /  \
//		 subtree  c2                    c1  subtree
struct node *rotateLeft(struct node *x){
    struct node *y = x->rightChild;
    struct node *subtree = y->leftChild;

    x->rightChild = subtree;
    y->leftChild = x;

    x->height = 1 + max(nodeHeight(x->leftChild),nodeHeight(x->rightChild));
    y->height = 1 + max(nodeHeight(y->leftChild),nodeHeight(y->rightChild));

    return y;
}

//		   	 X                         Y
//		   /   \					 /   \
//		  Y    c2 		--->        c1	  X
//	    /   \							/   \
//    c1  subtree				   subtree   c2
struct node *rotateRight(struct node *x){
    struct node *y = x -> leftChild;
    struct node *subtree = y -> rightChild;

    x->leftChild = subtree;
    y->rightChild = x;

    x->height = 1 + max(nodeHeight(x->leftChild),nodeHeight(x->rightChild));
    y->height = 1 + max(nodeHeight(y->leftChild),nodeHeight(y->rightChild));

    return y;
}

struct node *createNode(struct node* node, int key){
    if (node == NULL){
        struct node *node = new struct node;
        node->value = key;
        node->leftChild = NULL;
        node->rightChild = NULL;
        node->height = 1;
        node->count = 0;
        return node;
    } else if (key > node->value){
        node->rightChild = createNode(node->rightChild, key);
    } else if (key < node->value){
        node->leftChild = createNode(node->leftChild, key);
    } else {
        node->count++;
        return node;
    }

    // update height for every node in recursion
    node->height = 1 + max(nodeHeight(node->leftChild), nodeHeight(node->rightChild));

    int balanceFactor = nodeBF(node);

    // 1) case when BF(node) = 2 and BF(node->rightChild) = 1
    // LEFT ROTATION
    if (balanceFactor == 2 && nodeBF(node->rightChild) == 1){
        return rotateLeft(node);
    }

    // 2) case when BF(node) = -2 and BF(node->leftChild) = -1
    // RIGHT ROTATION
    if (balanceFactor == -2 && nodeBF(node->leftChild) == -1){
        return rotateRight(node);
    }

    // 3) case when BF(node) = -2 and BF(node->leftChild) = 1ž
    // LEFT-RIGHT ROTATION
    if (balanceFactor == -2 && nodeBF(node->leftChild) == 1){
        node->leftChild = rotateLeft(node->leftChild);
        return rotateRight(node);
    }

    // 4) case when BF(node) = 2 and BF(node->rightChild) = -1
    // RIGHT-LEFT ROTATION
    if (balanceFactor == 2 && nodeBF(node->rightChild) == -1){
        node->rightChild = rotateRight(node->rightChild);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::InsertElement(int key) {
    if (root == NULL){
        root = new struct node;
        root->value = key;
        root->leftChild = NULL;
        root->rightChild = NULL;
        root->height = 1;
        return;
    } else {
        root = createNode(root, key);
    }
}

pair<int*,int*> AVLTree::getChildrenNodesValues(int *key){
    pair<int*,int*> result;
    struct node *node = root;
    while (node != NULL){
        if (*key > node->value){
            node = node->rightChild;
        } else if (*key < node->value){
            node = node->leftChild;
        } else if (*key == node->value){
            break;
        }
    }

    if (node->leftChild != NULL){
        result.first = &node->leftChild->value;
    }
    if (node->rightChild != NULL){
        result.second = &node->rightChild->value;
    }
    return result;
}

int main(){
    AVLTree avl = AVLTree();
    int *root = avl.getRootNode();
    avl.InsertElement(6);
    avl.InsertElement(51);
    avl.InsertElement(49);
    avl.InsertElement(71);
    avl.InsertElement(92);
    avl.InsertElement(59);
    avl.InsertElement(79);
    avl.InsertElement(89);
    avl.InsertElement(64);
    avl.InsertElement(88);
    avl.InsertElement(47);
    avl.InsertElement(82);

    cout << "Preorder: ";
    string a = avl.PreOrderTraversal();
    cout << a << "\n";
    cout << "Postorder: ";
    string b = avl.PostOrderTraversal();
    cout << b << "\n";
}

