#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


template<typename T>
class BinarySearchTree {
public:
    
     BinarySearchTree               (                              );
     BinarySearchTree               (const BinarySearchTree<T>& bst);
     BinarySearchTree<T>& operator= (const BinarySearchTree<T>& bst);
    ~BinarySearchTree               (                              );


    const T& search                 (const T& p_key                ) const;
    void     insert                 (const T& p_key                );
    void     remove                 (const T& p_key                );

    template<typename Tlam>
    void inOrder(Tlam&& lam);

    template<typename Tlam>
    void preOrder(Tlam&& lam);

    template<typename Tlam>
    void postOrder(Tlam&& lam);

private:

    enum class BinaryNodeColour {
        BLACK = 0,
        RED
    };

    struct BinaryNode {
        T data;
        BinaryNode *left,
                   *right;
        BinaryNodeColour color;
    };

    BinaryNode* m_root;
};


#endif