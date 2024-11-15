
#include <stdio.h>
#include <math.h>

void cross_product(double a[], double b[], double* c) {
	// 외적 계산: c = a x b
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

double scalar_vector(double a[]) {
	double length;
	length = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	return(length);
}

void unit_vector(double a[], double* ua) { //단위 벡터
	double magnitude;
	magnitude = scalar_vector(a);
	if (magnitude != 0) {
		for (int i = 0; i < 3; ++i) {
			ua[i] = a[i] / magnitude;
			
		}
	}
}

void tool_offset(double p[], double r, int right, double u[], double f[], double* op) {
	double fu[3], u_fu[3];
	cross_product(f, u, fu);
	unit_vector(fu, u_fu);
	op[0] = p[0] + r * u_fu[0];
	op[1] = p[2] + r * u_fu[1];
	op[2] = p[2] + r * u_fu[2];

	if (right != 1) {

		op[0] = p[0] - r * u_fu[0];
		op[1] = p[2] - r * u_fu[1];
		op[2] = p[2] - r * u_fu[2];

	}
}

double dot_product(double a[], double b[]) {
	return(a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

void x_line(double p[], double u[], double q[], double v[], double* x) {
	double s, t, xp[3], xq[3];
	double ucp[3], ucv[3], vcu[3], vcq[3], pmq[3], qmp[3];
	double tn[3], tdn[3];
	int i;

	for (i = 0; i < 3; i++) {
		pmq[i] = p[i] - q[i];
		qmp[i] = q[i] - p[i];
	}
	cross_product(u, pmq, ucp);
	cross_product(u, v, ucv);
	t = scalar_vector(ucp) / scalar_vector(ucv);
	if (dot_product(ucp, ucv) < 0.0) t = -t;

	cross_product(v, qmp, vcq);
	cross_product(v, u, vcu);
	s = scalar_vector(vcq) / scalar_vector(vcu);
	if (dot_product(vcq, vcu) < 0.0) s = -s;

	for (i = 0; i < 3; i++) {
		xq[i] = q[i] + t * v[i];
		xp[i] = p[i] + s * u[i];
		x[i] = (xp[i] + xq[i]) / 2.0;
	}

	printf("Xp(%.3f, %.3f, %.3f), Xq(%.3f, %.3f, %.3f), X(%.3f, %.3f, %.3f)", xp[0], xp[1], xp[2], xq[0], xq[1], xq[2], x[0], x[1], x[2]);

}


int main() {
	double p[] = { 0., 0., 0. }, f[] = { 1., 0., 0., }, up[] = { 0., 0., 1. }, r = 1.0, op[3];
	double q[] = { 1., 1., 1. }, u[] = { 1., 0., 0. }, v[] = { -1., -1., 0. }, x[3];

	tool_offset(p, r, 1, up, f, op);
	printf("%.3f, %.3f, %.3f\n", op[0], op[1], op[2]);
	x_line(p, u, q, v, x);
	return 0;
}
