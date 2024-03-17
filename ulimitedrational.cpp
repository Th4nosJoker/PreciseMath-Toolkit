/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"


UnlimitedRational::UnlimitedRational(){
    p=new UnlimitedInt;
    q=new UnlimitedInt;
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    int * parr= new int[num->get_size()];
    for(int i=0; i < num->get_size();i++){
        parr[i]=num->get_array()[i];
    }
    p=new UnlimitedInt(parr,num->get_capacity(),num->get_sign(),num->get_size());
    int * qarr= new int[den->get_size()];
    for(int i=0; i < den->get_size();i++){
        qarr[i]=den->get_array()[i];
    }
    q=new UnlimitedInt(qarr,den->get_capacity(),den->get_sign(),den->get_size());
    
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    if(p->get_sign()==-1){
        string res;
        int size=p->get_size();
        res.reserve(size*2);
        res.push_back('-');
        int * arr=p->get_array();
        for(int i=0;i<size;i++){
            res.push_back(static_cast<char>('0'+arr[i]));
        }
        return res;
    }
    else if(p->get_sign()==1){
        string res;
        int size=p->get_size();
        res.reserve(size*2);
        int * arr=p->get_array();
        for(int i=0;i<size;i++){
            res.push_back(static_cast<char>('0'+ arr[i]));
        }
        return res;
    }
    else{
        //its 0
        string res;
        res.push_back('0');
        return res;
    }
}

string UnlimitedRational::get_q_str(){
    if(q->get_sign()==-1){
        string res;
        int size=q->get_size();
        res.reserve(size*2);
        res.push_back('-');
        int * arr=q->get_array();
        for(int i=0;i<size;i++){
            res.push_back(static_cast<char>('0'+arr[i]));
        }
        return res;
    }
    else if(q->get_sign()==1){
        string res;
        int size=q->get_size();
        res.reserve(size*2);
        int * arr=q->get_array();
        for(int i=0;i<size;i++){
            res.push_back(static_cast<char>('0'+arr[i]));
        }
        return res;
    }
    else{
        //its 0
        string res;
        res.push_back('0');
        return res;
    }
}

string UnlimitedRational::get_frac_str(){
    string pstring=get_p_str();
    string qstring=get_q_str();
    pstring.push_back('/');
    for(int i=0;i<qstring.size();i++){
        pstring.push_back(qstring[i]);
    }
    return pstring;
}


string moddedstringrat(string a){
    
    if(a[0]=='-'){
        string substring=a.substr(1,a.size()-1);
        return substring;
    }
    else{
        return a;
    }
}

UnlimitedInt* gcd(UnlimitedInt* a, UnlimitedInt* b){
    string stringa=a->to_string();
    string stringb=b->to_string();
    string moddeda=moddedstringrat(stringa);
    string moddedb=moddedstringrat(stringb);
    UnlimitedInt* aclone= new UnlimitedInt(moddeda);
    UnlimitedInt* bclone= new UnlimitedInt(moddedb);
    string bstring=bclone->to_string();
    while(bstring!="0"){
        UnlimitedInt* c=aclone;
        UnlimitedInt* temp=bclone;
        bclone= UnlimitedInt::mod(aclone,bclone);
        aclone=temp;
        bstring=bclone->to_string();
        // delete c;
        // temp=nullptr;
    }
    UnlimitedInt* ans= new UnlimitedInt(aclone->to_string());
    delete aclone;
    delete bclone;
    return ans;
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    if(i1->get_q_str()=="0" || i2->get_q_str()=="0"){
        UnlimitedInt* numerator= new UnlimitedInt("0");
        UnlimitedInt* denominator= new UnlimitedInt("0");
        UnlimitedRational* result= new UnlimitedRational(numerator,denominator);
        delete numerator;
        delete denominator;
        return result;
    }
    else{
        UnlimitedInt* p1=UnlimitedInt::mul(i1->p,i2->q);
        UnlimitedInt* p2=UnlimitedInt::mul(i2->p,i1->q);
        UnlimitedInt* q1=UnlimitedInt::mul(i1->q,i2->q);

        UnlimitedInt* num=UnlimitedInt::add(p1,p2);

        UnlimitedInt* gcdbro= gcd(num,q1);

        UnlimitedInt* num1=UnlimitedInt::div(num,gcdbro);
        UnlimitedInt* den1=UnlimitedInt::div(q1,gcdbro);

        UnlimitedRational* result=new UnlimitedRational(num1,den1);

        return result;
        
    }

}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    if(i1->get_q_str()=="0" || i2->get_q_str()=="0"){
        UnlimitedInt* numerator= new UnlimitedInt("0");
        UnlimitedInt* denominator= new UnlimitedInt("0");
        UnlimitedRational* result= new UnlimitedRational(numerator,denominator);
        delete numerator;
        delete denominator;
        return result;
    }
    else{
        UnlimitedInt* p1=UnlimitedInt::mul(i1->p,i2->q);
        UnlimitedInt* p2=UnlimitedInt::mul(i2->p,i1->q);
        UnlimitedInt* q1=UnlimitedInt::mul(i1->q,i2->q);

        UnlimitedInt* num=UnlimitedInt::sub(p1,p2);

        UnlimitedInt* gcdbro= gcd(num,q1);

        UnlimitedInt* num1=UnlimitedInt::div(num,gcdbro);
        UnlimitedInt* den1=UnlimitedInt::div(q1,gcdbro);

        UnlimitedRational* result=new UnlimitedRational(num1,den1);

        return result;
    }
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    if(i1->get_q_str()=="0" || i2->get_q_str()=="0"){
        UnlimitedInt* numerator= new UnlimitedInt("0");
        UnlimitedInt* denominator= new UnlimitedInt("0");
        UnlimitedRational* result= new UnlimitedRational(numerator,denominator);
        delete numerator;
        delete denominator;
        return result;
    }
    else{
        UnlimitedInt* p1=UnlimitedInt::mul(i1->p,i2->p);
        UnlimitedInt* p2=UnlimitedInt::mul(i1->q,i2->q);

        UnlimitedInt* gcdbro=gcd(p1,p2);

        UnlimitedInt* num=UnlimitedInt::div(p1,gcdbro);
        UnlimitedInt* den=UnlimitedInt::div(p2,gcdbro);

        UnlimitedRational* result=new UnlimitedRational(num,den);

        return result;
    }
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    if(i1->get_q_str()=="0" || i2->get_q_str()=="0"){
        UnlimitedInt* numerator= new UnlimitedInt("0");
        UnlimitedInt* denominator= new UnlimitedInt("0");
        UnlimitedRational* result= new UnlimitedRational(numerator,denominator);
        delete numerator;
        delete denominator;
        return result;
    }
    else{
        UnlimitedInt* p1=UnlimitedInt::mul(i1->p,i2->q);
        UnlimitedInt* p2=UnlimitedInt::mul(i1->q,i2->p);

        UnlimitedInt* gcdbro=gcd(p1,p2);

        UnlimitedInt* num=UnlimitedInt::div(p1,gcdbro);
        UnlimitedInt* den=UnlimitedInt::div(p2,gcdbro);

        UnlimitedRational* result=new UnlimitedRational(num,den);

        return result;
    }
}

// int main(){
//     UnlimitedInt* a=new UnlimitedInt("-10");
//     UnlimitedInt* b=new UnlimitedInt("-5");

//     UnlimitedInt* r3=gcd(a,b);
// //     UnlimitedRational* r1= new UnlimitedRational(a,b);

// //     UnlimitedInt* c=new UnlimitedInt("10");
// //     UnlimitedInt* d=new UnlimitedInt("7");

// //     UnlimitedRational* r2=new UnlimitedRational(c,d);

// //     UnlimitedRational* r3= UnlimitedRational::sub(r1,r2);

//     string ans= r3->to_string();

//     std::cout<<ans<<std::endl;

//     return 0;
// }