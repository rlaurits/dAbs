template<typename K,typename V>
class AVLMap {
    // TODO: Define your Node

    // TODO: specify whatever member data you need.
    Node *root = nullptr;
    int sz = 0;

    void updateh(Node *node) {
        if(node == nullptr) return;     //this is the base case
            
            updateh(node-> parent);
        }
    }

    int lrotate(Node *node) {
        Node *newroot = node-> right;
        Node *y = newroot-> left;
        if(node-> parent == nullptr) {
            root = newroot;
        } else if (node-> parent-> left == node) {
            node-> parent-> left = newroot;
        } else {
            node-> parent-> right = newroot;
        }
        newroot-> parent = node-> parent;

        newroot-> left = node;
        node-> parent = newroot;
        node-> right = y;
        //y might not exist, though, so if statement
        if(y != nullptr) y-> parent = node;
        updateh(node);

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // TODO: Iterator data. I keep a Node* and a bool that tells me if it is at end.
    public:
        friend class const_iterator;
        iterator(/*TODO*/)/*:...*/ { /*TODO*/ }
        // TODO: Other constructors as needed.

        bool operator==(const iterator &i) const { /*TODO*/ }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { /*TODO*/ }
        iterator &operator++() {
            // TODO
            return *this;
        }
        iterator &operator--() {
            // TODO
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
    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(/*TODO*/)/*:...*/ { /*TODO*/ }
        // TODO: Other constructors as needed.
        const_iterator(const iterator &iter)/*:...*/ {}

        bool operator==(const const_iterator &i) const { /*TODO*/ }
        bool operator!=(const const_iterator &i) const { /*TODO*/ }
        const std::pair<K,V> &operator*() { /*TODO*/ }
        const_iterator &operator++() {
            // TODO
            return *this;
        }
        const_iterator &operator--() {
            // TODO
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
        // TODO
    }
    ~BSTMap() {
        // TODO
    }
    BSTMap(const BSTMap<K,V> &that) {
        // TODO
    }

    BSTMap &operator=(const BSTMap<K,V> &that) {
        // TODO
    }

    bool empty() const { /*TODO*/ }

    unsigned size() const { /*TODO*/ }

    iterator find(const key_type& k);

    const_iterator find(const key_type& k) const;

    unsigned int count(const key_type& k) const;

    std::pair<iterator,bool> insert(const value_type& val);

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    iterator erase(const_iterator position) {
        Node *z = position.node;
        Node *ret = (++position).node;
        if(z-> left == nullptr) {
            transplant(z, z???????

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
