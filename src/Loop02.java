import java.util.Scanner;

public class Loop02 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		
		int number;
		int loopQ = 1;
		while(loopQ == 1) {
			System.out.println("숫자를 입력하세요.");
			
			number = input.nextInt();
			
			if(number % 2 == 0) {
				System.out.println("짝수입니다.");
			}
			else {
				System.out.println("홀수입니다.");
			}
			
			System.out.println("계속하고 싶다면 1, 그만하고 싶다면 0을 입력하세요.");
			loopQ = input.nextInt();
		}
		
		System.out.println("모든 숫자를 확인했습니다.");
		
	}

}
