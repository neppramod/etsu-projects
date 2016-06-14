For ramsey file, I converted it to text file using

$ ./showg_linux64 -q r44_11.g6
// Sample output

11
  0 : 7 8 9 10;
  1 : 4 5 6 10;
  2 : 3 6 7 8 10;
  3 : 2 4 6 7 9;
  4 : 1 3 5 8 9;
  5 : 1 4 6 7 8;
  6 : 1 2 3 5 9 10;
  7 : 0 2 3 5 9 10;
  8 : 0 2 4 5 9 10;
  9 : 0 3 4 6 7 8;
 10 : 0 1 2 6 7 8;


BinaryHeapSortTest.java uses this file, but BinaryHeapSort.java has another main function which does test on sample input. The screenshot file shows the ramsey output.
