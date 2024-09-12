
public class DataType02 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		float f = 65.20298f; //float은 f로 
		double d = 876.765; //double은 d로 끝나든 아니든 상관 x 디폴트가 double
		System.out.println(f + "\n" + d);
		
		char ch = 'J'; //char(문자)는 '' string(문자열)은 ""
		char ch2 = 'a';
		char ch3 = 'v';
		char ch4 = 'a';
		System.out.println(ch);
		System.out.println(ch2);
		System.out.println(ch3);
		System.out.println(ch4);
		
		char ch5 = 88;
		System.out.println(ch5);
		System.out.println(ch5+2);
		
		String str = "Java";
		String str2 = "Program";
		System.out.println(str + str2);
		
		boolean t = true;//true, false는 소문자로만 지정됨
		boolean fa = false;

		System.out.println(t);//문자열 아니고 정해진 값, 1비트짜리 값
		System.out.println(fa);
		
		
	}

}
