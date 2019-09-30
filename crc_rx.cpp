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
    string filename = "data2Rx.txt";
    ifstream infile;
    infile.open(filename.c_str());
    string buff, codeword, generator;
    int n,r;
    while(getline(infile, buff)){
        int flag = 0;
        codeword = buff.substr(0, buff.find(' '));
        generator = buff.substr(buff.find(' ') + 1, buff.length());
        r = generator.length();
        n = codeword.length() - r + 1;
        int d[codeword.length()],gen[r];

        for(int i = 0; i < codeword.length(); i++){
            d[i] = (int)(codeword[i] - '0');

        }



        for(int i = 0; i < r; i++){
            gen[i] = (int)(generator[i] - '0');

        }

        r--;

        int temp[r+n];
        for(int i=0;i<n+r;i++){
             temp[i] = d[i];
        }
            
        division(temp,gen,n,r);

        for(int i=0;i<r;i++)
        {
            if(temp[n+i] && flag==0)
            {
                cout<<"fail"<<endl;
                flag = 1;
            } 
        }

        if(flag == 0){
            cout<<"pass"<<endl;
        }

    }
    infile.close();


    return 0;
} 