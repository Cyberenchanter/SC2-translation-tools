#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, const char * argv[]) {
    string front=argv[1],local[9]={"enUS","deDe","esES","esMX","frFR","itIT","plPL","ptBR","ruRU"},suf=".SC2Data/LocalizedData/Gamestrings.txt";
    ifstream in;
    ofstream out;
    for(int i=1;i<9;i++){
        in.open(front+"/"+local[0]+suf,ios::binary);
        out.open(front+"/"+local[i]+suf,ios::binary);
        out<<in.rdbuf();
        out.close();
        in.close();
    }
    return 0;
}
