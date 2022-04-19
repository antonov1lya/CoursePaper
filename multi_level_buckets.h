#ifndef MULTI_LEVEL_BUCKETS_MULTI_LEVEL_BUCKETS_H
#define MULTI_LEVEL_BUCKETS_MULTI_LEVEL_BUCKETS_H
#include <vector>
#include <list>
class MLB{
private:
    class Bucket {
    private:
        int size=0, pointer=0, d=0;
        std::vector<std::list<int>> data;
    public:
        Bucket(int d){
            this->d=d;
            data.resize(d);
        }
        void push(int a, int b) {
            if (size == 0) {
                data[a].push_back(b);
                ++size;
                pointer = a;
            }
            else if (a < d) {
                if (a < pointer) {
                    pointer = a;
                }
                data[a].push_back(b);
                ++size;
            }
        }
        int pop() {
            if (size == 0) {
                return -1;
            }
            else {
                while (data[pointer].empty()) {
                    ++pointer;
                }
                --size;
                int value = data[pointer].front();
                data[pointer].pop_front();
                return value;
            }
        }
        bool empty() {
            return !size;
        }
    };
    int d=0, min=0, pointer=0, buckets=0, size=0;
    std::vector<Bucket*> data;
public:
    MLB(int d, int min){
        this->d=d;
        this->min=min;
    }
    void push(int prior, int elem){
        int i = (prior-min)/d;
        if(prior >= min + buckets * d){
            buckets = i+1;
            data.resize(buckets);
        }
        if(!data[i]){
            data[i] = new Bucket(d);
        }
        int j = prior-min-d*i;
        data[i]->push(j, elem);
        if(size==0){
            pointer=i;
        }else{
            if(i < pointer){
                pointer = i;
            }
        }
        ++size;
    }
    int pop(){
        if(!size){
            return -1;
        }else{
            while(!data[pointer]){
                ++pointer;
            }
            int key = data[pointer]->pop();
            if(data[pointer]->empty()){
                delete data[pointer];
                data[pointer]= nullptr;
            }
            --size;
            return key;
        }
    }
};


#endif //MULTI_LEVEL_BUCKETS_MULTI_LEVEL_BUCKETS_H
