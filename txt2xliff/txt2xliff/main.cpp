#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;
ifstream in;
ofstream out;
int cur_max;
string filename,front,local[10]={"zhCN","enUS","deDe","esES","esMX","frFR","itIT","plPL","ptBR","ruRU"},suf=".SC2Data/LocalizedData/Gamestrings.txt";
struct happy{
    string id,ori,tar;
}dat[15005];
void readid(){
    ifstream id;
    id.open("xdat"+filename+".txt");
    cur_max=1;
    while(getline(id, dat[cur_max].id)){
        cur_max++;
    }
    id.close();
    return;
}
void readori(){
    in.open(front+"/"+local[0]+suf);
    ofstream id;
    id.open("xdat"+filename+".txt",ios::app);
    int loc=0;
    string buf,bid,bori;
    while(getline(in, buf)){
        loc=0;
        while(buf[loc]!='=')
            loc++;
        bid=buf.substr(0,loc);
        bori=buf.substr(loc+1);
        if(!bori.empty()&&(bori[bori.size()-1]=='\r'||bori[bori.size()-1]=='\n'||bori[bori.size()-1]==' '))
            bori.erase(bori.size()-1);
        loc=1;
        while(loc<cur_max&&dat[loc].id!=bid){
            loc++;
        }
        if(loc==cur_max){
            dat[loc].id=bid;
            id<<bid<<endl;
            cur_max++;
        }
        dat[loc].ori=bori;
    }
    in.close();
    id.close();
    return;
}
void readtar(){
    in.open(front+"/"+local[1]+suf);
    int loc=0;
    string buf,bid,btar;
    while(getline(in, buf)){
        loc=0;
        while(buf[loc]!='=')
            loc++;
        bid=buf.substr(0,loc);
        btar=buf.substr(loc+1);
        if(!btar.empty()&&(btar[btar.size()-1]=='\r'||btar[btar.size()-1]=='\n'||btar[btar.size()-1]==' '))
            btar.erase(btar.size()-1);
        loc=1;
        while(loc<cur_max&&dat[loc].id!=bid){
            loc++;
        }
        if(loc==cur_max){
            continue;
        }
        dat[loc].tar=btar;
    }
    in.close();
    return;
}
string xml(string source){
    int len=source.length();
    string ans;
    for(int i=0;i<len;i++){
        if(source[i]=='<'){
            ans+="&lt;";
            continue;
        }
        if(source[i]=='>'){
            ans+="&gt;";
            continue;
        }
        if(source[i]=='&'){
            ans+="&amp;";
            continue;
        }
        if(source[i]=='\"'){
            ans+="&quot;";
            continue;
        }
        if(source[i]=='\''){
            ans+="&apos;";
            continue;
        }
        ans+=source[i];
    }
    return ans;
}
void writexliff(){
    out.open(filename+".xliff");
    out<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
    out<<"<xliff version=\"1.2\" xmlns=\"urn:oasis:names:tc:xliff:document:1.2\">"<<endl;
    out<<"  <file original=\""<<filename<<"\" source-language=\"zh-CN\" target-language=\"en-US\" datatype=\"plaintext\">"<<endl;
    out<<"    <body>"<<endl;
    for(int cur=1;cur<cur_max;cur++){
        out<<"      <trans-unit id=\""<<cur<<"\" resname=\""<<xml(dat[cur].id)<<"\">"<<endl;
        out<<"        <source>"<<xml(dat[cur].ori)<<"</source>"<<endl;
        if(dat[cur].ori!=dat[cur].tar)
            out<<"        <target>"<<xml(dat[cur].tar)<<"</target>"<<endl;
        else
            out<<"        <target></target>"<<endl;
        out<<"      </trans-unit>"<<endl;
    }
    out<<"    </body>"<<endl;
    out<<"  </file>"<<endl;
    out<<"</xliff>"<<endl;
    out.close();
    return;
}
int main(int argc, const char * argv[]) {
    front=argv[1];
    int sep=0;
    for (int loc=0;loc<front.length();loc++){
        if(front[loc]=='/'){
            sep=loc;
        }
    }
    filename=front.substr(sep+1);
    readid();
    readori();
    readtar();
    writexliff();
    return 0;
}
