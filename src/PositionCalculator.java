
public class PositionCalculator {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		double time = 5, h0 = 1000, acc= -9.81, v0 = 0, height;
		height = acc * time * time / 2 + v0 * time + h0;
		System.out.printf("자유낙하 물체의 %.2f초 후 위치는 %.2fm입니다.", time, height);
	}

}
