#include<iostream>
using namespace std;

int main(){
        int x;
        cout<<"give number" ;
        cin>>x;
        int reverse=0 ;
        int n;
        
    if(x%10==0)
    {
            int n=(x/10);
        if(n>0)
        {
            while(n>0){
        reverse=n%10+reverse*10;
        n=n/10; }
        cout<<reverse;
         }
    else if(n<0)
    {
        n=abs(n);
        while(n>0){
        reverse=n%10+reverse*10;
        n=n/10; }

    reverse=-reverse;
    cout<<reverse;
        
    }
    }

else
{ int n=x;
        if(n>0)
        {
            while(n>0){
        reverse=n%10+reverse*10;
        n=n/10;};
        cout<<reverse;
        }
    
    else if(n<0)
     {
        n=abs(n);
        while(n>0){
        reverse=n%10+reverse*10;
        n=n/10; };

    reverse=-reverse;
    cout<<reverse;
        
    }
};
    return 0;
}