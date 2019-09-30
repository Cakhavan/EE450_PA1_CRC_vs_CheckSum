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

void XOR(int code[], int rbe[], int result[]){

    for(int i = 0; i < 72; i++){

        if(code[i] == 0 && rbe[i] == 0){
            result[i] = 0;
        }else if(code[i] == 0 && rbe[i] == 1){
            result[i] = 1;
        }else if(code[i] == 1 && rbe[i] == 0){
            result[i] = 1;
        }else{
            result[i] = 0;
        }

    }

}

bool hasError(int arr[]){
    for(int i = 0; i < 72; i++){
        if(arr[i] == 1){
            return 1;
        }
    }
    return 0;
}

int main ()
{

    string filename = "data2Vs.txt";
    ifstream infile;
    infile.open(filename.c_str());
    string buff, data, generator, rbe;
    int n,r,e;

    int crc_tp=0;
    int crc_tn=0;
    int crc_fp= 0;
    int crc_fn = 0;
    int cs_tp=0;
    int cs_tn=0;
    int cs_fp=0;
    int cs_fn = 0;
    int count = 0;

    while(getline(infile, buff)){    

        data = buff.substr(0, buff.find(' '));
        buff = buff.substr(buff.find(' ') + 1, buff.length());
        generator = buff.substr(0, buff.find(' '));
        rbe = buff.substr(buff.find(' ') + 1, buff.length());
        n = data.length();
        r = generator.length();
        e = rbe.length();

        // CRC
        int d[data.length() + r], c[data.length()], gen[generator.length()], rbe_array[e];
        int temp[n+r]; 

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

        // cout<<"CRC : ";
        // for(int i=0;i<r;i++)
        // {
        //     cout<<temp[n+i] << " ";
        // }
        // cout << endl;

        // cout << "crc: ";
        for(int i =0; i < 72; i++){
            if(i<n){
                temp[i] = d[i];  
            }
        }

        // cout << endl;

        // temp is now encoded word

        int checksum[8] = {0,0,0,0,0,0,0,0};
        
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

            // take 1's complement of checksum
            for(int i = 0 ; i < 8; i++){
                if(checksum[i] == 1){
                    checksum[i] = 0;
                }else{
                    checksum[i] = 1;
                }
            }

            // append checksum to data
            int codeword_checksum[72];
            for(int i=0;i<72;i++){
                if(i<64){
                    codeword_checksum[i] = c[i];
                }else{
                    codeword_checksum[i] = checksum[i-64];
                }
            }

            for(int i = 0; i < e; i++){
                rbe_array[i] = (int)(rbe[i] - '0');
            }

            int resultschecksum[72];

            XOR(codeword_checksum, rbe_array, resultschecksum);


            int resultscrc[72];
            XOR(temp, rbe_array, resultscrc);


            // check performance

            // do checksum
            int checkseg1[8],checkseg2[8],checkseg3[8],checkseg4[8],checkseg5[8],checkseg6[8],checkseg7[8],checkseg8[8],checksumseg[8];
            for(int i = 0 ; i < 72; i++){
                if(i < 8){
                    checkseg1[i] = resultschecksum[i];
                }else if(i>=8 && i<16){
                    checkseg2[i-8] = resultschecksum[i];
                }else if(i>=16 && i<24){
                    checkseg3[i-16] = resultschecksum[i];
                }else if(i>=24 && i <32){
                    checkseg4[i-24] = resultschecksum[i];
                }else if(i>=32 && i <40){
                    checkseg5[i-32] = resultschecksum[i];
                }
                else if(i>=40 && i <48){
                    checkseg6[i-40] = resultschecksum[i];
                }
                else if(i>=48 && i <56){
                    checkseg7[i-48] = resultschecksum[i];
                }
                else if(i>=56 && i <64){
                    checkseg8[i-56] = resultschecksum[i];
                }else{
                    checksumseg[i-64] = resultschecksum[i];
                }
            }

            int newchecksum[8];
            addition(checkseg1,checkseg2,newchecksum);
            addition(checkseg3,newchecksum,newchecksum);
            addition(checkseg4,newchecksum,newchecksum);
            addition(checkseg5,newchecksum,newchecksum);
            addition(checkseg6,newchecksum,newchecksum);
            addition(checkseg7,newchecksum,newchecksum);
            addition(checkseg8,newchecksum,newchecksum);
            addition(checksumseg,newchecksum,newchecksum);


            // 1's comp of new checksum
            for(int i = 0 ; i < 8; i++){
                if(newchecksum[i] == 1){
                    newchecksum[i] = 0;
                }else{
                    newchecksum[i] = 1;
                }
            }

            // results
            bool errorchecksum = hasError(newchecksum);

            int result_temp[72+r+1];
            for(int i = 0; i < 72 + r; i++){
                if(i<72){
                    result_temp[i] = resultscrc[i];
                }else{
                    result_temp[i] = 0;
                }
            }



            // crc check
            division(result_temp,gen,72,r);
            int errorcrc = 0;
            for(int i =0; i < 8; i++){
                if(result_temp[i+64]){
                    errorcrc =1;
                }
            }

            bool actualerror = hasError(rbe_array);

            if(errorcrc == 1 && actualerror == 1){ // actual error and receiver rejects
                crc_tn++;
                count++;
            }else if(errorcrc == 0 && actualerror==1){ // actual error and receiver accepts
                crc_fp++;
                
            }else if(errorcrc == 1 && actualerror == 0){ // no error and receiver rejects
                crc_fn++;
                
            }else{  // no error and receiver accepts
                crc_tp++;
                
            }

            if(errorchecksum==1 && actualerror==1){
                cs_tn++;
            }else if(errorchecksum==0 && actualerror==1){
                cs_fp++;
            }else if(errorchecksum==1 && actualerror==0){
                cs_fn++;
            }else{
                cs_tp++;
            }
            
    }
    infile.close();

    cout << "crc false positives: " << crc_fp<<endl;
    cout << "crc false negatives: " << crc_fn<<endl;
    cout << "crc true positives: " << crc_tp<<endl;
    cout << "crc true negatives: " << crc_tn<<endl;
    cout << endl;
    cout << "checksum false positives: " << cs_fp<<endl;
    cout << "checksum false negatives: " << cs_fn<<endl;
    cout << "checksum true positives: " << cs_tp<<endl;
    cout << "checksum true negatives: " << cs_tn<<endl;
    cout << endl;



    double crc_percision = crc_tp/(crc_tp+crc_fp);
    //cout << "1" << endl;
    //double cs_percision = cs_tp/(cs_tp+cs_fp);
    //cout << "2" <<endl;
    double crc_recall = crc_tp/(crc_tp+crc_fn);
    //double cs_recall = cs_tp/(cs_tp+cs_fn);

    double crc_f1 = (crc_percision*crc_recall)/(crc_percision+crc_recall);
    //double cs_f1 = (cs_percision*cs_recall)/(cs_percision+cs_recall);

    cout << "crc f1: " << crc_f1 << endl;
    //cout << "cs f1: " << cs_f1 << endl;

 return 0;
} 