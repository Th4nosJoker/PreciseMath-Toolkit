/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    type="";
    id="";
    left=nullptr;
    right=nullptr;
}

ExprTreeNode::~ExprTreeNode(){
    type="";
    id="";
    delete val;
    delete evaluated_value;
    left=nullptr;
    right=nullptr;

}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    if(t==":="){
        type="EQUALTO";
        id="";
        left=nullptr;
        right=nullptr;
    }
    else if(t=="+"){
        type="ADD";
        id="";
        left=nullptr;
        right=nullptr;
    }
    else if(t=="-"){
        type="SUB";
        id="";
        left=nullptr;
        right=nullptr;
    }
    else if(t=="*"){
        type="MUL";
        id="";
        left=nullptr;
        right=nullptr;
    }
    else if(t=="/"){
        type="DIV";
        id="";
        left=nullptr;
        right=nullptr;
    }
    else if(t=="%"){
        type="MOD";
        id="";
        left=nullptr;
        right=nullptr;
    }
    else{
        bool flag=true;
        for(char c:t){
            if(std::isdigit(c)==false){
                flag=false;
                break;
            }
        }
        if(flag==true){//matlab ek number hai apun
            type="VAL";
            UnlimitedInt* one = new UnlimitedInt("1");
            UnlimitedRational* iskavalue= new UnlimitedRational(v,one);
            val=iskavalue;
            evaluated_value=iskavalue;
            id="";
            left=nullptr;
            right=nullptr;
        }
        else if(flag==false){//apun ek variable hai bc
            type="VAR";
            id=t;
            left=nullptr;
            right=nullptr;
        }
    }
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    val=v;
    evaluated_value=v;
    id=t;
    type="VAR";
    left=nullptr;
    right=nullptr;
}