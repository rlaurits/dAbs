#include <cstdio>
#include <string>

template<typename T>
class FileLinkedList {
        FileLinkedList(const FileLinkedList<T> &that) = delete;
        FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;

        // - private data.

        //wait...do we even need to define a Node struct??
        /*
        struct Node {
            T data;
            int prev;
            int next;
        };
        */
        //Node sentinel;

        //  layout of private data in head of file:  //
        //  |sz||freelist||sentinel||...nodes...|    //
        int sz;
        int freelist;
        int sentinel = 2*sizeof(int);
        int nodeSZ = 2*sizeof(int) + sizeof(T);
        FILE *file;
        
        // - Private helper functions.
        // - whoops, I wrote quite a lot of them, didn't I?

        static int readPrev(int nodeptr, FILE *f) {
            int tmp;
            fseek(f, nodeptr+sizeof(T), SEEK_SET);
            fread(&tmp, sizeof(int), 1, f);
            return tmp;
        }
        static void writePrev(int nodeptr, int newPrev, FILE *f) {
            fseek(f, nodeptr+sizeof(T), SEEK_SET);
            fwrite(&newPrev, sizeof(int), 1, f);
        }
        static int readNext(int nodeptr, FILE *f) {
            int tmp;
            fseek(f, nodeptr+sizeof(T)+sizeof(int), SEEK_SET);
            fread(&tmp, sizeof(int), 1, f);
            return tmp;
        }
        static void writeNext(int nodeptr, int newNext, FILE *f) {
            fseek(f, nodeptr+sizeof(T)+sizeof(int), SEEK_SET);
            fwrite(&newNext, sizeof(int), 1, f);
        }
        static T readData(int nodeptr, FILE *f) {
            T tmp;
            fseek(f, nodeptr, SEEK_SET);
            fread(&tmp, sizeof(T), 1, f);
            return tmp;
        }
        static void writeData(int nodeptr, const T t, FILE *f) {
            fseek(f, nodeptr, SEEK_SET);
            fwrite(&t, sizeof(T), 1, f);
        }
        //- these two are to read/update the size within the file -//
        int readSZ(FILE *f) {
            fseek(f, 0, SEEK_SET);
            int ret;
            fread(&ret, sizeof(int), 1, f);
            return ret;
        }
        void updateSZ(const int s) {
            fseek(file, 0, SEEK_SET);
            fwrite(&s, sizeof(int), 1, file);
        }
        //- these two are to read/update the freelist within the file -//
        int readFL(FILE *f) {
            fseek(f, sizeof(int), SEEK_SET);
            int ret;
            fread(&ret, sizeof(int), 1, f);
            return ret;
        }
        void updateFL(const int head) {
            fseek(file, sizeof(int), SEEK_SET);
            fwrite(&head, sizeof(int), 1, file);
        }

        
    public:
        typedef T value_type;

        class const_iterator {
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

                //This is prefix (returns val after incrementing)
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
                //This is postfix (returns val before incrementing)
                const_iterator operator++(int) {
                    auto tmp = *this;
                    auto next = readNext(nodeptr, file);
                    nodeptr = next;
                    return tmp;
                }
                const_iterator operator--(int) {
                    auto tmp = *this;
                    auto prev = readPrev(nodeptr, file);
                    nodeptr = prev;
                    return tmp;
                }
                                                
                friend class FileLinkedList;
        };

        // General Methods
        FileLinkedList(const std::string &fname) {
            file = fopen(fname.c_str(), "r+");
            if(file == 0) {
                sz = readSZ(file);
                freelist = readFL(file);
            } else {
                file = fopen(fname.c_str(), "w+");
                writePrev(sentinel, sentinel, file);
                writeNext(sentinel, sentinel, file);
                sz = 0;
                freelist = -1;
                updateSZ(sz);
                updateFL(freelist);
            }
        }

        template<typename I>
        FileLinkedList(I begin,I end,const std::string &fname) {}
        //I'm gonna be honest, I don't know what this constructor is
        //supposed to do

        ~FileLinkedList() {
            clear();
            fclose(file);
        }

        void push_back(const T &t) { insert(--end(), t); }
        void pop_back() { erase(--end()); }
        int size() const { return sz; }
         void clear() { while (size()>0) pop_back(); }

        const_iterator insert(const_iterator position, const T &t) {
            auto pos = position.nodeptr;
            int newnode = -1;
            if(freelist == -1) {
            newnode = 2*sizeof(int) + nodeSZ + sz*nodeSZ;
            } else {
                int newhead = readNext(freelist, file);
                newnode = freelist;
                freelist = newhead;
            }
            writeData(newnode, t, file);
            writePrev(newnode, readPrev(pos, file), file);
            writeNext(newnode, pos, file);

            writeNext(readPrev(newnode, file), newnode, file);
            writePrev(readNext(newnode, file), newnode, file);
            
            ++sz;
            updateSZ(sz);
            return const_iterator(newnode, file);
        }

        T operator[](int index) const{
            auto iter = begin();
            for(int i = 0; i < index; ++i) ++iter;
            return *iter;
        }
        const_iterator erase(const_iterator position) {
            auto pos = position.nodeptr;
            // - adjusting pointers
            writeNext(readPrev(pos, file), readNext(pos, file), file);
            writePrev(readNext(pos, file), readPrev(pos, file), file);

            // - adding pos to the freelist
            auto tmp = readNext(pos, file);
            writeNext(pos, freelist, file);
            freelist = pos;
            --sz;
            updateSZ(sz);

            return const_iterator(tmp, file);
        }
        void set(const T &value,int index);
        void set(const T &value,const_iterator position);

        const_iterator begin() {
            const_iterator iter(readNext(sentinel, file), file);
            return iter;
        }
        const_iterator begin() const {
            const_iterator iter(readNext(sentinel, file), file);
            return iter;
        }
        const_iterator end() {
            const_iterator iter(sentinel, file);
            return iter;
        }
        const_iterator end() const {
            const_iterator iter(sentinel, file);
            return iter;
        }
        const_iterator cbegin() const {
            const_iterator iter(readNext(sentinel, file), file);
            return iter;
        }
        const_iterator cend() const {
            const_iterator iter(sentinel, file);
            return iter;
        }
;};
