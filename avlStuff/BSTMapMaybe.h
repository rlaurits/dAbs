#include <utility>
#include <cassert>
using std::make_pair;

template<typename K,typename V>
class BSTMap {
    // Define your Node
    struct Node{
    std::pair<K,V> data;
    Node* left;
    Node* right;
    Node* parent;
    };
    // specify whatever member data you need.
    Node* root=nullptr;
    int sz=0;

    void destroy(Node* node){
    if (node){
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    }
    Node* minimum(Node* node) const {
    if (node==nullptr)return nullptr;
    while(node->left)node=node->left;
    return node;
    }
    static Node* maximum(Node* node) {
    if (node==nullptr) return nullptr;
    while(node->right)node=node->right;
    return node;
    }
    void transplant(Node* u,Node* v){
    if(u->parent==nullptr) root=v;
    else if (u==u->parent->left)u->parent->left=v;
    else u->parent->right=v;
    if (v) v->parent=u->parent;
    }
public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // TODO: Iterator data. I keep a Node* and a bool that tells me if it is at end.
    Node* node;
    Node* root;
    public:
        friend class const_iterator;
        iterator(Node* r,Node* n=nullptr):node{n}, root{r} { }
        bool operator==(const iterator &i) const { return node==i.node;  }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { assert(node); return node->data;}
        iterator &operator++() {
        assert(node);
            if(node->right){
        node=node->right;
        while (node->left) node=node->left;
        }
        else{
        auto y=node->parent;
        while ( y && node==y->right){
            node=y;
            y=y->parent;
        }
        node=y;
        }
            return *this;
        }
        iterator &operator--() {
        if(node==nullptr)node= maximum(root);
            else if(node->left){
        node=node->left;
        while(node->right)node=node->right;
        }
        else {
        auto y=node->parent;
        while(y && node==y->left){
            node=y;
            y=y->parent;
        }
        node=y;
        }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };

    class const_iterator {
        // TODO: iterator data
    Node* node;
    Node* root;
    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(Node* r,Node* n=nullptr):node{n},root(r) {  }
        // TODO: Other constructors as needed.
        const_iterator(const iterator &iter):node{iter.node},root{iter.root} {}

        bool operator==(const const_iterator &i) const { return node==i.node; }
        bool operator!=(const const_iterator &i) const {  return node!=i.node;}
        const std::pair<K,V> &operator*() { assert(node); return node->data; }
        const_iterator &operator++() {
            if(node->right){
        node=node->right;
        while (node->left) node=node->left;
        }
        else{
        auto y=node->parent;
        while ( y && node==y->right){
            node=y;
            y=y->parent;
        }
        node=y;
        }

            return *this;
        }
        const_iterator &operator--() {
        if(node==nullptr) node=maximum(root);
            else if(node->left){
        node=node->left;
        while(node->right)node=node->right;
        }
        else {
        auto y=node->parent;
        while(y && node==y->left){
            node=y;
            y=y->parent;
        }
        node=y;
        }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };



    BSTMap() {
    }
    ~BSTMap() {
    clear();
    }
    BSTMap(const BSTMap<K,V> &that) {
        for(auto &x:that) insert(x);
    }

    BSTMap &operator=(const BSTMap<K,V> &that) {
        clear();
    for(auto& x:that)insert(x);
    }

    bool empty() const { return size()==0; }

    unsigned size() const { return sz; }

    iterator find(const key_type& k){
    Node* ptr = root;
    while(ptr!=nullptr){
        if (k== ptr->data.first) return iterator(root,ptr);
        if (k<ptr->data.first) ptr=ptr->left;
        else ptr=ptr->right;
    }
    return end();
    }

    const_iterator find(const key_type& k) const{
    Node* ptr = root;
    while(ptr!=nullptr){
        if (k== ptr->data.first) return const_iterator(root,ptr);
        if (k<ptr->data.first) ptr=ptr->left;
        else ptr=ptr->right;
    }
    return cend();
    }

    unsigned int count(const key_type& k) const{
    return find(k)!=cend();
    }

    std::pair<iterator,bool> insert(const value_type& val){
    Node* ptr = root;
    Node* parent=nullptr;
    while(ptr!=nullptr){
        parent=ptr;
        if (val.first== ptr->data.first) return std::make_pair(iterator(root,ptr), false);
        if (val.first<ptr->data.first) ptr=ptr->left;
        else ptr=ptr->right;
    }
    auto newNode=new Node{val, nullptr,nullptr, parent};
    if (parent==nullptr) root=newNode;
    else if (newNode->data.first < parent->data.first) parent->left =newNode;
    else parent->right=newNode;
    sz++;
    return std::make_pair(iterator(root,newNode), true);
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    iterator erase(const_iterator position){
    Node* z=position.node;
    Node* ret = (++position).node;
    if(z->left==nullptr){
        transplant(z,z->right);
    }
    else if(z->right==nullptr){
        transplant(z,z->left);
    }
    else {
        Node* y=minimum(z->right);
        if(y->parent!=z){
            transplant(y,y->right);
            y->right=z->right;
            y->right->parent=y;
        }
        transplant(z,y);
        y->left=z->left;
        y->left->parent=y;
    }
    sz--;
    delete z;
    return iterator(root,ret);
    }

    unsigned int erase(const key_type& k){
    auto it=find(k);
    if(it==end())return 0;
    else {
        erase(it);
        return 1;
    }
    }

    void clear(){
    destroy(root);
    root=nullptr;
    sz=0;
    }

    mapped_type &operator[](const K &key){
    auto i=insert(make_pair(key, V{})).first;
    return (*i).second;
    }

    bool operator==(const BSTMap<K,V>& rhs) const{
    for (auto i=rhs.begin();i!=rhs.end();++i){
            auto r=find((*i).first);
                if(r==end() || (*r).second!=(*i).second)return false;
    }
    return size()==rhs.size();
    }

    bool operator!=(const BSTMap<K,V>& rhs) const{return   ! (*this == rhs);}

    iterator begin() { return iterator(root,minimum(root)); }

    const_iterator begin() const { return const_iterator(root,minimum(root)); }

    iterator end() { return iterator(root); }

    const_iterator end() const { return const_iterator(root); }

    const_iterator cbegin() const { return const_iterator(root,minimum(root)); }

    const_iterator cend() const { return const_iterator(root); }

};
