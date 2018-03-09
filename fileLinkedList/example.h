template<typename T>
class FileLinkedList {
        FileLinkedList(const FileLinkedList<T> &that) = delete;
        FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;

        // TODO - Your private data.
        struct Node {
            T data;
            int prev;
            int next;
        }

        // TODO - Private helper functions. (Maybe file IO with an index.)

        static int readPrev(int node, FILE *f) {    //static means it doesn't depend on any specific
            int tmp;                                //variables
            fseek(f, node+sizeof(T), SEEK_SET);     //address of node, + data
            fread(&tmp, sizeof(int), 1, f);
            return tmp;
        }

    public:
        typedef T value_type;

        class const_iterator {
                // TODO - Your private data.
                int node;
                FILE *file;
            public:
                const_iterator(int i,FILE *f);
                const_iterator(const const_iterator &i);
                T operator*();
                bool operator==(const const_iterator &i) const;
                bool operator!=(const const_iterator &i) const;
                const_iterator &operator=(const const_iterator &i);
                const_iterator &operator++() {
                    node = readNext(node);  //this throws an error bc readNext is part of 
                    return *this;           //LinkedList and refers to its f, not const_iterator's
                }                           //sol: revise readPrev to take in a FILE*
                const_iterator &operator--();
                const_iterator operator++(int);
                const_iterator operator--(int);

                friend class FileLinkedList;
        };

        // General Methods
        FileLinkedList(const std::string &fname);

        template<typename I>  // The type I will be an iterator.
        FileLinkedList(I begin,I end,const std::string &fname) {
            // TODO - Write this one here. It is easier than trying to fight with adding a template below.
        }
        ~FileLinkedList();
        void push_back(const T &t) { insert(end(),t); }
        void pop_back() { erase(--end()); }
        int size() const;
        void clear() { while (size()>0) pop_back(); }
        const_iterator insert(const_iterator position, const T &t){
            auto pos = position.ptr;
            int newnode = -1;
            //ask freelist
            if(freelist == -1) {
                //write to end of file
                //we know there are no gaps
                //fseek(f, sizeof(Node)+2*sizeof(int)+sz*sizeof(Node, SEEK_SET);
                newnode = sizeof(Node)+2*sizeof(int)+sz*sizeof(Node);   //don't need fseek
                                                                        //bc set newnode's address
            } else {
                int newhead = readNext(freelist);   //the address of the next node
                newnode = freelist;
                freelist = newhead;
            }
            writeData(newnode, t);              //makes newnode-> data = t
            writeNext(newnode, pos);            //makes newnode-> next = pos
            writePrev(newnode, readPrev(pos));  //so that newnode-> prev = pos-> prev
            writeNext(readPrev(pos), newnode);  //makes pos-> prev-> next = newnode
            writePrev(pos, newnode);            //makes pos-> prev = newnode

            return const_iterator(newnode, f);  //not sure why there's an f here?
        }
            
        T operator[](int index) const{
            auto itr=begin();
            for (int i=0;i<index;++i) ++itr;
            return *itr;
        }
        const_iterator erase(const_iterator position) {
            //easier than insert, bc you don't have to check if freelist is empty first
            int pos = position. ...;
            
            //modify pointers

            //push into freelist
            writeNext(pos, freelist);
            freelist = pos;
        }
        void set(const T &value,int index);
        void set(const T &value,const_iterator position);

        const_iterator begin();
        const_iterator begin() const;
        const_iterator end();
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
};
