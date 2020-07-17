
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
	static int t, n;
	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		//System.setIn(new FileInputStream("src/B9.in"));
		Scanner cin = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		t = cin.nextInt();
		n = cin.nextInt();
		BigInteger d;
		d = cin.nextBigInteger();
		BigInteger sum = new BigInteger("0");
		BigInteger[] a = new BigInteger[1005];
		for(int i = 1; i <= t; ++i) {
			a[i] = cin.nextBigInteger();
			sum = sum.add(a[i]);
		}
		int x, y;
		BigInteger fenzi = new BigInteger("1"), fenmu = new BigInteger("1");
		for(int i = 1; i <= n; ++i) {
			x = cin.nextInt();
			y = cin.nextInt();
			fenzi = fenzi.multiply(a[y]);
			fenmu = fenmu.multiply(sum);
			sum = sum.add(d);
			a[y] = a[y].add(d);
		}
		if(fenzi.compareTo(new BigInteger("0")) == 0) {
			System.out.println("0/1");
		} else {
			if(fenzi.compareTo(fenmu)==0) {
				System.out.println("1/1");
			} else {
				BigInteger GCD = fenzi.gcd(fenmu);
				fenzi = fenzi.divide(GCD);
				fenmu = fenmu.divide(GCD);
				System.out.print(fenzi);
				System.out.print("/");
				System.out.print(fenmu);
			}
		}
		
	}
}
