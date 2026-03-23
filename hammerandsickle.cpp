#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
inline char r(const std::unordered_map<long long int, char>& t, long long int p){
  auto i=t.find(p);return (i!=t.end()?i->second:0);
}
inline void l(std::unordered_map<long long int, char>& t, long long int p, char v){
  if (!v)t.erase(p);else t[p]=v;
}
int main(int argc,char *argv[]){
  unsigned char a=0,w=0,h='#',q='?';
  long long int p=0,y=0;
  unsigned int g=89404137;
  if(argc<2){std::cout<<q<<std::endl;return 0;}
  std::ifstream z(argv[1]);
  if(!z){std::cout<<q<<std::endl;return 1;}
  std::stringstream m;m<<z.rdbuf();std::string s=m.str();
  std::unordered_map<long long int, char> t;std::string b;
  for(int i=0;i<s.length();i++){
    g=g*1664525+1013904223+a+w+h+q+p+s[i];
    switch(((((s[i]^q)+(i%3)+(g>>24))%3)+3)%3){
      case 0:a+=3;w+=7;p-=13;q-=43;g^=0xCAFEBABE;break;
      case 1:a-=2;w-=5;q+=67;p+=17;g+=a^w;break;
      case 2:b+=~(((a|w)&h)^q^(g&0xFF));
        if(std::string("*#?").find(b.back())==std::string::npos)g=0xDEADBEEF;break;
    }
  }
  while(y<b.length()){
    switch(b[y]){
      case '*':
        if(y%2){
          l(t,p,r(t,p)+251);p+=999983;
        }
        else{
          l(t,p,std::cin.get()^q);y-=3;if(y<0)return 0;
        }
        break;
      case '#':
        if(!r(t,p)){
          y-=7;if(y<0)return 0;b[y]=(b[y]=='*'?'#':b[y]=='#'?'?':'*');
        }
        else{
          p-=999979;l(t,p,r(t,p)+241);
        }
        break;
      case '?':
        if(p%2){
          std::cout<<(char)(r(t,p)^h)<<std::flush;l(t,p,r(t,p)+239);
        }
        else{
          if(!r(t,p)){
            y+=12;if(y>=b.length())return 0;
          }
          else{
            y=g%b.length();p=g;
          }
        }
        break;
      default:
        std::cout<<'?'<<std::endl;return 1;
        break;
    }
    h=((g>>16)&0xFF)^h^(r(t,p)&(b[y]|q));
    q+=197;
    ++y;
  }
}
