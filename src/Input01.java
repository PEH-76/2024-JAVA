import java.util.Scanner;

public class Input01 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		
		System.out.print("정숫값 입력하기: ");
		int integer = input.nextInt();
		
		System.out.print("\n실숫값 입력하기: ");
		double db = input.nextDouble();
		
		System.out.println("\n정숫값  : " + integer + "\n실숫값 : " + db);
		//System.out.printf("\n정숫값 : %d\n실숫값 : %f", integer, db);
	}

}
