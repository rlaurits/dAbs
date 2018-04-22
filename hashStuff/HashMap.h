#include <string>
#include <vector>
using namespace std;

template<typename K,typename V,typename Hash>
class HashMap {
    Hash hashFunction;
    // Data to store the hash table and the number of elements.

    int sz;
    
    // Suggestion for the hash table: either
    vector<vector<pair<K,V>>> table;
    // or
    // vector<list<pair<K,V>>> table;
    // would work well for the chaining approach. 

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
        // NOTE: These might be different depending on how you store your table.
        typename std::remove_reference<decltype(table.begin())>::type mainIter;
        typename std::remove_reference<decltype(table.begin())>::type mainEnd;
        typename std::remove_reference<decltype(table[0].begin())>::type subIter;
    public:
        friend class const_iterator;

        // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi,const decltype(mainEnd) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi,
                const decltype(mainEnd) me,
                const decltype(subIter) si):
                mainIter(mi),mainEnd(me),subIter(si) {}

        bool operator==(const iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return *subIter; }
        iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    class const_iterator {
        // NOTE: These might be different depending on how you store your table.
        typename std::remove_reference<decltype(table.cbegin())>::type mainIter;
        typename std::remove_reference<decltype(table.cbegin())>::type mainEnd;
        typename std::remove_reference<decltype(table[0].cbegin())>::type subIter;
    public:
        // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.cbegin()) mi,const decltype(table.cbegin()) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.
        const_iterator(const decltype(table.cbegin()) mi,
            const decltype(table.cbegin()) me,
            const decltype(table[0].cbegin()) si):
                mainIter(mi),mainEnd(me),subIter(si) {}
        const_iterator(const decltype(table.begin()) mi,
            const decltype(table.begin()) me,
            const decltype(table[0].begin()) si):
                mainIter(mi),mainEnd(me),subIter(si) {}

        // NOTE: These might be different depending on how you store your table.
        const_iterator(const iterator &i):mainIter(i.mainIter),mainEnd(i.mainEnd),subIter(i.subIter) {

        }

        bool operator==(const const_iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const std::pair<K,V> &operator*() const { return *subIter; }
        const_iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    HashMap(const Hash &hf);
    // HashMap(const HashMap<K,V,Hash> &that); // Only if needed.

    // HashMap &operator=(const HashMap<K,V,Hash> &that); // Only if needed.

    bool empty() const;

    unsigned int size() const;

    iterator find(const key_type& k);

    const_iterator find(const key_type& k) const;

    int count(const key_type& k) const;

    std::pair<iterator,bool> insert(const value_type& val);

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        // TODO: Put this one here to simplify the templates
    }

    iterator erase(const_iterator position);

    int erase(const key_type& k) {
        const_iterator iter = find(k);
        if(iter == cend()) return 0;
        erase(iter);
        return 1;
    }

    void clear();

    mapped_type &operator[](const K &key);

    bool operator==(const HashMap<K,V,Hash>& rhs) const;

    bool operator!=(const HashMap<K,V,Hash>& rhs) const {return !(*this==rhs);}

    // NOTE: These might be different depending on how you store your table
    iterator begin() {
        return iterator(table.begin(),table.end());
    }

    const_iterator begin() const{
        return const_iterator(table.begin(),table.end());
    }

    iterator end(){
        return iterator(table.end(),table.end());
    }

    const_iterator end() const{
        return const_iterator(table.end(),table.end());
    }

    const_iterator cbegin() const{
        return const_iterator(table.begin(),table.end());
    }

    const_iterator cend() const{
        return const_iterator(table.end(),table.end());
    }

private:
    void growTableAndRehash();
};
