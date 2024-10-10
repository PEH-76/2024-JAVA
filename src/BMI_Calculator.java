import java.util.Scanner;

public class BMI_Calculator {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner input = new Scanner(System.in);
		
		System.out.print("키(cm) : ");
		double height_cm = input.nextDouble();
		double height_m = height_cm / 100;
		
		System.out.print("체중(kg) : ");
		double weight = input.nextDouble();
		
		double BMI = weight / (height_m * height_m);
		System.out.printf("BMI : %.2f\n", BMI);
		String status;
		if (BMI >= 30) {
			status = "비만";
		}
		else if (BMI >= 25) {
			status = "과체중";
		}
		else if (BMI >= 18.5) {
			status = "정상";
		}
		else {
			status = "저체중";
		}
		System.out.println("비만도 : " + status);
		
	}

}
