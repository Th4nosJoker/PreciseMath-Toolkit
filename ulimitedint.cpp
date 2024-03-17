/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

UnlimitedInt::UnlimitedInt(){
    size=0;
    sign=1;
    capacity=0;
    unlimited_int= nullptr;
}

UnlimitedInt::UnlimitedInt(string s){
    if (s[0]=='-'){
        //negative integer
        sign=-1;
        size=s.length()-1;
        capacity=s.length()-1;
        unlimited_int=new int[capacity];
        string substring=s.substr(1,s.size()-1);
        int j=0;
        for(char i:substring){
            int digit= i-'0';
            unlimited_int[j]=digit;
            j++;
        }
    }
    else if((s[0]=='0') && (s.length()==1)){
        // cout<<"yo"<<endl;
        sign=0;
        size=s.length();
        capacity=s.length();
        unlimited_int=new int[capacity];
        int j=0;
        for(char i:s){
            int digit= i-'0';
            unlimited_int[j]=digit;
            j++;
        }
    }
    else{
        //positive integer
        sign=1;
        size=s.length();
        capacity=s.length();
        unlimited_int=new int[capacity];
        
        int j=0;
        for(char i:s){
            int digit= i-'0';
            unlimited_int[j]=digit;
            j++;
        }
    }
}
UnlimitedInt::UnlimitedInt(int i){
    if(i<0){
        //negative number
        sign=-1;
        int a=i;
        string s=std::to_string(a);
        size=s.length()-1;
        capacity=s.length()-1;
        unlimited_int=new int[capacity];
        string substring=s.substr(1,s.size()-1);
        int j=0;
        for(char k:substring){
            int digit= k-'0';
            unlimited_int[j]=digit;
            j++;
        }
    }
    else if(i==0){
        sign=0;
        size=1;
        capacity=1;
        unlimited_int= new int[capacity];
        unlimited_int[0]=0;
    }
    else{
        //positive integer
        sign=1;
        string s=std::to_string(i);
        size=s.length();
        capacity=s.length();
        unlimited_int=new int[capacity];
        int j=0;
        for(char k:s){
            int digit= k-'0';
            unlimited_int[j]=digit;
            j++;
        }
        

    }
}
UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    
    capacity = cap;
    sign = sgn;
    size = sz;
    unlimited_int = new int[capacity];
    for (int i = 0; i < size; i++) {
        unlimited_int[i] = ulimited_int[i];
    }
    delete [] ulimited_int;
}

UnlimitedInt::~UnlimitedInt(){
    delete [] unlimited_int;
    size=0;
    capacity=0;
    sign=0;
}

int UnlimitedInt::get_size(){
    return size;
}

int* UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}
string UnlimitedInt::to_string(){
    if(sign==-1){
        string res;
        res.reserve(size*2);
        res.push_back('-');
        for(int i=0;i<size;i++){
            res.push_back(static_cast<char>('0'+unlimited_int[i]));
        }
        return res;
    }
    else if(sign==1){
        string res;
        res.reserve(size*2);
        for(int i=0;i<size;i++){
            res.push_back(static_cast<char>('0'+unlimited_int[i]));
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
UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    if(((i1->get_sign()) *(i2->get_sign()))==1){
        int max_capacity=max(i1->get_capacity(),i2->get_capacity());
        int* arr=new int[max_capacity+1]();
        int i=i1->get_size()-1;
        int j=i2->get_size()-1;
        int k=max_capacity;
        int carryon=0;
        while(i>=0 && j>=0){
            int sum=i1->unlimited_int[i]+i2->unlimited_int[j]+carryon;
            if( sum> 9){
                carryon=1;
                sum-=10;
                arr[k]=sum;
            }
            else{
                carryon=0;
                arr[k]=sum;
            }
            k--;
            i--;
            j--;
        }
        //anyone less than 0
        while(i>=0){
            int sum=i1->unlimited_int[i]+carryon;
            if( sum> 9){
                carryon=1;
                sum-=10;
                arr[k]=sum;
            }
            else{
                carryon=0;
                arr[k]=sum;
            }
            i--;
            k--;
        }
        while(j>=0){
            int sum=i2->unlimited_int[j]+carryon;
            if( sum> 9){
                carryon=1;
                sum-=10;
                arr[k]=sum;
            }
            else{
                carryon=0;
                arr[k]=sum;
            }
            j--;
            k--;
        }
        if(carryon==1){
            arr[k]=1;
            UnlimitedInt* i3=new UnlimitedInt;
            i3->size=max_capacity+1;
            i3->capacity=max_capacity+1;
            i3->unlimited_int=arr;
            arr=nullptr;
            if((i1->get_sign()==1) && (i2->get_sign()==1)){
                i3->sign=1;//positive
            }
            else{
                i3->sign=-1;//negative
            }
            return i3;
        }
        int newcapacity=max_capacity;
        int* arr1= new int[newcapacity];
        for(int i=0; i<newcapacity;i++){
            arr1[i]=arr[i+1];
        }
        delete []arr;
        UnlimitedInt* i3=new UnlimitedInt;
        i3->size=max_capacity;
        i3->capacity=max_capacity;
        i3->unlimited_int=arr1;
        arr1=nullptr;
        if((i1->get_sign()==1) && (i2->get_sign()==1)){
            i3->sign=1;//positive
        }
        else{
            i3->sign=-1;//negative
        }
        return i3;
        //no need to check leading zeroes here
    }
    else if(((i1->get_sign())*(i2->get_sign()))==-1){
        if(i1->get_size() > i2->get_size()){
            // i1>i2 in magnitude but -i1+ i2
            int resultcapacity= i1->get_size();
            int * result=new int[resultcapacity];

            int carry=0;

            int i=i1->size-1;
            int j=i2->size-1;
            int k=resultcapacity-1;

            while(i>=0 || j>=0){
                int numi1= (i>=0) ? i1->unlimited_int[i] : 0;
                int numi2= (j>=0) ? i2->unlimited_int[j] : 0;
            
                int sub = numi1 - numi2 -carry;
                if (sub < 0){
                    sub+=10;
                    carry = 1;

                }
                else{
                    carry=0;
                }

                result[k]=sub;

                i--;
                j--;
                k--;
            }

            //removing leading zeroes
            int l=0;
            while(l<resultcapacity-1){
                if(result[l]>0){
                    break;
                }
                l++;
            }
            //now l points to the first positive integer
            string newresult;

            if(i1->get_sign()==-1){
                newresult.push_back('-');
            }
            while(l<resultcapacity){
                newresult.push_back(static_cast<char>('0'+result[l]));
                l++;
            }
            UnlimitedInt* i3=new UnlimitedInt(newresult);
            delete [] result;
            return i3;
        }
        else if(i2->get_size()>i1->get_size()){
            int resultcapacity= i2->get_size();
            int * result=new int[resultcapacity]();

            int carry=0;

            int i=i2->size-1;
            int j=i1->size-1;
            int k=resultcapacity-1;

            while(i>=0 || j>=0){
                int numi2= (i>=0) ? i2->unlimited_int[i] : 0;
                int numi1= (j>=0) ? i1->unlimited_int[j] : 0;
            
                int sub = numi2 - numi1 -carry;
                if (sub < 0){
                    sub+=10;
                    carry = 1;

                }
                else{
                    carry=0;
                }

                result[k]=sub;

                i--;
                j--;
                k--;
            }

            //removing leading zeroes
            int l=0;
            while(l<resultcapacity-1){
                if(result[l]>0){
                    break;
                }
                l++;
            }
            //now l points to the first positive integer
            string newresult;
            if(i2->get_sign()==-1){
                newresult.push_back('-');
            }
            while(l<resultcapacity){
                newresult.push_back(static_cast<char>('0'+result[l]));
                l++;
            }
            UnlimitedInt* i3=new UnlimitedInt(newresult);
            delete [] result;
            return i3;
        }
        else if(i1->get_size()==i2->get_size()){
            //checking who is greater in magnitude
            int whogreater=0;
            int i=0;
            int j=0;
            while(i<i1->get_size() && j<i2->get_size()){
                if(i1->unlimited_int[i] > i2->unlimited_int[j]){
                    whogreater=1;
                    break;
                }
                else if(i1->unlimited_int[i] < i2->unlimited_int[j]){
                    whogreater=2;
                    break;
                }
                i++;
                j++;

            }
            if(whogreater==0){
                UnlimitedInt* i3=new UnlimitedInt("0");
                return i3;
            }

            else if(whogreater==1){
                int resultcapacity= i1->get_size();
                int * result=new int[resultcapacity];

                int carry=0;

                int i=i1->size-1;
                int j=i2->size-1;
                int k=resultcapacity-1;

                while(i>=0 || j>=0){
                    int numi1= (i>=0) ? i1->unlimited_int[i] : 0;
                    int numi2= (j>=0) ? i2->unlimited_int[j] : 0;
            
                    int sub = numi1 - numi2 -carry;
                    if (sub < 0){
                        sub+=10;
                        carry = 1;

                    }
                    else{
                        carry=0;
                    }

                    result[k]=sub;

                    i--;
                    j--;
                    k--;
                }

                //removing leading zeroes
                int l=0;
                while(l<resultcapacity-1){
                    if(result[l]>0){
                        break;
                    }
                    l++;
                }
                //now l points to the first positive integer
                string newresult;
                if(i1->get_sign()==-1){
                    newresult.push_back('-');
                }
                while(l<resultcapacity){
                    newresult.push_back(static_cast<char>('0'+result[l]));
                    l++;
                }
                UnlimitedInt* i3=new UnlimitedInt(newresult);
                delete [] result;
                return i3;
            }
            else if(whogreater==2){
                int resultcapacity= i2->get_size();
                int * result=new int[resultcapacity];

                int carry=0;

                int i=i2->size-1;
                int j=i1->size-1;
                int k=resultcapacity-1;

                while(i>=0 || j>=0){
                    int numi2= (i>=0) ? i2->unlimited_int[i] : 0;
                    int numi1= (j>=0) ? i1->unlimited_int[j] : 0;
            
                    int sub = numi2 - numi1 -carry;
                    if (sub < 0){
                        sub+=10;
                        carry = 1;

                    }
                    else{
                        carry=0;
                    }

                    result[k]=sub;

                    i--;
                    j--;
                    k--;
                }

                //removing leading zeroes
                int l=0;
                while(l<resultcapacity-1){
                    if(result[l]>0){
                        break;
                    }
                    l++;
                }
                //now l points to the first positive integer
                string newresult;
                if(i2->get_sign()==-1){
                    newresult.push_back('-');
                }
                while(l<resultcapacity){
                    newresult.push_back(static_cast<char>('0'+result[l]));
                    l++;
                }
                UnlimitedInt* i3=new UnlimitedInt(newresult);
                delete [] result;
                return i3;
            }
        }
    }
    else if((i1->get_sign())*(i2->get_sign())== 0){
        if(i1->get_sign()==0){
            return i2;
        }
        return i1;
    }

}
//done

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    if((i1->get_sign())*(i2->get_sign())==-1){
        int max_capacity=max(i1->get_capacity(),i2->get_capacity());
        int* arr=new int[max_capacity+1];
        int i=i1->size-1;
        int j=i2->size-1;
        int k=max_capacity;
        int carryon=0;
        while(i>=0 && j>=0){
            int sum=i1->unlimited_int[i]+i2->unlimited_int[j]+carryon;
            if( sum> 9){
                carryon=1;
                sum-=10;
                arr[k]=sum;
            }
            else{
                carryon=0;
                arr[k]=sum;
            }
            k--;
            i--;
            j--;
        }
        //anyone less than 0
        while(i>=0){
            int sum=i1->unlimited_int[i]+carryon;
            if( sum> 9){
                carryon=1;
                sum-=10;
                arr[k]=sum;
            }
            else{
                carryon=0;
                arr[k]=sum;
            }
            i--;
            k--;
        }
        while(j>=0){
            int sum=i2->unlimited_int[j]+carryon;
            if( sum> 9){
                carryon=1;
                sum-=10;
                arr[k]=sum;
            }
            else{
                carryon=0;
                arr[k]=sum;
            }
            j--;
            k--;
        }
        if(carryon==1){
            arr[k]=1;
            UnlimitedInt* i3=new UnlimitedInt;
            i3->size=max_capacity+1;
            i3->capacity=max_capacity+1;
            i3->unlimited_int=arr;
            arr=nullptr;
            if((i1->get_sign()==1) && (i2->get_sign()==-1)){
                i3->sign=1;//positive
            }
            else{
                i3->sign=-1;//negative
            }
            return i3;
        }
        int newcapacity=max_capacity;
        int* arr1= new int[newcapacity];
        for(int i=0; i<newcapacity;i++){
            arr1[i]=arr[i+1];
        }
        delete [] arr;
        UnlimitedInt* i3=new UnlimitedInt;
        i3->size=max_capacity;
        i3->capacity=max_capacity;
        i3->unlimited_int=arr1;
        arr1=nullptr;
        if(i1->get_sign()==1 && (i2->get_sign()==-1)){
            i3->sign=1;//negative
        }
        else{
            i3->sign=-1;//positive
        }
        return i3;
        //no need to check leading zeroes here
    }
    else if((i1->get_sign())*(i2->get_sign())==1){
        if(i1->get_size() > i2->get_size()){
            int resultcapacity= i1->get_size();
            int * result=new int[resultcapacity];

            int carry=0;

            int i=i1->size-1;
            int j=i2->size-1;
            int k=resultcapacity-1;

            while(i>=0 || j>=0){
                int numi1= (i>=0) ? i1->unlimited_int[i] : 0;
                int numi2= (j>=0) ? i2->unlimited_int[j] : 0;
            
                int sub = numi1 - numi2 -carry;
                if (sub < 0){
                    sub+=10;
                    carry = 1;

                }
                else{
                    carry=0;
                }

                result[k]=sub;

                i--;
                j--;
                k--;
            }

            //removing leading zeroes
            int l=0;
            while(l<resultcapacity-1){
                if(result[l]>0){
                    break;
                }
                l++;
            }
            //now l points to the first positive integer
            string newresult;

            if(i1->get_sign()==-1){
                newresult.push_back('-');
            }
            while(l<resultcapacity){
                newresult.push_back(static_cast<char>('0'+result[l]));
                l++;
            }
            UnlimitedInt* i3=new UnlimitedInt(newresult);
            delete [] result;
            return i3;
        }
        else if(i1->get_size() < i2->get_size()){
            int resultcapacity= i2->get_size();
            int * result=new int[resultcapacity];

            int carry=0;

            int i=i2->size-1;
            int j=i1->size-1;
            int k=resultcapacity-1;

            while(i>=0 || j>=0){
                int numi2= (i>=0) ? i2->unlimited_int[i] : 0;
                int numi1= (j>=0) ? i1->unlimited_int[j] : 0;
            
                int sub = numi2 - numi1 -carry;
                if (sub < 0){
                    sub+=10;
                    carry = 1;

                }
                else{
                    carry=0;
                }

                result[k]=sub;

                i--;
                j--;
                k--;
            }

            //removing leading zeroes
            int l=0;
            while(l<resultcapacity-1){
                if(result[l]>0){
                    break;
                }
                l++;
            }
            //now l points to the first positive integer
            string newresult;
            if(i2->get_sign()==1){
                newresult.push_back('-');
            }
            while(l<resultcapacity){
                newresult.push_back(static_cast<char>('0'+result[l]));
                l++;
            }
            UnlimitedInt* i3=new UnlimitedInt(newresult);
            delete [] result;
            return i3;
        }
        else{
            int whogreater=0;
            int i=0;
            int j=0;
            while(i<i1->get_size() && j<i2->get_size()){
                if(i1->unlimited_int[i] > i2->unlimited_int[j]){
                    whogreater=1;
                    break;
                }
                else if(i1->unlimited_int[i] < i2->unlimited_int[j]){
                    whogreater=2;
                    break;
                }
                i++;
                j++;

            }
            if(whogreater==0){
                UnlimitedInt* i3=new UnlimitedInt("0");
                return i3;
            }

            else if(whogreater==1){
                int resultcapacity= i1->get_size();
                int * result=new int[resultcapacity];

                int carry=0;

                int i=i1->size-1;
                int j=i2->size-1;
                int k=resultcapacity-1;

                while(i>=0 || j>=0){
                    int numi1= (i>=0) ? i1->unlimited_int[i] : 0;
                    int numi2= (j>=0) ? i2->unlimited_int[j] : 0;
            
                    int sub = numi1 - numi2 -carry;
                    if (sub < 0){
                        sub+=10;
                        carry = 1;

                    }
                    else{
                        carry=0;
                    }

                    result[k]=sub;

                    i--;
                    j--;
                    k--;
                }

                //removing leading zeroes
                int l=0;
                while(l<resultcapacity-1){
                    if(result[l]>0){
                        break;
                    }
                    l++;
                }
                //now l points to the first positive integer
                string newresult;
                if(i1->get_sign()==-1){
                    newresult.push_back('-');
                }
                while(l<resultcapacity){
                    newresult.push_back(static_cast<char>('0'+result[l]));
                    l++;
                }
                UnlimitedInt* i3=new UnlimitedInt(newresult);
                delete [] result;
                return i3;
            }
            else if(whogreater==2){
                int resultcapacity= i2->get_size();
                int * result=new int[resultcapacity];

                int carry=0;

                int i=i2->size-1;
                int j=i1->size-1;
                int k=resultcapacity-1;

                while(i>=0 || j>=0){
                    int numi2= (i>=0) ? i2->unlimited_int[i] : 0;
                    int numi1= (j>=0) ? i1->unlimited_int[j] : 0;
            
                    int sub = numi2 - numi1 -carry;
                    if (sub < 0){
                        sub+=10;
                        carry = 1;

                    }
                    else{
                        carry=0;
                    }

                    result[k]=sub;

                    i--;
                    j--;
                    k--;
                }

                //removing leading zeroes
                int l=0;
                while(l<resultcapacity-1){
                    if(result[l]>0){
                        break;
                    }
                    l++;
                }
                //now l points to the first positive integer
                string newresult;
                if(i2->get_sign()==1){
                    newresult.push_back('-');
                }
                while(l<resultcapacity){
                    newresult.push_back(static_cast<char>('0'+result[l]));
                    l++;
                }
                UnlimitedInt* i3=new UnlimitedInt(newresult);
                delete [] result;
                return i3;
            }
        }
            
        
    }   
    else if(((i1->get_sign())*(i2->get_sign()))== 0){
        if(i1->get_sign()==0){
            i2->sign=-1*(i2->get_sign());
            return i2;
        }
        return i1;
    }
}
//done
    
UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    int intialsize=i1->get_size()+i2->get_size();
    int* result= new int[intialsize]();
    int size1=i1->get_size();
    int size2=i2->get_size();


    for(int i=size1-1;i>=0;i--){
        for(int j=size2-1;j>=0;j--){
            int product=i1->unlimited_int[i] * i2->unlimited_int[j];
            int p1=i+j;
            int p2=i+j+1;

            int sum=product+result[p2];

            result[p1]+=sum/10;//carryon
            result[p2]= sum%10;//remainder
        }
    }

    int k=0;//to find the first positive number in result;
    while(result[k]==0 && k<intialsize-1){
        k++;
    }
    //now the k value points to the first value that is non zero
    int newsize=intialsize - k ;
    int* arr=new int[newsize];
    int l=0;
    while(k<intialsize && l<newsize){
        arr[l]=result[k];
        k++;
        l++;
    }
    //now done
    delete [] result;
    // int sign=0;
    if(newsize==1 && arr[0]==0){
        UnlimitedInt* i3=new UnlimitedInt(arr,newsize,0,newsize);
        return i3;
    }
    else if((i1->sign) * (i2->sign) == 1){
        UnlimitedInt* i3=new UnlimitedInt(arr,newsize,1,newsize);
        return i3;
    }
    UnlimitedInt* i3=new UnlimitedInt(arr,newsize,-1,newsize);
    return i3;
    
    

    
}
//done

string moddedstring(string a){
    
    if(a[0]=='-'){
        string substring=a.substr(1,a.size()-1);
        return substring;
    }
    else{
        return a;
    }
}

int compare(string remainder, string divisor){
    if(remainder.size() != divisor.size()){
        return (remainder.size() > divisor.size()) ? 1 : -1;
    }
    for(int i = 0;i<remainder.size();i++){
        if(remainder[i]!= divisor[i]){
            return (remainder[i] > divisor[i]) ? 1 : -1;
        }
    }

    return 0;

}
UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    string quotient="";
    string remainder="";
    string stringi1=i1->to_string();
    string stringi2=i2->to_string();
    string moddedi1=moddedstring(stringi1);
    string moddedi2=moddedstring(stringi2);
    UnlimitedInt* i1clone= new UnlimitedInt(moddedi1);
    UnlimitedInt* i2clone= new UnlimitedInt(moddedi2);
    int q=0;
    for(int i=0; i<i1clone->get_size();i++){
        remainder.push_back(static_cast<char>('0'+i1clone->unlimited_int[i]));
        q=0;
        
        while(compare(remainder, i2clone->to_string()) >=0){
            UnlimitedInt* remainderint=new UnlimitedInt(remainder);
            remainder= UnlimitedInt::sub(remainderint,i2clone)->to_string();
            //we need to remove leading zeroes from the remainder
            int l=0;
            while(l<remainder.size()){
                if(remainder[l]!='0'){
                    break;
                }
                l++;
            }
            //now l points to the first positive integer in remainder
            if(l==remainder.size()){
                remainder="";
            }
            else{
                string subremainder = remainder.substr(l,remainder.size()-l);
                remainder=subremainder;
            }
            q++;
            delete remainderint;
        }

        if(remainder=="0"){
            remainder.pop_back();
        }
        quotient.push_back(static_cast<char>('0'+ q ));
    }
    
    int l=0;
    while(l<quotient.size()-1){
        if(quotient[l]!='0'){
            break;
        }
        l++;
    }
    string newquotient= quotient.substr(l,quotient.size()-l);
    quotient=newquotient;//quotient with no leading zeroes
    // cout<<"remainder "<<remainder<<endl;
    // cout<<"quotient "<<quotient<<endl;
    // cout<<"l value "<<l<<endl;
    if(remainder==""){
        if((i1->get_sign())*(i2->get_sign()) == 1){
            //positive should be returned
            UnlimitedInt* finalquotientans= new UnlimitedInt(quotient);
            delete i1clone;
            delete i2clone;
            return finalquotientans;
        }
        else{
            //negative should be returned
            if(quotient=="0"){
                UnlimitedInt* finalquotientans= new UnlimitedInt(quotient);
                delete i1clone;
                delete i2clone;
                return finalquotientans;
            }
            string negquotient="-";
            for(int j=0;j<quotient.size();j++){
                negquotient.push_back(quotient[j]);
            }
            UnlimitedInt* finalquotientans= new UnlimitedInt(negquotient);
            delete i1clone;
            delete i2clone;
            return finalquotientans;
        }
    }
    else{
        if((i1->get_sign())*(i2->get_sign()) == 1){
            //positive should be returned
            UnlimitedInt* finalquotientans= new UnlimitedInt(quotient);
            delete i1clone;
            delete i2clone;
            return finalquotientans;

        }

        else{
            //negative value to be returned
            string negquotient="-";
            for(int j=0;j<quotient.size();j++){
                negquotient.push_back(quotient[j]);
            }
            UnlimitedInt* quotientint= new UnlimitedInt(negquotient);
            UnlimitedInt* one=new UnlimitedInt("1");
            UnlimitedInt* newquotientint= UnlimitedInt::sub(quotientint,one);
            delete i1clone;
            delete i2clone;
            delete quotientint;
            delete one;
            return newquotientint;
        }


    }
    
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* floordivision = UnlimitedInt::div(i1,i2);
    UnlimitedInt* multiply= UnlimitedInt::mul(i2,floordivision);
    UnlimitedInt* subtract=UnlimitedInt::sub(i1,multiply);

    return subtract;
}


// int main(){
//     UnlimitedInt* i1=new UnlimitedInt("-20034");
//     UnlimitedInt* i2=new UnlimitedInt("-10");
//     UnlimitedInt* i3=UnlimitedInt::mod(i1,i2);
//     cout<<"i1 value "<<i1->to_string()<<endl;
//     cout<<"i2 value "<<i2->to_string()<<endl;
//     std::cout<<"i3 value "<<i3->to_string()<<endl;
//     cout<<"i3 sign "<<i3->get_sign()<<endl;
//     delete i3;
//     delete i1;
//     delete i2;
//     return 0;
// }
