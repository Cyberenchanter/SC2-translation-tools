#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
struct behav{
    string id;
    bool is_hidden=0;
}bdat[30005];
int behavcnt=0;
string front,local[10]={"zhCN","enUS","deDe","esES","esMX","frFR","itIT","plPL","ptBR","ruRU"},suf=".SC2Data/LocalizedData/Gamestrings.txt",sufb="/Base.SC2Data/GameData/BehaviorData.xml";
void initbehavior(){
    ifstream in;
    in.open(front+sufb);
    string buf;
    int loc;
    while (getline(in, buf)) {
        loc=0;
        while(buf[loc]==' '){
            loc++;
        }
        buf=buf.substr(loc);
        if(buf.substr(0,10)=="<CBehavior"){
            loc=10;
            while(buf[loc]!='=')
                loc++;
            buf=buf.substr(loc+2);
            loc=0;
            while(buf[loc]!='\"')
                loc++;
            bdat[++behavcnt].id=buf.substr(0,loc);
        }
        /*if(buf.substr(0,37)=="<InfoFlags index=\"Hidden\" value=\"1\"/>")
            bdat[behavcnt].is_hidden=true;*/
    }
    in.close();
    return;
}
bool chkbehavior(string x){
    string xid;
    int loc=0,i;
    for(i=0;x[i]!='=';i++){
        if(x[i]=='/')
            loc=i;
    }
    xid=x.substr(loc+1,i-loc-1);
    for(i=0;i<=behavcnt;i++){
        if(xid==bdat[i].id){
            if(x.find("复件")!=string::npos)
                bdat[i].is_hidden=true;
            return bdat[i].is_hidden;
        }
    }
    return false;
}
void reduct(string fname){
    ifstream in;
    ofstream out;
    in.open(fname);
    string x[20005],abil="Abil",effect="Effect",behavior="Behavior";
    int len=0;
    while (getline(in,x[len])) {
        len++;
    }
    in.close();
    out.open(fname);
    for(int i=0;i<len;i++){
        if(x[i].substr(0,4)==abil)
            continue;
        if(x[i].substr(0,6)==effect)
            continue;
        if(x[i].substr(0,8)==behavior)
            if(chkbehavior(x[i]))
                continue;
        if(x[i].find("复件")!=string::npos)
            continue;
        out<<x[i]<<endl;
    }
    out.close();
    return;
}
int main(int argc, const char * argv[]) {
    front=argv[1];
    initbehavior();
    reduct(front+"/"+local[0]+suf);
    reduct(front+"/"+local[1]+suf);
    return 0;
}
