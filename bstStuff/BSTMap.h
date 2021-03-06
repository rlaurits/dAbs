#include <utility>
#include <iostream>
#include <cstdio>
using namespace std;

template<typename K,typename V>
class BSTMap {
	struct Node {
	    Node *left;
	    Node *right;
        Node *parent;
        std::pair<K,V> data;
    };

    int sz;
    Node *root;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
         
        Node *ptr;
        Node *iter_root;

    public:
        friend class const_iterator;
        friend class BSTMap<K,V>;
        iterator(Node *nd, Node *rt) {
            ptr = nd;
            iter_root = rt;
        }
        iterator(const iterator &i) { 
            ptr = i.ptr;
            iter_root = i.iter_root;
        }
        iterator(const const_iterator c_iter) {
            ptr = c_iter.ptr;
            iter_root = c_iter.iter_root;
        }
        // an extra constructor to make an iterator pointing to the root
        // (so I don't have to type iterator(iter_root, iter_root) when I want that)
        iterator(Node *rt) {
            ptr = rt;
            iter_root = rt;
        }

        iterator farLeft() {
            if(ptr == nullptr) {
                return *this;
            } else {
                while(ptr-> left != nullptr) {
                    ptr = ptr-> left;
                }
                return *this;
            }
        }
        iterator farRight() {
            if(ptr == nullptr) {
                return *this;
            } else {
                while(ptr-> right != nullptr) {
                    ptr = ptr-> right;
                }
                return *this;
            }
        }

        bool operator==(const iterator &i) const {
            return (ptr == i.ptr) && (iter_root == i.iter_root);
        }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return ptr-> data; }
        //prefix
        iterator &operator++() {
            if(ptr != nullptr) {
                if(ptr-> right != nullptr) {
                    ptr = ptr-> right;
                    farLeft();
                } else {
                    while(ptr-> parent != nullptr && ptr-> parent-> right == ptr) {
                        ptr = ptr-> parent;
                    }
                    ptr = ptr-> parent;
                }
            }
            return *this;
        }
        iterator &operator--() {
            if(ptr == nullptr) {
                iterator iter(root);
                iter-> farRight();
                return iter;
            }
            if(ptr-> left != nullptr) {
                ptr = ptr-> left;
                farRight();
            } else {
                while(ptr-> parent != nullptr && ptr-> parent-> left == ptr) {
                    ptr = ptr-> parent;
                }
            }
            return *this;
        }
        //postfix
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
        Node *ptr;
        Node *iter_root;
                        
    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(const Node *nd) {
            
        }
        const_iterator(const const_iterator &iter) {
            ptr = iter.ptr;
        }
        const_iterator(const iterator &iter) {
            ptr = iter.ptr;
        }

        const_iterator farLeft() {
            while(ptr-> left!= nullptr) {
                ptr = ptr-> left;
            }
            return *this;
        }
        const_iterator farRight() {
            while(ptr-> right != nullptr) {
                ptr = ptr-> right;
            }
            return *this;
        }

        bool operator==(const const_iterator &i) const { return *ptr == i-> ptr;}
        bool operator!=(const const_iterator &i) const { return *this != i; }
        const std::pair<K,V> &operator*() { return ptr-> data;}
        const_iterator &operator++() {
            if(ptr != nullptr) {
                ptr = ptr-> right;
            }
            this-> farRight();
            return *this;
        }
        const_iterator &operator--() {
            if(ptr == nullptr) {
                const_iterator iter(root);
                iter-> farRight();
                return iter;
            }
            if(ptr-> left != nullptr) {
                ptr = ptr-> left;
            }
            this-> farLeft();
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
        root = nullptr;
        sz = 0;
    }
    ~BSTMap() {
        clear();
        delete *root;
<<<<<<< HEAD
=======
    }

    Node *copySubTree(Node *nd) {
        Node *newparent = new Node;
        newparent = nd;
        insert(nd-> data);
        Node **ptrptr = insert.first.ptr;
        ptrptr = newparent;
        if(nd-> left != nullptr) {
            //Node *newleft = new Node;
            //newleft-> parent = ptrptr;
            //ptrptr-> left = newleft;
            newleft = copySubTree(nd-> left);
        }
        if(nd-> right != nullptr) {
            Node *newright = new Node;
            //newright = copySubTree(nd-> right);
            //newright-> parent = newparent;
            //newparent-> right = newright;
            newright = copySubTree(nd-> right);
        }
        return newparent;
>>>>>>> e8073c4c734fb042b83729c3f38acfa49d46875b
    }
        

    BSTMap(const BSTMap<K,V> &that) {
        
        copySubTree;
            
        
    }

    BSTMap &operator=(const BSTMap<K,V> &that) {
        delete *this;
        return BSTMap(that);
    }

    bool empty() const { return size() == 0; }

    unsigned size() const { 
        cout<<"TESTING\n";
        return sz; 
    }

    iterator find(const key_type& k) {
        for(iterator iter = begin(); iter != end(); ++iter) {
            if(iter.ptr-> data.first == k) {
                return iter;
            }
        }
        iterator iter = end();
        return iter;
    }

    const_iterator find(const key_type& k) const {
        iterator iter = find(k);
        return const_iterator(iter);
    }

    unsigned int count(const key_type& k) const { 
        if(find(k)!=cend()) return 1;
        else return 0;
    }

        // - finds the place k belongs in the tree, returns a ptr to
        //   the parent it needs to be inserted under - //
    Node *descend(Node *nd, const key_type &k) {
        if(k < nd-> data.first) {
            if(nd-> left == nullptr) {
                return nd;
            } else {
                return descend(nd-> left, k);
            }
        } else {
            if(nd-> right == nullptr) {
                return nd;
            } else {
                return descend(nd-> right, k);
            }
        }
        
    }

    std::pair<iterator,bool> insert(const value_type& val) {
        if(sz == 0) {
            Node *newnode = new Node;
            newnode-> data = val;
            newnode-> left = nullptr;
            newnode-> right = nullptr;
            newnode-> parent = nullptr;
            root = newnode;
            ++sz;
            return std::make_pair(iterator(root), true);
        } else if(find(val.first) != end()) {
            return std::make_pair(find(val.first), false);
        } else {
            cout<<"testingA\n";
            Node *newnode = new Node;
            //Node *ndptr = &newnode;
            newnode-> data = val;
            newnode-> left = nullptr;
            newnode-> right = nullptr;
            Node *prnt = descend(root, val.first);
            newnode-> parent = prnt;
            if(newnode-> data.first < prnt-> data.first) {
                prnt-> left = newnode;
                ++sz;
                return std::make_pair(iterator(newnode), true);
            } else {
                prnt-> right = newnode;
                ++sz;
                return std::make_pair(iterator(newnode), true);
            }
        }
    }

    
    

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    iterator erase(const_iterator position);
        

    unsigned int erase(const key_type& k){
        const_iterator it = find(k);
        if (it!=cend()) {
            erase(it);
            return 1;
        }
        else {
            return 0;
        }
    }

    void clear() {
        while(sz > 0) {
            erase(cbegin());
        }
    }

    mapped_type &operator[](const K &key){
        return (*insert(make_pair(key, V())).first).second;
    }

    bool operator==(const BSTMap<K,V>& rhs) const;

    bool operator!=(const BSTMap<K,V>& rhs) const { 
        return ! (*this == rhs); 
    }

    iterator begin() { return iterator(root).farLeft(); }

    const_iterator begin() const { 
        return const_iterator(root).farLeft(); 
    }

    iterator end() {
        iterator iter = iterator(root).farRight();
        iter.ptr = nullptr;
        return iter;
    }

    const_iterator end() const {
        const_iterator c_iter = const_iterator(root).farRight();
        c_iter.ptr = nullptr;
        return c_iter;
    }

    const_iterator cbegin() const {
        return const_iterator(root).farLeft(); 
    }

    const_iterator cend() const {
        const_iterator c_iter = const_iterator(root).farRight();
        c_iter.ptr = nullptr;
    }

};
