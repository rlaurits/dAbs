#include <utility>

template<typename K,typename V>
class BSTMap {
    // TODO: Define your Node
	struct Node {
	Node *left;
	Node *right;
    Node *parent;
    //std::pair<K,V> data;
};

    // TODO: specify whatever member data you need.
    int sz;
    Node *root;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // TODO: Iterator data. 
        Node *ptr;

        //Need to be able to go back from end, i.e. --end() should 
        //give last element.
        //One approach is to keep a Node* and a bool that tells me if 
        //it is at end.
        //If just keeping Node* and use nullptr to indicate end(), then
        //operator-- need a case for nullptr, in which case to get the 
        //maximum element. But to get the maximum element, we need to 
        //store information about the tree, e.g. the root pointer, as member.
    public:
        friend class const_iterator;
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
            while(ptr-> left != nullptr) {
                *ptr = ptr-> left;
            }
        }
        iterator farRight() {
            while(ptr-> right != nullptr) {
                *ptr = ptr-> right;
            }
        }
        
        bool operator==(const iterator &i) const { return *ptr == i-> ptr; }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return *ptr; }
        iterator &operator++() {
            //TODO
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
        root = nullptr;
        sz = 0;
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

    bool empty() const { return size() == 0; }

    unsigned size() const { /*TODO*/ }

    iterator find(const key_type& k);

    const_iterator find(const key_type& k) const;

    unsigned int count(const key_type& k) const { 
        if(find(k)!=cend()) return 1;
        else return 0;
    }

    std::pair<iterator,bool> insert(const value_type& val);

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

    void clear();

    mapped_type &operator[](const K &key){
        return (*insert(make_pair(key, V())).first).second;
    }

    bool operator==(const BSTMap<K,V>& rhs) const;

    bool operator!=(const BSTMap<K,V>& rhs) const { return ! (*this == rhs); }

    iterator begin() { return iterator(/*TODO*/); }

    const_iterator begin() const { return const_iterator(/*TODO*/); }

    iterator end() { return iterator(/*TODO*/); }

    const_iterator end() const { return const_iterator(/*TODO*/); }

    const_iterator cbegin() const { return const_iterator(/*TODO*/); }

    const_iterator cend() const { return const_iterator(/*TODO*/); }

};
