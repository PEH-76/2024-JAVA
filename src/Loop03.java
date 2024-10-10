import java.util.Scanner;

public class Loop03 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		int number;
		int sum = 0;
		
		System.out.println("10보다 큰 숫자를 입력하세요.");
		number = input.nextInt();
		
		do{
			sum += number;
			number --;
		}while(number >= 10);
		
		System.out.println("합계: " + sum);
		
	}

}
