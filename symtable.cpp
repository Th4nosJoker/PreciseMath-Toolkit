/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

void destroySymbolTable(SymEntry* &node){
    if(node){
        destroySymbolTable(node->left);
        destroySymbolTable(node->right);
        delete node;
        node=nullptr;
    }
}

SymbolTable::SymbolTable(){
    size=0;
    root=new SymEntry;    
}

SymbolTable::~SymbolTable(){
    size=0;
    destroySymbolTable(root);
}

void SymbolTable::insert(string k, UnlimitedRational* v){
    if(root->key==""){
        //its empty so this is the first value
        root->key=k;
        root->val=v;
    }
    SymEntry* curr=root;
    SymEntry* prev=nullptr;
    while(curr!=nullptr){
        if(k<curr->key){
            prev=curr;
            curr=curr->left;
        }
        else{
            prev=curr;
            curr=curr->right;
        }
    }
    //curr==nullptr
    //we need to insert at prev
    SymEntry* temp=new SymEntry(k,v);
    size++;
    if(k<prev->key){
        prev->left=temp;
    }
    else if(k>prev->key){
        prev->right=temp;
    }
}

void SymbolTable::remove(string k){
    //first we find
    SymEntry* curr=root;
    SymEntry* prev=nullptr;
    while(curr->key!=k){
        if(k<curr->key){
            prev=curr;
            curr=curr->left;
        }
        else{
            prev=curr;
            curr=curr->right;
        }
    }
    //now curr points to the key
    //case 1: if curr is a leaf node
    if(curr->right==nullptr && curr->left==nullptr){
        delete curr;
        size--;
        return;
    }

    //case 2: if curr has only one child
    //left child exists
    else if(curr->right==nullptr && curr->left!=nullptr){
        if(prev->right==curr){
            prev->right=curr->left;
            delete curr;
            size--;
            return;
        }
        else{
            prev->left=curr->left;
            delete curr;
            size--;
            return;
        }
    }
    //right child exists
    else if(curr->left==nullptr && curr->right!=nullptr){
        if(prev->right==curr){
            prev->right=curr->right;
            delete curr;
            size--;
            return;
        }
        else{
            prev->left=curr->right;
            delete curr;
            size--;
            return;
        }
    }

    //case 3: if curr has two childs
    //need to do recursion
    else{
        SymEntry* pred=curr->left;
        while(pred->right!=nullptr){
            pred=pred->right;
        }
        string backupkey=curr->key;
        UnlimitedRational* backupval=curr->val;
        curr->key=pred->key;
        curr->val=pred->val;
        pred->key=backupkey;
        pred->val=backupval;
        SymbolTable::remove(pred->key);
    }
    return;
}

UnlimitedRational* SymbolTable::search(string k){
    SymEntry* curr=root;
    while(curr->key!=k && curr!=nullptr){
        if(k<curr->key){
            curr=curr->left;
        }
        else{
            curr=curr->right;
        }
    }
    //now curr points to the right key
    if(curr==nullptr){
        return nullptr;
    }
    return curr->val;
}

int SymbolTable::get_size(){
    return size;
}

SymEntry* SymbolTable::get_root(){
    return root;
}