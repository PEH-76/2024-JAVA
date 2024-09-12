
public class DataType01 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		byte b = 127;
		short s = 32767;
		int a = 2147483647;
		long l = 9223372036854775807L; //long은 L로 끝나야 함
		
		System.out.println(b + "\n" + s + "\n" + a + "\n" + l);
		
		//각 변수를 변환하거나 치환(=)할 때 자료형이 같아야 성립
		//정수형은 변환이 간단한데 큰 자료형을 작은 데이터 자료형에 넣을 때는 안 됨
		//s = b; 는 되지만 b = s; 안 됨
		

	}

}
