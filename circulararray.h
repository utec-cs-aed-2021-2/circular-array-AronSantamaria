#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <deque>
#include <chrono>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

template <typename S>
void resize(S *&old_array, int* old_capacity, int* new_capacity, int size){
    S* new_array = new S[*new_capacity];
    for (int i = 0; i < size; ++i) {
        new_array[i] = old_array[i];
    }
    *old_array = *new_array;

}

template <typename T>
class CircularArray{
private:
    int capacity = 1;
    T* array = new T[capacity];
    int size = 0;
    int index = 0;
public:
    CircularArray(int _capacity){
        resize(array,&capacity, &_capacity, size);
        capacity = _capacity;
    }
    void push_back(int _value){
        array[index] = _value;
        if (index == capacity - 1){
            resize(array,&capacity, &capacity+1, size);
            capacity = capacity+1;
            index = 0;
        }else{
            index+=1;size+=1;
        }
    }
    void push_front(int _value){
        for (int i = size-1; i >= 0; i--) {
            array[i+1] = array[i];
        }
        array[0] = _value;index+=1;size+=1;
    }
    void pop_back(){
        index-=1;size-=1;
    }
    void pop_front(){
        for (int i = 0; i < size; ++i) {
            array[i] = array[i+1];}
        index-=1;size-=1;
    }
    void reverse(){
        T* new_array = new T[capacity];
        int counter = 0;
        for (int i = size-1; i >= 0; i--) {
            new_array[counter] = array[i]; counter+=1;
        }
        delete[] array;
        array = new_array;
    }
    void QuickSort(int mini, int maxi ){
        int y, z, pivote, aux, start=0;
        y = mini;
        z = maxi;

        pivote = array[(mini + maxi) / 2 ];
        do{
            while((array[y] < pivote) && (z <= maxi) ){
                y++;
            }
            while((pivote < array[z]) && (z > mini) ){
                z--;
            }
            if(y <= z ){
                aux = array[y];
                array[y] = array[z];
                array[z] = aux;
                y++;
                z--;
            }
        }while(y <= z);

        if(mini < z ){
            QuickSort(mini, z);
        }
        if(y < maxi ){
            QuickSort(y, maxi);
        }
    }
    void sort(){
        //cout<<"This: "<<capacity<<", Size: "<<size<<endl;
        QuickSort(0, size-1);
    }
    bool is_full(){
        if (capacity == size){
            return true;
        }else{
            return false;
        }

    }
    bool is_empty(){
        if (size == 0){
            return true;
        }else{
            return false;
        }

    }
    bool is_sorted(){
        auto min_referencial = array[0];
        for (int i = 0; i < size; ++i) {
            //cout<<"Compare: "<<array[i]<<", with: "<<min_referencial<<endl;
            if (array[i] < min_referencial){
                return false;
            }
            min_referencial = array[i];
        }
        return true;
    }
    string to_string(){
        string res;
        int it = *&array[0];

        for (int i = 0; i < size; ++i) {
            it = *&array[i];
            res = res + std::__cxx11::to_string(it);
            res = res + " ";
        }

        return res;
    }
};
namespace utec{
    template <typename K>
    class stack : public CircularArray<K>{
    public:

        stack(int _capacity) : CircularArray<K>(_capacity){
        }
    };

    template <typename P>
    class queue : public CircularArray<P>{
    public:

        queue(int _capacity) : CircularArray<P>(_capacity){
        }
    };
}
