template<typename K,typename V>
class AVLMap {
    // TODO: Define your Node
    struct Node {
        std::pair<K,V> data;
        Node *left;
        Node *right;
        Node *parent;
        int height;
    };

    // TODO: specify whatever member data you need.
    Node *root;
    int sz;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // TODO: Iterator data. I keep a Node* and a bool that tells me if it is at end.
        Node *ptr;
        bool atEnd;
    public:
        friend class const_iterator;
        iterator(Node *nd) {
            ptr = nd;
            atEnd = false;
        }
        iterator(const iterator &i) {
            ptr = i.ptr;
            atEnd = i.atEnd;
        }
        iterator(const const_iterator c_iter) {
            ptr = c_iter.ptr;
            atEnd = c_iter.atEnd;
        }

        iterator farLeft() {
            if(ptr-> left != nullptr && atEnd != true) {
                while(ptr-> left != nullptr) {
                    ptr = ptr-> left;
                }
            }
            return *this;
        }
        iterator farRight() {
            if(ptr-> right != nullptr && atEnd != true) {
                while(ptr-> right != nullptr) {
                    ptr = ptr-> right;
                }
            }
            return *this;
        }

        //I'm not entirely sure exactly what values to compare here
        //The pointers? The nodes? The nodes' data?
        bool operator==(const iterator &i) const {
            return (ptr = i.ptr) && (atEnd == i.atEnd);
        }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return ptr-> data; }
        iterator &operator++() {
            if(atEnd == false) {
                if(ptr-> right != nullptr) {
                    ptr = ptr-> right;
                    farLeft();
                } else {
                    Node *tmp = ptr;
                    while(ptr-> parent != nullptr
                            && ptr-> parent-> right == ptr) {
                        ptr = ptr-> parent;
                    }
                    //bc this means that we're at the root and still haven't
                    //found a node bigger than us, so we must be at the end:
                    if(ptr-> parent == nullptr) {
                        ptr = tmp;
                        atEnd = true;
                    } else {
                        ptr = ptr-> parent;
                    }
                }
            }
            return *this;
        }
        iterator &operator--() {
            if(atEnd == true) {
                atEnd = false;
            } else {
                if(ptr-> left != nullptr) {
                    ptr = ptr-> left;
                    farRight();
                } else {
                    Node *tmp = ptr;
                    while(ptr-> parent != nullptr
                            && ptr-> parent-> left == ptr) {
                        ptr = ptr-> parent;
                    }
                    if(ptr-> parent == nullptr) {
                        ptr = tmp;
                    } else {
                        ptr = ptr-> parent;
                    }
                }
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
        Node *ptr;
        bool atEnd;
    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(Node *nd) {
            ptr = nd;
        }
        const_iterator(const iterator &iter) {
            ptr = iter.ptr;
            atEnd = iter.atEnd;
        }
        const_iterator(const const_iterator &iter) {
            ptr = iter.ptr;
            atEnd = iter.atEnd;
        }

        bool operator==(const const_iterator &i) const {
            return (ptr == i.ptr) && (atEnd == i.atEnd);
        }
        bool operator!=(const const_iterator &i) const { !(*this == i) }
        const std::pair<K,V> &operator*() { return ptr-> data; }
        const_iterator &operator++() {
            iterator iter(*this);
            ++iter;
            return const_iterator(iter);
        }
        const_iterator &operator--() {
            iterator iter(*this);
            --iter;
            return const_iterator(iter);
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

    Node *copySubTree(Node *nd, BSTMap<K,V> &bst) {
        Node *newparent = new Node;
        newparent = bst.insert(nd-> data).first.ptr;
        if(nd-> left != nullptr) {
            newparent-> left = copySubTree(nd-> left);
        }
        if(nd-> right != nullptr) {
            newparent-> right = copySubTree(nd-> right);
        }
        return newparent;
    }

    BSTMap(const BSTMap<K,V> &that) {
        copySubTree(that.root, *this);
    }

    BSTMap &operator=(const BSTMap<K,V> &that) {
        clear();
        copySubTree(that.root, *this);
    }

    bool empty() const { return sz == 0; }

    unsigned size() const { return sz; }

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

    unsigned int count(const key_type& k) const {
        if(find(k) != cend()) return 1;
        else return 0;
    }

    // finds the place k belongs in the tree, returns a ptr to the parent
    // it needs to be inserted under
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
            newnode-> height = 1;
            root = newnode;
        } else if(find(val.first) != end()) {
            return std::make_pair(find(val.first), false);
        } else {
            Node *newnode = new Node;
            newnode-> data = val;
            newnode-> left = nullptr;
            newnode-> right = nullptr;
            newnode-> height = 1;
            Node *prnt = descend(root, val.first);
            newnode-> parent = prnt;
            if(newnode-> data.first < prnt-> data.first) {
                prnt-> left = newnode;
            } else {
                prnt-> right = newnode;
            }
        }
        ++sz;
        return std::make_pair(iterator(newnode), true);
    }


    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    iterator erase(const_iterator position);

    unsigned int erase(const key_type& k);

    void clear();

    mapped_type &operator[](const K &key){
        return (*insert(make_pair(key, V())).first).second;
    }

    bool operator==(const BSTMap<K,V>& rhs) const;

    bool operator!=(const BSTMap<K,V>& rhs) const;

    iterator begin() { return iterator(/*TODO*/); }

    const_iterator begin() const { return const_iterator(/*TODO*/); }

    iterator end() { return iterator(/*TODO*/); }

    const_iterator end() const { return const_iterator(/*TODO*/); }

    const_iterator cbegin() const { return const_iterator(/*TODO*/); }

    const_iterator cend() const { return const_iterator(/*TODO*/); }

};
