#include <windows.h>
#include <iostream>
using namespace std;
class Vector{ // некоторые функции были перемещены в private, чтобы с ними можно было работать только внутри класса.
    int *arr;
    int size;
    int capacity;
    void fullfill() const{
        for (int i=0; i<size;i++){
            arr[i] = rand()%10;
        }
    }
    void increase_capacity(){
        capacity = size*2;
        int *temp_arr = new int[capacity];
        for (int i=0;i<size;i++){
            temp_arr[i] = arr[i];
        }
        arr = new int[capacity];
        for (int j=0;j<size;j++){
            arr[j] = temp_arr[j];
        }
        for (int z=(size+1);z<capacity;z++){
            arr[z] = 0;
        }
        delete[] temp_arr;
    }
    void insert_element(int &temp_i,int &temp_ind){
        int *temp_arr = new int[capacity];
        for (int i=0;i<temp_ind;i++){
            temp_arr[i] = arr[i];
        }
        temp_arr[temp_ind] = temp_i;
        for (int j = temp_ind;j<size;j++){
            temp_arr[j+1] = arr[j];
        }
        for (int z = 0; z<(size+1);z++) {
            arr[z] = temp_arr[z];
        }
        size++;
        delete[] temp_arr;
        print();
    }
    void u_error(int &x) const{
        if(x>=size){
            cout <<"Ошибка: по индексу " << x <<" нельзя добавить или удалить элемент, т.к. индекс последнего "
                                                "элемента в массиве: " << size-1 << endl;
        }
        if(x<0){
            cout <<"Ошибка: по индексу " << x << " нельзя добавить или удалить элемент"
                                                 " т.к. нумерация в массиве с >=0" << endl;
        }
    }
public:
    Vector(int u_size){
        if(u_size>=0) {
            size = u_size;
            capacity = size * 2;
            arr = new int[capacity];
            fullfill();
            print();
        }
        else{
            cout <<"Ошибка: массив не может состоять из <0 элементов." << endl;
        }
    }
    void u_push_back() {
        int temp_i(0);
        cout << "Напишите элемент, который вы хотите добавить в конец массива: " << endl;
        cin>>temp_i;
        if (size < capacity) {
            arr[size] = temp_i;
            size++;
        }
        else{
            increase_capacity();
            arr[size] = temp_i;
            size++;
        }
        print();
    }
    void u_insert(){
        if (size<capacity) {
            int u_val(0);
            int u_ind(0);
            cout << "Введите элемент, а затем его желаемую позицию: " << endl;
            cin >> u_val;
            cout <<"Теперь позицию (индекс): " << endl;
            cin >> u_ind;
            if (size < capacity) {
                if (u_ind >= 0 && u_ind <= (size-1)) {
                    insert_element(u_val, u_ind);
                }
                else {
                    u_error(u_ind);
                }
            }
            else {
                increase_capacity();
                insert_element(u_val,u_ind);
            }
        }
    }
    void u_delete(){
        int u_ind(0);
        cout <<"Введите индекс элемента, который хотите удалить: " << endl;
        cin >> u_ind;
        if (u_ind>=0 && u_ind <= (size-1)){
            int *temp_arr = new int[capacity];
            for (int i =0; i< u_ind;i++){
                temp_arr[i] = arr[i];
            }
            arr[u_ind] = 0;
            for (int j = (u_ind+1);j<size;j++){
                temp_arr[j-1]=arr[j];
            }
            for (int z = 0; z<capacity;z++){
                arr[z] = temp_arr[z];
            }
            delete [] temp_arr;
            (size--);
        }
        else{
            u_error(u_ind);
        }
        print();
    }
    void print(){
        cout<<"Ваш массив сейчас выглядит так:\n";
        if (size!=0) {
            for (int j = 0; j < size; j++) {
                cout << arr[j] << " ";
            }
            cout << "\n________ \n";
        }
        else{
            cout << "Ваш массив 0-го размера \n";
        }
    }
    void GetReference(){
        int temp_a = 0;
        cout<<"Ссылку какого элемента вы хотите получить?Введите индекс: " << endl;
        cin >> temp_a;
        if (temp_a>=0 && temp_a < size) {
            cout << "элемент: " << arr[temp_a] <<"\nссылка: " << &arr[temp_a] << endl;
        }
        else{
            cout <<"Ошибка: вы вышли за диапазон массива. Нумерация элементов массива начинается с 0. Так "
                   "в вашем массиве элементы имеют индексы от 0 до " << size-1 << endl;
        }
    }
    void Arr_info() const {
        cout << "_____\nразмер массива: " << size << "\nвместимость массива: " << capacity << endl;
    }
    ~Vector(){
        delete [] arr;
    }

};
// ----------------------------------------------------

int main(){
 //   SetConsoleOutputCP(CP_UTF8);// CLion
    setlocale(0,"");
    int size(0);
    cout <<"Введите размер массива" << endl;
    cin >> size;
    if (size>=0) {
        Vector a(size);
        a.u_push_back();
        a.u_insert();
        a.u_delete();
        a.GetReference();
        a.Arr_info();
    }
    else {
        cout << "Ошибка: ваш массив не может состоять из отрицательного кол-ва элементов" << endl;
    }
    return 0;
}