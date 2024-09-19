
public class SumDigits {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int num = 374;
		int hundreds = num / 100;
		int tens = (num - hundreds * 100) / 10;
		int units = num % 10;
		System.out.printf("정수 %d의 각 자리 숫자의 총합: %d", 
				num, hundreds + tens + units);
	}

}
