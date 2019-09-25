#include <iostream>
#include <fstream> 
#include <string> 
using namespace std;






int main ()
{

    string filename = "data2Vs.txt";
    ifstream infile;
    infile.open(filename.c_str());
    string buff, data, generator, rbe;

    while(getline(infile, buff)){    

        data = buff.substr(0, buff.find(' '));
        buff = buff.substr(buff.find(' ') + 1, buff.length());
        generator = buff.substr(0, buff.find(' '));
        rbe = buff.substr(buff.find(' ') + 1, buff.length());

        cout << "data: " << data.length() << endl;
        cout << "generator: " << generator.length() << endl;
        cout << "rbe: " << rbe.length() << endl;


    }
    infile.close();
 return 0;
} 