#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <list>

using namespace std;

class LFUCache {
private:
    int capacity;
    int minFreq;
    //clave,<valor,frecuencia de la clave>
    unordered_map<int,pair<int,int>> keyVal;
    //frecuencia, list=clave,clave,clave,clave...
    unordered_map<int,list<int>> freqList;
    //clave, iterador dentro de la lista de freqList
    unordered_map<int,list<int>::iterator> pos;
public:
    LFUCache(int capacity) {
        this->capacity=capacity;
        minFreq=0;
    }
    
    int get(int key) {
        if(keyVal.find(key)==keyVal.end()){
            return -1;
        }
        //con freqList y pos, encuentras y eliminas esa clave de su lista actual
        //ya que su frecuencia ha aumentado
        freqList[keyVal[key].second].erase(pos[key]);
        keyVal[key].second++; //se aumenta la frecuencia de la clave
        //se añade la clave a la nueva lista de freqList, correspondiente a su nueva
        //frecuencia
        freqList[keyVal[key].second].push_back(key);
        //y actualizas su posición en pos
        pos[key]=--freqList[keyVal[key].second].end();
        if(freqList[minFreq].empty()){
            minFreq++;
        }
        return keyVal[key].first;
    }
    
    void put(int key, int value) {
        if(!capacity) return;
        //ACTUALIZA
        if(keyVal.find(key)!=keyVal.end()){
            keyVal[key].first=value;
            freqList[keyVal[key].second].erase(pos[key]);
            keyVal[key].second++;
            freqList[keyVal[key].second].push_back(key);
            pos[key]=--freqList[keyVal[key].second].end();
            if(freqList[minFreq].empty()) minFreq++;
            return;
        }
        //ELIMINA
        if(keyVal.size()==capacity){
            int delKey=freqList[minFreq].front();
            keyVal.erase(delKey);
            pos.erase(delKey);
            freqList[minFreq].pop_front();
        }
        keyVal[key]={value,1};
        freqList[1].push_back(key);
        pos[key]=--freqList[1].end();
        minFreq=1;
    }
};

int main(){
    return 0;
}