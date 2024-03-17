/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
// #include <iostream>

using namespace std;
Evaluator::Evaluator(){
    symtable=new SymbolTable;
}

Evaluator::~Evaluator(){
    delete symtable;
    for(ExprTreeNode* i:expr_trees){
        delete i;
    }
}


bool numberchecker(string input){
    bool check=true;
    for(char c:input){
        if(std::isdigit(c)==false){
            check=false;
            break;
        }
    }
    return check;
}


void Evaluator::parse(vector<string> code){
    //v = ( ( ( 2 + 3 ) * ( 7 - 5 ) ) - ( 3 / 1 ) )

    vector <ExprTreeNode*> stack;
    UnlimitedInt* zero= new UnlimitedInt("0");//default shit
    ExprTreeNode* first=new ExprTreeNode(code[0],zero);
    ExprTreeNode* second=new ExprTreeNode(code[1],zero);

    // std::cout<<"parse tree started"<<endl;
    for(int i=2;i<code.size();i++){
        // cout<<"inside for loop"<<endl;
        if(code[i]==")"){
            //pop 3 elements blah blah blah
            // cout<<"inside if "<<endl;
            // cout<<"checking out "<<code[i]<<endl;

            ExprTreeNode* rightnode=stack.back();
            stack.pop_back();
            ExprTreeNode* middlenode=stack.back();
            stack.pop_back();
            ExprTreeNode* leftnode=stack.back();
            stack.pop_back();

            //calculate the evaluated_value
            UnlimitedRational* leftnodeval=leftnode->evaluated_value;
            UnlimitedRational* rightnodeval=rightnode->evaluated_value;
            if(middlenode->type=="ADD"){
                middlenode->evaluated_value=UnlimitedRational::add(leftnodeval,rightnodeval);
            }
            else if(middlenode->type=="SUB"){
                middlenode->evaluated_value=UnlimitedRational::sub(leftnodeval,rightnodeval);
            }
            else if(middlenode->type=="MUL"){
                middlenode->evaluated_value=UnlimitedRational::mul(leftnodeval,rightnodeval);
            }
            else if(middlenode->type=="DIV"){
                middlenode->evaluated_value=UnlimitedRational::div(leftnodeval,rightnodeval);
            }
            middlenode->right=rightnode;
            middlenode->left=leftnode;
            stack.push_back(middlenode);

        }

        else if(code[i]!="("){
            // cout<<"inside else if"<<endl;
            if(numberchecker(code[i])==true){//number hai bc
                // cout<<"checking out "<<code[i]<<endl;
                UnlimitedInt* number=new UnlimitedInt(code[i]);
                ExprTreeNode* toinsert=new ExprTreeNode(code[i],number);
                stack.push_back(toinsert);
            }
            else if(code[i]=="+"){
                // cout<<"checking out "<<code[i]<<endl;
                ExprTreeNode* toinsert=new ExprTreeNode(code[i],zero);
                stack.push_back(toinsert);
            }
            else if(code[i]=="-"){
                ExprTreeNode* toinsert=new ExprTreeNode(code[i],zero);
                stack.push_back(toinsert);
            }
            else if(code[i]=="*"){
                ExprTreeNode* toinsert=new ExprTreeNode(code[i],zero);
                stack.push_back(toinsert);
            }
            else if(code[i]=="/"){
                // cout<<"checking out "<<code[i]<<endl;
                ExprTreeNode* toinsert=new ExprTreeNode(code[i],zero);
                stack.push_back(toinsert);
            }
            else if(code[i]=="%"){
                ExprTreeNode* toinsert=new ExprTreeNode(code[i],zero);
                stack.push_back(toinsert);
            }
            else{//bc sirf variable baki hai, aur woh variable hun jo already simptable mein hai
                UnlimitedRational* variable_value=symtable->search(code[i]);
                ExprTreeNode* toinsert=new ExprTreeNode(code[i],variable_value);//using the unlimitedrational input
                stack.push_back(toinsert);
            }
        }
    }
    // cout<<"stack size "<<stack.size()<<endl;
    //now stack has only one element
    ExprTreeNode* finalright=stack.back();
    stack.pop_back();
    second->id=first->id;
    second->evaluated_value=finalright->evaluated_value;
    second->right=finalright;
    second->left=first;
    expr_trees.push_back(second);//exprtree mein push kiya
    // std::cout<<"parse tree ended"<<endl;

}

void Evaluator::eval(){
    symtable->insert(expr_trees.back()->id,expr_trees.back()->evaluated_value);
    //populated the fucking simptable

}

// int main(){
//     vector <string> code1={"v",":=","(","13","+","(","2","/","(","3","-","3",")",")",")"};
//     Evaluator E1;
//     E1.parse(code1);
//     E1.eval();
//     UnlimitedRational* i1 = E1.symtable->search("v");
//     std::cout<<"done"<<endl;
//     cout<<i1->get_frac_str()<<endl;

// }