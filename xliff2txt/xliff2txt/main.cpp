#include <iostream>
using namespace std;
int main(int argc, const char * argv[]) {
    freopen(argv[1], "r", stdin);
    if(argc>2){
        freopen(argv[2], "w", stdout);
    }else{
        freopen("Gamestrings.txt", "w", stdout);
    }
    string x,res="resname",state="state=";
    bool is_res=0,is_state,is_trans=0,is_first=1;
    int loc,len;
    while (cin>>x) {
        len=x.length();
        if(is_res){
            loc=0;
            while(x[loc]!='\"'&&loc<len){
                cout<<x[loc];
                loc++;
            }
            if(x[loc]=='\"'){
                is_res=false;
                cout<<"=";
            }else{
                cout<<" ";
            }
            continue;
        }
        if(is_trans){
            loc=0;
            while(loc<len){
                if(x[loc]=='<'){
                    is_trans=false;
                    break;
                }
                if(x[loc]=='&'){
                    if(x[loc+1]=='q'){
                        cout<<"\"";
                        loc+=6;
                        continue;
                    }
                    if(x[loc+1]=='l'){
                        cout<<"<";
                        loc+=4;
                        continue;
                    }
                    if(x[loc+1]=='g'){
                        cout<<">";
                        loc+=4;
                        continue;
                    }
                }
                cout<<x[loc++];
            }
            if(is_trans)
                cout<<" ";
            continue;
        }
        //check "resname"
        is_res=true;
        for(loc=0;loc<7;loc++){
            if(x[loc]!=res[loc]){
                is_res=false;
                break;
            }
        }
        if(is_res){
            if(is_first)
                is_first=0;
            else
                cout<<endl;
            loc=9;
            while(x[loc]!='\"'&&loc<len){
                cout<<x[loc];
                loc++;
            }
            if(x[loc]=='\"'){
                is_res=false;
                cout<<"=";
            }else{
                cout<<" ";
            }
            continue;
        }
        //check for"state="
        is_state=true;
        for(loc=0;loc<6;loc++){
            if(x[loc]!=state[loc]){
                is_state=false;
                break;
            }
        }
        if(is_state){
            loc=7;
            while(x[loc]!='>')
                loc++;
            loc++;
            is_trans=true;
            while(loc<len){
                if(x[loc]=='<'){
                    is_trans=false;
                    break;
                }
                if(x[loc]=='&'){
                    if(x[loc+1]=='q'){
                        cout<<"\"";
                        loc+=6;
                        continue;
                    }
                    if(x[loc+1]=='l'){
                        cout<<"<";
                        loc+=4;
                        continue;
                    }
                    if(x[loc+1]=='g'){
                        cout<<">";
                        loc+=4;
                        continue;
                    }
                }
                cout<<x[loc++];
            }
            if(is_trans)
                cout<<" ";
        }
    }
    return 0;
}
