#pragma once
#include <iostream>
using namespace std;

enum class Color
{
    Red, Black
};

template <typename V, typename K>
class RBTree
{
protected:
    struct Node
    {
        Node ();//
        Node(const V&, const K&, Node* nright = 0,
             Node* nleft = 0, Node* par = 0, Color col = Color::Black);//
        ~Node();//
        
        V value;
        K key;
        Node* left;
        Node* right;
        Node* parent;
        Color color;
        
        Node* grandpa();//
        Node* uncle();//
        Node* sibling();//
        //перегрузила для констр копирования
        Node* operator=(const Node* copyNode);
        string getNodeColor();//получение цвета ноды
    };
    
public:
    RBTree();//
    RBTree(const RBTree &copy);//
    ~RBTree();//
    
    
    void addNode(V value, K key);//добавить узел
    
    void removeFirstNode(K key);//удаление первой ноды по ключу
    void removeNodesByKey(K key);//удаление всех узлов с таким ключом
    
    V findNodeByKey(K key);//найти ноду по ключу
    V findMaxKey();//
    V findMinKey();//
    
    size_t size();//
    bool isEmpty();//
    
    
    void printTree();//вывести дерево на экран
    
private:
    Node* _root;
    size_t _size;
    
    void addBalance(Node* nd);//баланс при вставке написан
    void first_add_case(Node* nd);
    void second_add_case(Node* nd);
    void third_add_case(Node* nd);
    void fourth_add_case(Node* nd);
    
    void removeBalance(Node *nd);//ужасная балансировка при удалении
    void first_delete_case(Node *nd);
    void second_delete_case(Node *nd);
    void third_delete_case(Node *nd);
    void fourth_delete_case(Node *nd);
    void fifth_delete_case(Node *nd);
    void sixth_delete_case(Node *nd);
    
    void leftRotate(Node *node);//покрутить дерево
    void rightRotate(Node *node);//тоже покрутить
    
    //не хотелось бы чтобы пользователь видел что
    //такая гадость имеет место быть...
    void removeNode(Node* nd);//рекурсия просто для удаления
    void printTree(Node *nd, int level);//рекурсия для вывода дерева
    void removeTree(Node* nd);//рекурсия для деструктора
    void constructTree(Node* nd, Node *cp);//рекурсия для констр копирования
    void removeFirstNode(K key, Node *nd);//рекурсия для удаления первой ноды с ключом key
    V findNodeByKey(K key, Node *nd);//рекурсия для поиска ноды
};

template <typename V, typename K>
RBTree<V, K>::Node::Node()
    :left(0), right(0), parent(0) {}

template <typename V, typename K>
RBTree<V, K>::Node::Node(const V& val, const K& k, Node* nright,
                         Node* nleft, Node* par, Color col)
    :value(val),key(k),right(nright),left(nleft),parent(par),color(col) {}

template <typename V, typename K>
typename RBTree<V, K>::Node::Node* RBTree<V,K>::Node::operator=(const Node* copy)
{
    if (this == copy)
        return this;
    if (copy == 0)
        return 0;
    value = copy->value;
    key = copy->key;
    left = copy->left;
    right = copy->right;
    color = copy->color;
    parent = copy->parent;
    return this;
}

template <typename V, typename K>
RBTree<V, K>::Node::~Node() {}

template <typename V, typename K>
RBTree<V, K>::RBTree()
    :_root(0),_size(0) {}


template <typename V, typename K>
RBTree<V, K>::RBTree(const RBTree& copy)
{
    _size = copy._size;
    if (copy._root == 0)
    {
        _root = 0;
        return;
    }
    _root = new Node(copy._root->value, copy._root->key, copy._root->right,
                     copy._root->left,copy._root->parent,copy._root->color);
    constructTree(_root, copy._root);
}

template<typename V, typename K>
void RBTree<V,K>::constructTree(Node* node, Node* copy)
{
    if (copy)
    {
        node = copy;
        if (copy->left != 0)
        {
            constructTree(node->left, copy->left);
        }
        if (copy->right != 0)
        {
            constructTree(node->right, copy->right);
        }
    }
}

template <typename V, typename K>
RBTree<V, K>::~RBTree()
{
    removeTree(_root);
}

template<typename V, typename K>
void RBTree<V,K>::removeTree(Node* node)
{
    if (node)
    {
        if (node->left)
            removeTree(node->left);
        if (node->right)
            removeTree(node->right);
        delete node;
    }
}

template <typename V, typename K>
typename RBTree<V, K>::Node* RBTree<V, K>::Node::grandpa()
{
    if (this == nullptr || this->parent == nullptr)
        return nullptr;
    return this->parent->parent;
}

template <typename V, typename K>
typename RBTree<V, K>::Node* RBTree<V, K>::Node::uncle()
{
    if (this->grandpa() == nullptr)
        return nullptr;
    if (this->parent == grandpa()->right)
        return grandpa()->left;
    else
        return grandpa()->right;
}

template <typename V, typename K>
typename RBTree<V, K>::Node* RBTree<V, K>::Node::sibling()
{
    if (this == this->parent->left)
        return this->parent->right;
    else
        return this->parent->left;
}

template <typename V, typename K>
void RBTree<V,K>::addNode(V value, K key)
{
    if (this->isEmpty() == true)
    {
        _root = new Node(value, key);
        _size++;
        return;
    }
    else
    {
        _size++;
        Node *node = _root;
        for (int k = 0; k != -1; k++)
        {
            if (key < node->key)
            {
                if (node->left == nullptr)
                {
                    node->left = new Node(value, key, 0, 0, node, Color::Red);
                    addBalance(node->left);
                    //_size++;
                    return;
                }
                else
                {
                    node = node->left;
                }
            }
            else if (key >= node->key)
            {
                if (node->right == 0)
                {
                    node->right = new Node(value, key, 0, 0, node, Color::Red);
                    addBalance(node->right);
                    // _size++;
                    return;
                }
                else
                {
                    node = node->right;
                }
            }
        }
    }
}

template <typename V, typename K>
void RBTree<V,K>::addBalance(Node* node)
{
    // _size++;
    if (node == _root)
    {
        _root->color = Color::Black;
        return;
    }
    
    else
        first_add_case(node);
}

template <typename V, typename K>
void RBTree<V,K>::first_add_case(Node* node)
{
    if (node->parent->color == Color::Red)
    {
        second_add_case(node);
    }
    else
        return;
}

template <typename V, typename K>
void RBTree<V,K>::second_add_case(Node* node)
{
    Node *u = node->uncle();
    if ((u != nullptr)&&(u->color == Color::Red))
    {
        node->parent->color = Color::Black;
        u->color = Color::Black;
        Node *gr = node->grandpa();
        gr->color = Color::Red;
        addBalance(gr);
    }
    else
    {
        third_add_case(node);
    }
}

template <typename V, typename K>
void RBTree<V,K>::third_add_case(Node* node)
{
    Node *gr = node->grandpa();
    
    if ((node == node->parent->right)&&(node->parent == gr->left))
    {
        leftRotate(node->parent);
        node = node->left;
    }
    else if ((node == node->parent->left)&&(node->parent == gr->right))
    {
        rightRotate(node->parent);
        node = node->right;
    }
    fourth_add_case(node);
}

template <typename V, typename K>
void RBTree<V,K>::fourth_add_case(Node* node)
{
    Node *gr = node->grandpa();
    
    node->parent->color = Color::Black;
    gr->color = Color::Red;
    
    if ((node == node->parent->left)&&(node->parent == gr->left))
    {
        rightRotate(gr);
    }
    else
    {
        leftRotate(gr);
    }
}

template <typename V, typename K>
void RBTree<V,K>::removeFirstNode(K key)
{
    if (isEmpty())
        return;
    removeFirstNode(key, _root);
}

template <typename V, typename K>
void RBTree<V,K>::removeFirstNode(K key, Node* node)
{
    if (node == nullptr)
        return;
    if (key > node->key)
    {
        removeFirstNode(key, node->right);
    }
    if (key < node->key)
    {
        removeFirstNode(key, node->left);
    }
    if (key == node->key)
    {
        _size--;
        removeNode(node);
    }
    
}

template <typename V, typename K>
void RBTree<V,K>::removeNodesByKey(K key)
{
    int count1 = _size;
    for (size_t count = count1; count > 0; count--)
    {
        removeFirstNode(key,_root);
    }
}

template <typename V, typename K>
void RBTree<V, K>::removeNode(Node *node)
{
    //если у ноды нет потомков или потомок всего 1
    if (node->left == nullptr && node->right == nullptr)
    {
        removeBalance(node);
        if (node->parent->left == node)
            node->parent->left = 0;
        else if (node->parent->right == node)
            node->parent->right = 0;
        delete node;
        // _size--;
        return;
    }
    if (!node->left)
    {
        Node* right = node->right;
        node->value = right->value;
        node->key = right->key;
        node->left = right->left;
        node->right = right->right;
        removeBalance(right);
        delete right;
        //_size--;
        return;
    }
    else if (!node->right)
    {
        Node* left = node->left;
        node->value = left->value;
        node->key = left->key;
        node->left = left->left;
        node->right = left->right;
        removeBalance(left);
        delete left;
        // _size--;
        return;
    }
    //сюда попадают узлы с 2 потомками
    Node* n = node;
    if (n->right->left == 0)
    {
        n->value = n->right->value;
        n->key = n->right->key;
        Node* buf = n->right->right;
        removeBalance(n->right);
        delete n->right;
        // _size--;
        n->right = buf;
        return;
    }
    else
    {
        Node* l = n->right;
        while (l->left != 0)
        {
            l = l->left;
        }
        n->value = l->value;
        n->key = l->key;
        removeNode(l);
    }
}

template <typename V, typename K>
void RBTree<V,K>::removeBalance(Node *node)
{
    if (node->color == Color::Black && !node->right
            && !node->left)
    {
        first_delete_case(node);
    }
}

template <typename V, typename K>
void RBTree<V,K>::first_delete_case(Node *node)
{
    if (node->parent)
    {
        second_delete_case(node);
    }
}

template <typename V, typename K>
void RBTree<V,K>::second_delete_case(Node *node)
{
    Node *s = node->sibling();
    Node *parent = node->parent;
    if (s->color == Color::Red)
    {
        parent->color = Color::Red;
        s->color = Color::Black;
        if (parent->left == node)
            leftRotate(node->parent);
        else
            rightRotate(node->parent);
    }
    third_delete_case(node);
}

template <typename V, typename K>
void RBTree<V,K>::third_delete_case(Node *node)
{
    Node* s = node->sibling();
    
    if ((node->parent->color == Color::Black)
            && (s->color == Color::Black)
            && (!s->left || s->left->color==Color::Black)
            && (!s->right || s->right->color == Color::Black))
    {
        s->color = Color::Red;
        first_delete_case(node->parent);
    }
    else
        fourth_delete_case(node);
}

template <typename V, typename K>
void RBTree<V,K>::fourth_delete_case(Node *node)
{
    Node *s = node->sibling();
    if (node->parent->color == Color::Red
            && s->color == Color::Black
            && (!s->left || s->left->color == Color::Black)
            && (!s->right || s->right->color == Color::Black))
    {
        s->color = Color::Red;
        node->parent->color = Color::Black;
    }
    else fifth_delete_case(node);
}

template <typename V, typename K>
void RBTree<V,K>::fifth_delete_case(Node *node)
{
    Node* s = node->sibling();
    if (s->color == Color::Black)
    {
        if (node->parent->left == node
                && (!s->right || s->right->color == Color::Black)
                && (!s->left || s->left->color == Color::Red))
        {
            s->color = Color::Red;
            s->left->color = Color::Black;
            rightRotate(s);
        }
        else if (node->parent->right == node
                 && (!s->left || s->left->color == Color::Black)
                 && (!s->right || s->right->color == Color::Red))
        {
            s->color = Color::Red;
            s->right->color = Color::Black;
            leftRotate(s);
        }
    }
    sixth_delete_case(node);
}

template <typename V, typename K>
void RBTree<V,K>::sixth_delete_case(Node *node)
{
    Node* s = node->sibling();
    s->color = node->parent->color;
    node->parent->color = Color::Black;
    if (node->parent->left == node)
    {
        s->right->color = Color::Black;
        leftRotate(node->parent);
    }
    else
    {
        s->left->color = Color::Black;
        rightRotate(node->parent);
    }
}

template <typename V, typename K>
void RBTree<V,K>::rightRotate(Node *node)
{
    Node *pin = node->left;
    pin->parent = node->parent;
    if (node->parent)
    {
        if (node->parent->left == node)
            node->parent->left = pin;
        else
            node->parent->right = pin;
    }
    else
    {
        _root = pin;
    }
    node->left = pin->right;
    if (pin->right != nullptr)
        pin->right->parent = node;
    node->parent = pin;
    pin->right = node;
}

template <typename V, typename K>
void RBTree<V,K>::leftRotate(Node *node)
{
    Node *pin = node->right;
    pin->parent = node->parent;
    if (node->parent != nullptr)
    {
        if (node->parent->left == node)
            node->parent->left = pin;
        else
            node->parent->right = pin;
    }
    else
    {
        _root = pin;
    }
    node->right = pin->left;
    if (pin->left != nullptr)
        pin->left->parent = node;
    node->parent = pin;
    pin->left = node;
}

template <typename V, typename K>
V RBTree<V,K>::findNodeByKey(K key)
{
    return findNodeByKey(key, _root);
}
template <typename V, typename K>
V RBTree<V,K>::findNodeByKey(K key, Node* node)
{
    if (!node)
        throw std::out_of_range("no node");
    else if (node->key == key)
        return node->value;
    
    else if (node->key > key)
    {
        findNodeByKey(key, node->left);
    }
    else if (node->key < key)
    {
        findNodeByKey(key, node->right);
    }
}

template <typename V, typename K>
V RBTree<V,K>::findMaxKey()
{
    if (!isEmpty())
    {
        Node *node = _root;
        while (node->right)
        {
            node = node->right;
        }
        return node->value;
    }
}

template <typename V, typename K>
V RBTree<V,K>::findMinKey()
{
    if (!isEmpty())
    {
        Node *node = _root;
        while (node->left)
        {
            node = node->left;
        }
        return node->value;
    }
}

template <typename V, typename K>
string RBTree<V, K>::Node::getNodeColor()
{
    if (color == Color::Red)
        return "red";
    return "black";
}

template <typename V, typename K>
size_t RBTree<V,K>::size()
{
    return _size;
}


template <typename V, typename K>
bool RBTree<V,K>::isEmpty()
{
    if (_root == 0)
        return true;
    else
        return false;
}

template <typename V, typename K>
void RBTree<V,K>::printTree()
{
    int level = 0;
    printTree(_root, level);
}

template <typename V, typename K>
void RBTree<V,K>::printTree(Node *node, int level)
{
    if (isEmpty() == false)
    {
        if (node->right)
        {
            printTree(node->right, level+1);
        }
        for (int i = 0; i < level; i++)
        {
            string l = "     ";
            cout << l;
            if (i%10 == 0)
                l += l;
        }
        cout << node->value << " " << node->key << " "
             << node->getNodeColor() << endl;
        if (node->left)
        {
            printTree(node->left, level+1);
        }
    }
}
