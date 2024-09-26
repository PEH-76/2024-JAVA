import java.util.Scanner;

public class Example4_01 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		
		System.out.print("숫자를 입력하시오: ");
		double num = input.nextDouble();
		
		if (num < 100) {
			if (num > 50) {
				System.out.println("숫자가 100보다 작고 50보다 큽니다.");
			}
			
			else {
				System.out.println("숫자가 50보다 작습니다.");
			}
		}
		/*System.out.print("점수를 입력하시오: ");
		double num = input.nextDouble();
		
		while(num > 100 || num < 0) {
			System.out.print("점수를 다시 입력하십시오: ");
			num = input.nextDouble();
		}
		
		if (num >= 90) {
			System.out.println("A입니다.");
		}
		else if(num >= 80) {
			System.out.println("B입니다.");
		}
		else if(num >= 70) {
			System.out.println("C입니다.");
		}
		else if(num >= 60) {
			System.out.println("D입니다.");
		}
		else if(num >= 50) {
			System.out.println("E입니다.");
		}
		else {
			System.out.println("F입니다.");	
		}
		*/
		System.out.println("out of section");
	}

}
