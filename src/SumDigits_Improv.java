import java.util.Scanner;


public class SumDigits_Improv {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		/*
		int num = 374;
		int hundreds = num / 100;
		int tens = (num - hundreds * 100) / 10;
		int units = num % 10;
		System.out.printf("정수 %d의 각 자리 숫자의 총합: %d", 
				num, hundreds + tens + units);
				*/
		System.out.print("숫자를 입력하세요.: ");
		Scanner InNum = new Scanner(System.in);
		int num = InNum.nextInt();
		int digit, DigitSum;
		DigitSum = num % 10;
		for(digit = 10; num / digit == 0; digit *= 10) {
			for()
				DigitSum += num / digit;
		}
		System.out.printf("각 자리 숫자의 합은: %d입니다.", DigitSum);
		
	}

}
