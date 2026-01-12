#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define X 1000000
#define Z 1000000
int main(int argc,char *argv[]){
  unsigned char a=0,w=0,h='#',q='?';
  int p=0,j=0,y=0;
  unsigned int g=89404137;
  if(argc<2){std::cout<<q<<std::endl;return 0;}
  std::ifstream z(argv[1]);
  if(!z){std::cout<<q<<std::endl;return 1;}
  std::stringstream m;m<<z.rdbuf();std::string s=m.str();
  static char t[X]={0};static char b[Z]={0};
  for(int i=0;i<s.length();i++){
    g=g*1664525+1013904223+a+w+h+q+p+s[i];
    switch(((((s[i]^q)+(i%3)+(g>>24))%3)+3)%3){
      case 0:a+=3;w+=7;p-=13;q-=43;g^=0xCAFEBABE;if(p<0)p+=X;break;
      case 1:a-=2;w-=5;q+=67;p+=17;g+=a^w;if(p>X-1)p-=X;break;
      case 2:b[j]=~(((a|w)&h)^q^(g&0xFF));
        if(std::string("*#?").find(b[j])==std::string::npos)g=0xDEADBEEF;
        ++j;q-=(g&1);if(j>Z-1)return 1;break;
    }
  }
  while(y<j){
    switch(b[y]){
      case '*':
        if(y%2){
          t[p]+=251;p+=999983;if(p>X-1)p-=X;
        }
        else{
          t[p]=std::cin.get()^q;y-=3;if(y<0) return 0;
        }
        break;
      case '#':
        if(t[p]==0){
          y-=7;if(y<0)return 0;b[y]=(b[y]=='*'?'#':b[y]=='#'?'?':'*');
        }
        else{
          p=(p-999979);if(p<0)p+=X;t[p]+=241;
        }
        break;
      case '?':
        if(p%2){
          std::cout<<(char)(t[p]^h);t[p]+=239;
        }
        else{
          if(t[p]==0){
            y+=12;if(y>=j)return 0;
          }
          else{
            y=g%j;p=g%X;
          }
        }
        break;
      default:
        std::cout<<'?'<<std::endl;return 1;
        break;
    }
    h=((g>>16)&0xFF)^h^(t[p]&(b[y]|q));
    q+=197;
    ++y;
  }
}
