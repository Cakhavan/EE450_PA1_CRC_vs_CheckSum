#include <iostream>
#include <fstream> 
#include <sstream>
#include <string> 
using namespace std;

void division(int temp[],int gen[],int n,int r)
{
 for(int i=0;i<n;i++)
 {
     if (gen[0]==temp[i])
     {
         for(int j=0,k=i;j<r+1;j++,k++)
             if(!(temp[k]^gen[j]))
                 temp[k]=0;
             else
                 temp[k]=1;
     } }}

int main ()
{
    string filename = "data2Tx.txt";
    ifstream infile;
    infile.open(filename.c_str());
    string buff, data, generator;
    int n,r;
    
    while(getline(infile, buff)){

        data = buff.substr(0, buff.find(' '));
        generator = buff.substr(buff.find(' '), buff.length());
        n = data.length();
        r = generator.length();
        cout << "data string: " << data << endl;
        cout << "data int: " << endl;
        int d[data.length()],gen[generator.length()];
        for(int i = 0; i < data.length(); i++){
            d[i] = (int)data[i];
            cout << d[i];
        }
        cout << endl;

        cout << "generator string: " << generator << endl;
        cout << "generator int: " << endl;
        for(int i = 0; i < generator.length(); i++){
            gen[i] = (int)generator[i];
            cout << gen[i];
        }
        cout << endl;

        
        int temp[data.length()];
        for(int i=0; i < n+r ;i++){
            temp[i] = d[i];
        }
        
        division(d,gen,n,r);
        cout<<"CRC : ";
        for(int i=0;i<r;i++)
        {
            cout<<temp[n+i]<<" ";
            d[n+i] = temp[n+i];
        }

            }
    infile.close();
    return 0;
} 