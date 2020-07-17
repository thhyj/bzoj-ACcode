
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.Scanner;
public class Main {
	static BigInteger a, b;

	public static void main(String[] args) throws FileNotFoundException {
		Scanner cin = new Scanner(System.in);
		a = cin.nextBigInteger();
		b = cin.nextBigInteger();
		System.out.println(a.multiply(b));
	}
}
