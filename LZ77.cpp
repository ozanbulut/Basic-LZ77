//Basic LZ77 encoder and decoder

#include <cstdio>
#include <cstring>
#include <fstream>

#define MAXSIZE 0x0F

using namespace std;

typedef pair<int,int> ii;

void decode(const char* inFile,const char* outFile){
    FILE* fin=fopen(inFile,"rb");
    ofstream fout(outFile);
    string output="";
    unsigned char buffer[3];
    while(fread(buffer,sizeof(buffer),1,fin)){
        int jump = buffer[0]<<4;
        int size = buffer[1];
        jump |= (size>>4);
        size &= MAXSIZE;
        if(jump)
            output+=output.substr(output.size()-jump,size);
        char end=(char)buffer[2];
        output+=end;
    }
    fout<<output;
    fclose(fin);
}

//ii->first is index
//ii->second is size
ii longestPrefix(char* content,int w,int size){
    ii result(0,0);
    for(int i=max(0,w-0xFFF),j=0; i<w; i++){
        for(j=0; i+j<w && j+w<size && j<MAXSIZE; j++){
            if(content[i+j]!=content[w+j]){
                break;
            }
        }
        if(j>result.second){
            result= ii(w-i,j);
        }
    }
    return result;
}

void encode(const char* inFile,const char* outFile){
    FILE* fin=fopen(inFile,"rb");
    FILE* fout=fopen(outFile,"wb");
    fseek(fin, 0, SEEK_END);
    long size = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    char content[size];
    fread(content,size,1,fin);
    for(int i=0; i<size; i++){
        ii longest=longestPrefix(content,i,size-1);
        unsigned char buffer[3];
        memset(buffer,0,sizeof(buffer));
        buffer[1]=longest.second & MAXSIZE;
        buffer[1] |= (longest.first & 0x0F) << 4;
        buffer[0]=(longest.first>>4)&0xFF;
        i+=longest.second;
        buffer[2]=content[i];
        fwrite(buffer,sizeof(buffer),1,fout);
    }
    fclose(fin);
    fclose(fout);
}


int main(int argc,char* args[]){
    if(argc<4){
        printf("usage: ./out e inFile outFile or\n");
        printf("./out d inFile outFile or\n");
        printf("options: e->encode, d->decode");
    }
    if(args[1][0]=='e'){
        encode(args[2],args[3]);
    }else{
        decode(args[2],args[3]);
    }
    return 0;
}
