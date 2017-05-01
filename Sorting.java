import java.util.Scanner;
import java.util.Random;

class Sorting {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		Random rand = new Random();

        	double min;
		int n = sc.nextInt();
		int m = sc.nextInt();


		double[][] array = new double[n][m];

		for (int i = 0; i < n; i++) {

		    for (int j = 0; j < m; j++) {
		        array[i][j] = rand.nextDouble();
            }

        }

        min = array[0][0];

        for (int i = 0; i < n; i ++) {

		    for (int j = 0; j < m; j++) {

		        if (min > array[i][j]) {
		            min = array[i][j];
                }
            }

        }

// O(n)

        System.out.println(min);
    }
}
