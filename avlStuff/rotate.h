
void rotateLeft(Node *nd) {
    Node *ultraParent = nd-> parent;
    ultraParent-> right = nd-> right;
    nd-> parent = nd-> right;
    nd-> right = nd-> parent.left;
    nd-> right.parent = nd;
    nd-> parent.left = nd;
    nd-> parent.parent = ultraParent;
}

void rotateRight(Node *nd) {
    Node *ultraParent = nd-> parent;
    ultraParent-> left = nd-> left;
    nd-> parent = nd-> left;
    nd-> left = nd-> parent.right;
    nd-> left.parent = nd;
    nd-> parent.right = nd;
    nd-> parent.parent = ultraParent;
}

void updateHeight(Node *nd) {
    if(nd-> left == nullptr && nd-> right == nullptr) {
        nd.height = 1;
    } else if(nd.right == nullptr) {
        nd.height = nd.left-> height + 1;
    } else if(nd.left == nullptr) {
        nd.height = nd.right-> height +1;
    } else {
        nd.height = max(left.height, right.height) + 1
    }
}
void updateAllHeights(Node *pos) {
    while(pos != nullptr) {     
        Node *tmp = pos;
        updateHeight(pos);
        pos = pos-> parent;
        if(pos-> height == tmp-> height) {
            pos = nullptr;
        }
    }
}    
//this was my attempt to actually do it recursively
void updateHeights(Node *nd) {
    if(nd-> parent-> left == nd && nd-> parent-> right == nullptr) {
        parent-> height = nd-> height + 1;
    } else if(nd-> parent-> right == nd && nd-> parent-> left == nullptr {
        parent-> height = nd-> height + 1;
    } else {
        nd-> parent-> height = max(nd-> parent-> left-> height, nd-> parent-> right-> height) + 1;
    }
    if(nd-> parent-> parent != nullptr) {
        updateHeights(nd-> parent);
    }
}
        
//this is supposed to contain both the checking of heights and the balancing of them
void balance(Node *pos) {
    while(pos != nullptr) {
        int diff = pos-> left-> height - pos-> right-> height;
        if(diff < 0) diff = diff*(-1);
        if(diff == 0 || diff == 1) break;
        if(pos-> left-> height > pos-> right-> height) {
            
            
        

