package sem3.algo.practice1.binaryheap;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class BinaryHeapSortTest {

    public static final String FILE_NAME = "r44_11.txt";
    public static final String OUTPUT_FILE_NAME = "r44_11-formatted.txt";

    public static void main(String[] args)
    {
        String outputString = "";
        try (BufferedReader br = new BufferedReader(new FileReader(new File(FILE_NAME)))) {
            String line;
            while ((line = br.readLine()) != null) {
                //System.out.println(line);
                if (line.contains(":") && line.contains(";")) { // we will sort
                    String[] testString = line.split(":");
                    if (testString[1]!= null && testString[1].contains(";"))
                        testString[1] = testString[1].replace(";", "");

                    String[] testNumberString = testString[1].split(" ");
                    List<Integer> intList = new ArrayList<Integer>();

                    for (int i = 0; i < testNumberString.length; i++) {
                        testNumberString[i] = testNumberString[i].trim();
                        if (testNumberString[i].matches("\\d+"))
                            intList.add(Integer.parseInt(testNumberString[i]));
                    }

                    BinaryHeapSort binaryHeapSort = new BinaryHeapSort();

                    int[] intArr = new int[intList.size()];

                    for (int i = 0; i < intList.size(); i++)
                        intArr[i] = intList.get(i);

                    // Sort the array
                    binaryHeapSort.heapSort(intArr);

                    // Print
                    binaryHeapSort.print();

                    // After this parsing get back the array list
                    int[] sortedInt = binaryHeapSort.getArray();

                    String sortedIntStr = "";

                    for (int i = 0; i < sortedInt.length; i++) {
                        sortedIntStr += sortedInt[i] + " ";
                    }
                    sortedIntStr += "\n";

                    // Replace original int lines with sorted lines
                    outputString += sortedIntStr;

                } else {  // We don't need to sort, just put whatever we got
                    outputString += line;
                }

            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        //System.out.println(outputString);
        // Write the text to file
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(OUTPUT_FILE_NAME));
            writer.write(outputString);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
