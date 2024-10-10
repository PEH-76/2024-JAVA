import java.util.Scanner;

public class Study_3 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);

		int sum_odd = 0;
		int sum_even = 0;
		
		while(true) {
			System.out.print("두 양의 정수를 입력하세요.: ");
			double num_1 = input.nextDouble();
			double num_2 = input.nextDouble();
			
			if(num_1 >= num_2) {
				System.out.println("첫 번째 정수는 두 번째 정수보다 작아야 합니다.");
			}
			else {
				for(int numbers = (int)num_1; numbers <= (int)num_2; numbers++) {
					if(numbers % 2 == 1) {
						sum_odd += numbers;
					}
					else {
						sum_even += numbers;
					}
					
				}
				System.out.printf("홀수의 합 : %d\n짝수의 합 : %d", sum_odd, sum_even);
				break;
			}
		}
	}

}