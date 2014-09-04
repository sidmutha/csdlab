#include"wrapper.h"
#include"cache.h"
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<cstdint>

using namespace std;

int strToInt(string s){
  stringstream ss(s);
  int n;
  ss >> n;
  return n;
}

int main(int argc, char** argv){
  string line;
  ifstream f("config.txt");
  getline(f, line);
  stringstream ss(line);
  string temp;
  int numCaches;
  ss >> temp >> temp >> numCaches;
  
  Wrapper* w = new Wrapper(numCaches);

  int i;
  for(i = 0; i < numCaches; i++){
    getline(f, line); // blank line
    
    getline(f, line); // [Level i]
    
    getline(f, line); // Size = ??KB
    ss.str(string());
    ss.clear();
    ss << line;
    ss >> temp >> temp >> temp;
    string sz_str = temp.substr(0, temp.length() - 2);
    int size = strToInt(sz_str);
    
    getline(f, line); // Associativity = ??
    ss.str(string());
    ss.clear();
    ss << line;
    ss >> temp >> temp;
    int asso;
    ss >> asso;
    
    getline(f, line); // Block_size = ??bytes
    ss.str(string());
    ss.clear();
    ss << line;
    ss >> temp >> temp >> temp;
    sz_str = temp.substr(0, temp.length() - 5);
    int blockSize = strToInt(sz_str);
       
    getline(f, line); // Hit_Latency = ?? // ignore
    
    getline(f, line); // Replacement_Policy = LRU
    ss.str(string());
    ss.clear();
    ss << line;
    ss >> temp >> temp >> temp;
    
    int replacementPolicy;
    if(temp.compare("LRU") == 0){
      replacementPolicy = 0;
    }else if(temp.compare("LFU") == 0){
      replacementPolicy = 1;
    }else{
      replacementPolicy = 2;
    }
    
    w->cacheArray[i] = Cache(i, w, size, asso, blockSize, replacementPolicy);
    //cout << i << ", "  << size << ", " << asso << ", " << blockSize << ", " << replacementPolicy << endl;
  }
  f.close();
  // readin pintrace file:
  f.open("pinatrace_mini.out");
  string rw;
  uint64_t addr = 0x7fa4f3a28a60;
  string t;
  do{
    line.clear();
    getline(f, line);
    if(line.compare("#eof") == 0)
      break;
    //cout << line << endl;
    ss.str(string());
    ss.clear();
    ss << line;
    
    ss >> temp >> rw >> t;// >> addr;
    /*
    if(rw.compare("R")){
      w->read(addr);
    }else{
      w->write(addr);
    }
    */
    cout << t << " | " << rw << endl;
    
  }while(true);
  return 0;
}
