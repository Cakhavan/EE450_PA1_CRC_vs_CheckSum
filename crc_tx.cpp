#include <iostream>
#include <fstream> 
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
        generator = buff.substr(buff.find(' ') + 1, buff.length());
        n = data.length();
        r = generator.length();
        cout << "n is " << n << " and r is " << r << endl;
        // cout << "data string: " << data << endl;
        cout << "data int: ";
        int d[data.length() + r],gen[generator.length()];
        for(int i = 0; i < n; i++){
            d[i] = (int)(data[i] - '0');
            cout << d[i];
        }
        cout << endl;

        // cout << "generator string: " << generator << endl;
        cout << "generator int: ";
        for(int i = 0; i < r; i++){
            gen[i] = (int)(generator[i] - '0');
            cout << gen[i];
        }
        cout << endl;

        for(int i=0;i<r;i++){
            d[n+i] = 0;
        }
        int temp[n+r];   
        for(int i=0;i<n+r;i++){
            temp[i] = d[i];
        }
            
        division(temp,gen,n,r);
        cout<<"CRC : ";
        for(int i=0;i<r;i++)
        {
            d[n+i] = temp[n+i];
            cout<<d[n+i];
        }
        cout << endl;
            }
    infile.close();
    return 0;
} 