package com.kmp.prefix;

import static java.lang.System.out;
import java.util.Scanner;

class ComputPrefix {

	public int[] computPrefixFromPattern(String pattern) {

		int len; // length of prefix
		int pi[]; // prefix index of pattern
		int q, k;

		len = pattern.length();
		char pat[] = new char[len+1];
		char p[] = pattern.toCharArray();
		pi = new int[len + 1];
		
		for(int i = 0; i < len; i++)
			pat[i+1] = p[i];		
		
		pi[1] = 0;
		k = 0;

		for (q = 2; q < len; q++) {

			while (k > 0 && (pat[k+1] != pat[q])) {
				k = pi[k];
			}

			if (pat[k+1] == pat[q])
				k = k + 1;
			pi[q] = k;
		}

		return pi;
	}
}

public class PreFix {

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		ComputPrefix cp = new ComputPrefix();
		String pattern;
		int pi[];

		while (true) {
			out.print("Enter Pattern:");
			pattern = sc.next();
			pi = cp.computPrefixFromPattern(pattern);
			for (int i = 1; i < pi.length; i++)
				out.print(pi[i] + " ");
			out.println();
		}

	}

}
