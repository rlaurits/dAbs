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

    public:
        friend class const_iterator;
        friend class BSTMap<K,V>;
        iterator(Node *nd) {
            ptr = nd;
        }
        iterator(const iterator &i) { 
            ptr = i.ptr;
        }
        iterator(const const_iterator citer) {
            ptr = citer.ptr;
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

        bool operator==(const iterator &i) const { return ptr == i.ptr; }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return ptr-> data; }
        //prefix
        iterator &operator++() {
            if(ptr != nullptr) {
                ptr = ptr-> right;
            }
            this-> farLeft();
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
            }
            this-> farRight();
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
    }
    BSTMap(const BSTMap<K,V> &that) {
        // TODO
    }

    BSTMap &operator=(const BSTMap<K,V> &that) {
        // TODO
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
            newnode-> parent = nullptr;
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
        return iterator(root).farRight();
    }

    const_iterator end() const {
        return const_iterator(root).farRight();
    }

    const_iterator cbegin() const {
        return const_iterator(root).farLeft(); 
    }

    const_iterator cend() const {
        return const_iterator(root).farRight();
    }

};
