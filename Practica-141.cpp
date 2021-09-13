
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
        return capacity != size;
    }
    bool is_empty(){
        return size != 0;
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
    void to_string(){
        for (int i = 0; i < size; ++i) {
            cout<< array[i]<<" ";
        }
        cout<<endl;
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

int main(){

    CircularArray<int>* array = new CircularArray<int>(7);
    cout<< boolalpha << array->is_empty() <<endl;
    array->push_back(6);
    array->push_back(3);
    array->push_back(7);
    array->push_back(8);
    array->push_back(1);
    cout<< boolalpha << array->is_empty() <<endl;
    cout<< boolalpha << array->is_full() <<endl;
    array->pop_front();
    array->pop_back();
    array->push_front(10);
    array->push_front(2);
    array->push_front(15);
    array->push_front(4);
    array->to_string();
    cout<<boolalpha<<array->is_full()<<endl;
    cout<<boolalpha<<array->is_sorted()<<endl;
    array->sort();
    array->to_string();
    array->reverse();
    array->to_string();

    delete array;

    //MOSTRANDO LAS CLASES QUEUE Y STACK HEREDADAS DE CIRCULAR ARRAY
    utec::queue<int>* queue = new utec::queue<int>(7);
    queue->push_back(6);
    queue->push_back(3);
    queue->push_back(7);
    queue->push_back(8);
    queue->push_back(1);
    queue->push_back(2);

    utec::stack<int>* stack = new utec::stack<int>(7);
    stack->push_back(6);
    stack->push_back(3);
    stack->push_back(7);
    stack->push_back(8);
    stack->push_back(1);
    stack->push_back(2);

    delete queue;
    delete stack;
    return 0;
}