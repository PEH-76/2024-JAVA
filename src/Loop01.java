import java.util.Scanner;

public class Loop01 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		
		int sum = 0;
		int time;
		
		System.out.println("5개의 숫자를 입력하세요.");
		
		for(time = 0; time < 5; time ++) {
			int num = input.nextInt();
			sum += num;
		}
		
		System.out.println("합계 : " + sum);
		
	}

}
