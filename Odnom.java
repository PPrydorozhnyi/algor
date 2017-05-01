import java.util.Scanner;
import java.util.Random;

class Odnom {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        Random rand = new Random();


        int n;
        int counter = 0;
        double number;
        long start;
        long finish;
		
		// введення початкових данних.
        System.out.print("Enter dimension of the array: ");
		if ( sc.hasNextInt() ) {
			
        	n = sc.nextInt();
			
		} else {
			
			System.out.println("Incorrect input. Please, check your value and try again.");
			
			return;
		}
		
        System.out.print("\nEnter your constant value: ");
		
		if ( sc.hasNextDouble() ) {
			
        number = sc.nextDouble();
			
		} else {
			
			System.out.println("Incorrect input. Please, check your value and try again.");
			
			return;
			
		}

        double[] array = new double[n];

        for (int i = 0;  i < n; i++) {

            array[i] = rand.nextDouble() * rand.nextInt(4 * (int)number);

        }

        for (int i = 0;  i < n; i++) {

                System.out.println(array[i]);

            }

        start = System.nanoTime();
        //System.out.println("\nTime1: " + start);
        
        for (int i = 0; i < n; i++) {

            if (array[i] > number) {
                counter++;
            }
        }
        
        finish = System.nanoTime();
        
        finish -= start;

        System.out.println("\nAmount of numbers: " + counter);
        System.out.println("\nTime(in nanoseconds): " + finish);

    }
}
