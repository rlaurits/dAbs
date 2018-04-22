


iterator erase(const_iterator position);

int erase(const key_type &k) {
    const_iterator iter = find(k);
    if(iter == cend()) return 0;    //if key cannot be found, don't try to erase anything
    erase(iter);
    return 1;
}

mapped_type &operator[](const K &key) {
    (insert(make_pair(key, V())).first).second     //gives a default value of type V
    // - .first gives the iterator of the (iterator, bool) result
    // - .second gives just the value of the (key, val) pair iterator points to

}


HashMap(const Hash &hf) :hashFunction{ hf } {}  //copying the hashFunction at top of file
