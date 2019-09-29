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

void addition(int seg1[], int seg2[], int sum[])
{
    int carry = 0;
    for(int i = 0; i < 8; i++){
        sum[i] = 0;
    }
    for(int i=7; i >= 0; i--){

        if((seg1[i] + seg2[i] + carry) == 0 && i!=0){
            sum[i] = 0;
            carry = 0;

        }else if((seg1[i] + seg2[i] + carry) == 1 && i!=0){
            sum[i] = 1;
            carry = 0;

        }else if((seg1[i] + seg2[i] + carry) == 2 && i!=0){
            sum[i] = 0;
            carry = 1;

        }else if(((seg1[i] + seg2[i] + carry) == 3) && i!=0){
            sum[i] = 1;
            carry = 1;

        }else if(((seg1[i] + seg2[i] + carry) == 3) && i==0){
            sum[i] = 1;
            int newSeg[8];
            for(int i = 0; i < 8; i++){
                newSeg[i] = sum[i];
                sum[i] = 0;
            }
            int segCarry[8] = {0,0,0,0,0,0,0,1};
            addition(newSeg,segCarry,sum);

        }else if(((seg1[i] + seg2[i] + carry) == 2) && i==0){
            sum[i] = 0;
            int newSeg[8];
            for(int i = 0; i < 8; i++){
                newSeg[i] = sum[i];
                sum[i] = 0;
            }
            int segCarry[8] = {0,0,0,0,0,0,0,1};
            addition(newSeg,segCarry,sum);
            
        }else if(((seg1[i] + seg2[i] + carry) == 1) && i==0){
            sum[i] = 1;
        }else if(((seg1[i] + seg2[i] + carry) == 0) && i==0){
            sum[i] = 0;
            
        }
    }

}

int main ()
{

    string filename = "data2Vs.txt";
    ifstream infile;
    infile.open(filename.c_str());
    string buff, data, generator, rbe;
    int n,r;

        // // CheckSum
        // int checksum[8] = {0,0,0,0,0,0,0,0};
        // int seg1[8] = {1,1,1,1,1,1,1,1};
        // int seg2[8] = {1,1,1,0,0,0,0,0};
        // addition(seg1,seg2,checksum);
        // for(int i = 0 ; i < 8; i++){
        //     cout << checksum[i] << " ";
        // }
int flag = 0;
    while(getline(infile, buff)){    

        data = buff.substr(0, buff.find(' '));
        buff = buff.substr(buff.find(' ') + 1, buff.length());
        generator = buff.substr(0, buff.find(' '));
        rbe = buff.substr(buff.find(' ') + 1, buff.length());
        n = data.length();
        r = generator.length();

        // CRC
        int d[data.length() + r], c[data.length()], gen[generator.length()];
        int temp[n+r]; 
        if(flag == 0){
            cout << "n is " << n << endl;
        }
        
        for(int i = 0; i < n; i++){
            d[i] = (int)(data[i] - '0');
            c[i] = (int)(data[i] - '0');
        }

        for(int i = 0; i < r; i++){
            gen[i] = (int)(generator[i] - '0');
        }

        r--;

        for(int i=0;i<r;i++){
            d[n+i] = 0;
        }
         
        for(int i=0;i<n+r;i++){
            temp[i] = d[i];
        }

        division(temp,gen,n,r);
        int checksum[8] = {0,0,0,0,0,0,0,0};
        if(flag == 0){
            int seg1[8], seg2[8], seg3[8], seg4[8], seg5[8], seg6[8], seg7[8], seg8[8];
            for(int i = 0 ; i < n ; i++){
                if(i < 8){
                    seg1[i] = c[i];
                }else if(i>=8 && i<16){
                    seg2[i-8] = c[i];
                }else if(i>=16 && i<24){
                    seg3[i-16] = c[i];
                }else if(i>=24 && i <32){
                    seg4[i-24] = c[i];
                }else if(i>=32 && i <40){
                    seg5[i-32] = c[i];
                }
                else if(i>=40 && i <48){
                    seg6[i-40] = c[i];
                }
                else if(i>=48 && i <56){
                    seg7[i-48] = c[i];
                }
                else if(i>=56 && i <64){
                    seg8[i-56] = c[i];
                }
            } 
            addition(seg1,seg2,checksum);
            addition(seg3,checksum,checksum);
            addition(seg4,checksum,checksum);
            addition(seg5,checksum,checksum);
            addition(seg6,checksum,checksum);
            addition(seg7,checksum,checksum);
            addition(seg8,checksum,checksum);
            flag=1;
        }


    }
    infile.close();
 return 0;
} 