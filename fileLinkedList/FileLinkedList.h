template<typename T>
class FileLinkedList {
        FileLinkedList(const FileLinkedList<T> &that) = delete;
        FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;

        // TODO - Your private data.
        struct Node {
            T data;
            int prev;
            int next;
        };
        Node sentinel;
        FILE *file;
        int freelist;

        // TODO - Private helper functions. (Maybe file IO with an index.)

        static int readPrev(int nodeptr, FILE *f) {
            int tmp;
            fseek(f, nodeptr+sizeof(T), SEEK_SET);
            fread(&tmp, sizeof(int), 1, f);
            return tmp;
        }
        static int readNext(int nodeptr, FILE *f) {    //node is just the address
            int tmp;
            fseek(f, nodeptr+sizeof(T)+sizeof(int), SEEK_SET);
            fread(&tmp, sizeof(int), 1, f);
            return tmp;
        }
        static T readData(int nodeptr, FILE *f) {
            T tmp;
            fseek(f, nodeptr, SEEK_SET);
            fread(&tmp, sizeof(T), 1, f);
            return tmp;
        }
        static void writeData(int nodeptr, FILE *f) {
            fseek(f, nodeptr, SEEK_SET);
            fwrite(&nodeptr, sizeof(T), 1, f);
        }
        
    public:
        typedef T value_type;

        class const_iterator {
                // TODO - Your private data.
                int nodeptr;
                FILE *file;
            public:
                const_iterator(int i,FILE *f) {
                    nodeptr = i;
                    file = f;
                }
                const_iterator(const const_iterator &i) {
                    nodeptr = i.nodeptr;
                    file = i.file;
                }
                T operator*() {
                    T ret;
                    ret = readData(nodeptr, file);
                    return ret;
                }
                bool operator==(const const_iterator &i) const {
                    return nodeptr == i.nodeptr;
                }
                bool operator!=(const const_iterator &i) const {
                    return nodeptr != i.nodeptr;
                }
                const_iterator &operator=(const const_iterator &i) {
                    nodeptr = i.nodeptr;
                    file = i.file;
                }
                const_iterator &operator++() {
                    auto next = readNext(nodeptr, file);
                    nodeptr = next;
                    return *this;
                }
                const_iterator &operator--() {
                    auto prev = readPrev(nodeptr, file);
                    nodeptr = prev;
                    return *this;
                }
                const_iterator operator++(int) {//I don't remember which one of
                    auto next = readNext(nodeptr, file);
                    nodeptr = next;
                    return *this;
                }
                const_iterator operator--(int) {//these was pre and post
                    auto prev = readPrev(nodeptr, file);
                    nodeptr = prev;
                    return *this;
                }
                                                //...or even which does what...
                friend class FileLinkedList;
        };

        // General Methods
        FileLinkedList(const std::string &fname) {
            file = fopen(fname.c_str(), "w+");
            //sentinel = new Node;
            sentinel.prev = &sentinel;
            sentinel.next = &sentinel;
            freelist = -1;
        }

        template<typename I>  // The type I will be an iterator.
        FileLinkedList(I begin,I end,const std::string &fname) {
            // TODO - Write this one here. It is easier than trying to fight with adding a template below.
        }
        ~FileLinkedList();
        void push_back(const T &t) { insert(end(),t); }
        void pop_back() { erase(--end()); }
        int size() const;
        void clear() { while (size()>0) pop_back(); }
        const_iterator insert(const_iterator position, const T &t);
        T operator[](int index) const{
            auto itr=begin();
            for (int i=0;i<index;++i) ++itr;
            return *itr;
        }
        const_iterator erase(const_iterator position);
        void set(const T &value,int index);
        void set(const T &value,const_iterator position);

        const_iterator begin() {
            auto iter = new const_iterator(sentinel.next, file);
            return iter;
        }
        const_iterator begin() const {
            auto iter = new const_iterator(sentinel.next, file);
            return iter;
        }
        const_iterator end() {
            auto iter = new const_iterator(sentinel, file);
            return iter;
        }
        const_iterator end() const {
            auto iter = new const_iterator(sentinel, file);
            return iter;
        }
        const_iterator cbegin() const {
            auto iter = new const_iterator(sentinel.next, file);
            return iter;
        }
        const_iterator cend() const {
            auto iter = new const_iterator(sentinel, file);
            return iter;
        }
};
