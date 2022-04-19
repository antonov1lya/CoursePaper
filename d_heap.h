#ifndef COURSE_PAPER_D_HEAP_H
#define COURSE_PAPER_D_HEAP_H
template<typename Type>
class DHeap{
private:
    std::vector<Type> h;
    int n, d, capacity;
    void swap(Type &first, Type &second){
        Type tmp = first;
        first = second;
        second = tmp;
    }
public:
    DHeap(int d){
        this->d=d;
        n=0;
        capacity=0;
    }
    void push(const Type &add){
        if (n<capacity){
            h[n]=add;
        }
        else {
            h.push_back(add);
            ++capacity;
        }
        int i = n++;
        while (i>0 and h[i] < h[(i-1)/d]){
            swap(h[i],h[(i-1)/d]);
            i=(i-1)/d;
        }
    }
    bool empty(){
        return !n;
    }
    Type pop(){
        if(n!=0){
            Type min = h[0];
            swap(h[0],h[--n]);
            int i=0;
            while (true){
                int j = i;
                for (int k=1; k<d+1; ++k) {
                    if (d * i + k < n and h[d * i + k] < h[j]) {
                        j = d * i + k;
                    }
                }
                if (i==j){
                    break;
                }else{
                    swap(h[i], h[j]);
                    i=j;
                }
            }
            return min;
        }else{
            return Type();
        }
    }
};
#endif //COURSE_PAPER_D_HEAP_H
