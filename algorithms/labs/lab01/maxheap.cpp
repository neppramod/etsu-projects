#include <iostream>

using namespace std;

int max_size;
int size;
char *h;

void Print()
{
    for (int i = 1; i < size; i++)
        cout << h[i];
}

int ParentIndex(int n)
{
    return (n)/2;   
}

void Swap(int n, int p)
{
    char tmp = h[n];
    h[n] = h[p];
    h[p] = tmp;
}

void HeapSort(int n)
{
    if (n > 1) {
        int p = ParentIndex(n);
        if (h[n] > h[p]) {
            Swap(n, p);
            HeapSort(p);
        }
    }
}

void Insert(char c)
{
   h[size] = c;
   HeapSort(size); 
   size++;
}


int main(int argc, char *argv[])
{
    size = 1;
    cout << "Number of items: ";
    cin >> max_size;
    max_size = max_size + 1;
    char inputChar;
    h = new char[max_size];

    for(int i = 1; i <= max_size-1; i++) {
        cin >> inputChar;
        Insert(inputChar);
    }

    Print();

    delete [] h;
}
