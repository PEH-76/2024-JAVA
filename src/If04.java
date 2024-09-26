import java.util.Scanner;

public class If04 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		System.out.println("3개의 숫자를 입력하시오.");
		
		int x = input.nextInt();
		int y = input.nextInt();
		int z = input.nextInt();
		
		if(x > y && x > z) {
			System.out.println(x + "는 가장 큰 값입니다.");
		}
		else {
			System.out.println(x + "는 가장 큰 값이 아닙니다.");
		}
		
	}

}
