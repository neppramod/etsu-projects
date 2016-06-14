// Heap code in Java
// Pramod Nepal

import java.util.Scanner;

public class MaxHeap {
    private int max_size;           //max size of heap, this is included just to explain that size is not maximum size, but is current heap size.
    private int size;               //size of current heap
    private String[] h;             //array of strings that the heap will use

    public MaxHeap(int max_size) 
    {
        size = 1;
        this.max_size = max_size + 1;
        h = new String[this.max_size];       //we are not using the 0th position of the array, so we need one additional memory spot
    }
    
    public void Print()
    {
        for(int i = 1; i <= size-1; i++) {
            System.out.print(h[i] + " ");
        }
    }
    
    public void Insert(String item)
    {           
        h[size] = item;         
        FixHeapIter(size);
        size++;
    }   
    
    
    public void swap(int first, int second)
    {
        String tmp = h[first];
        h[first] = h[second];
        h[second] = tmp;
    }
    
    public void FixHeapIter(int n) 
    {
        
        if (n > 1) { 
        
            int parent =  n / 2;
        
        
            int compare = h[n].compareTo(h[parent]);
        
            if (compare > 0) {
                swap(n, parent);
                FixHeapIter(parent);
            }
        
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int size;

        System.out.print("Number of chars: ");
        size = scanner.nextInt();

        MaxHeap maxHeap = new MaxHeap(size);

        for (int i = 1; i <= size; i++) {
            String ch = scanner.next();
            maxHeap.Insert(ch);
        }

        maxHeap.Print();
    }
}
