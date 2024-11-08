#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//#include "nc.extern.h"

//bezier

#define TRUE 1
#define FALSE 0
#define EQZ 10e-4 //기본 단위 mm
#define NSET 0xff

//bezier
#define OFFSET_RIGHT 1
#define OFFSET_LEFT 0
#define SUCCESS 1
#define FAIL 0
#define YES 1
#define NO 0

#define BZR_PT 30
#define DIM 3


FILE* fnc;
float rz = 5.0; //안전 이동 평면(임의 설정)
float cpx, cpy, cpz; //공구 현위치
int modal_g0 = 0, modal_g1 = 0;
unsigned char modal_g01 = NSET;

// NC CODE GEN.
void nc_wopen(char const* fname) {
	fnc = fopen(fname, "w");
	if (fnc == nullptr) {
		printf("Error: Failed to open file '%s' for writing.\n", fname);
		exit(1);
	}
}

void nc_wclose(void) {
	fclose(fnc);
}

int nc_write_g_01(int n, float x, float y, float z)
{
	char gs[4], xs[20], ys[20], zs[20], check;
	check = 0; //bit0 : G00/G01, bit1~3: x, y, z가 쓰이면 1
	if (n == 0) {
		if (modal_g01) {
			sprintf(gs, "G00");
			check |= 1;
		}
		modal_g01 = 0;
	}
	else if (n == 1) {
		if (modal_g01 != 1) {
			sprintf(gs, "G01");
			check |= 1;
		}
		modal_g01 = 1;
	}

	else {
		printf("Error : nc_write_g_01\n");
		return FALSE;
	}

	if (cpx != x) {
		sprintf(xs, "X%.3f ", x);
		cpx = x;
		check |= 0x2;
	}

	if (cpy != y) {
		sprintf(ys, "Y%.3f ", y);
		cpy = y;
		check |= 0x4;
	}

	if (cpz != z) {
		sprintf(zs, "Z%.3f ", z);
		cpz = z;
		check |= 0x8;
	}

	if (check) {
		if ((check & 1) && (check & 0b00001110)) fprintf(fnc, "%s ", gs); // xyz 좌표에 변화 있으면 씀
		else modal_g01 = NSET; //아니면 modal reset
		if (check & 2) fprintf(fnc, "%s ", xs);
		if (check & 4) fprintf(fnc, "%s ", ys);
		if (check & 8) fprintf(fnc, "%s ", zs);
		if (check & 0b00001110) fprintf(fnc, "\n"); //Blocj이 있을 때만 E0B 사용
		return TRUE;


	}

	return FALSE;
}

int nc_write_g_23(int n, float x, float y, float z, float i, float j, float k) {
	char gs[4], xs[20], ys[20], zs[20], is[20], js[20], ks[20], check = 0;
	modal_g01 = NSET;

	if (n == 2) {
		sprintf(gs, "G02"); check |= 1;
	}
	else if (n == 3) {
		sprintf(gs, "G03"); check |= 1;
	}
	else {
		printf("Error : nc_write_g_23\n");
		return FALSE;
	}

	if (cpx != x) {
		sprintf(xs, "X%.3f ", x);
		cpx = x;
		check |= 0x2;
	}

	if (cpy != y) {
		sprintf(ys, "Y%.3f ", y);
		cpy = y;
		check |= 0x4;
	}

	if (cpz != z) {
		sprintf(zs, "Z%.3f ", z);
		cpz = z;
		check |= 0x8;
	}

	if (i != 0.0) {
		sprintf(is, "I%.3f ", i);
		check |= 0x10;
	}

	if (j != 0.0) {
		sprintf(js, "J%.3f ", j);
		check |= 0x20;
	}

	if (k != 0.0) {
		sprintf(ks, "K%.3f ", k);
		check |= 0x40;
	}

	if (check) {
		if (check & 1) fprintf(fnc, "%s ", gs);
		if (check & 2) fprintf(fnc, "%s ", xs);
		if (check & 4) fprintf(fnc, "%s ", ys);
		if (check & 8) fprintf(fnc, "%s ", zs);
		if (check & 0x10) fprintf(fnc, "%s ", is);
		if (check & 0x20) fprintf(fnc, "%s ", js);
		if (check & 0x40) fprintf(fnc, "%s ", ks);
		fprintf(fnc, "\n");
		return TRUE;
	}
	return FALSE;
}

void nc_write_header(float set_x, float set_y, float set_z, float feed_rate) {
	fprintf(fnc, "G21 (mm)\n"); //meteric
	fprintf(fnc, "G90 (absolute)\n"); //absolute coordinate
	fprintf(fnc, "F%.3f (feed rate)\n", feed_rate);//공구 현위치를 공작물 좌표계 좌표값
	fprintf(fnc, "G92 X%.3f Y%.4f Z%.3f (Set current Tool Position in the active WCS)\n", set_x, set_y, set_z);
	cpx = set_x;
	cpy = set_y;
	cpz = set_z;
	fprintf(fnc, "G17 (XY plane)\n"); //XY 보간
	fprintf(fnc, "M03 (Spindle On)\n");
	nc_write_g_01(0, set_x, set_y, rz); //안전 평면 이동

}

void nc_write_tail(void) {
	fprintf(fnc, "M05 (Spindle Off)\n");
	fprintf(fnc, "M30 (Program stop and rewind)\n");
}

void nc_retract_moveto(float x, float y, float z) {
	if (fabs(x - cpx) > EQZ || fabs(y - cpy) > EQZ || fabs(z - cpz) > EQZ) {
		nc_write_g_01(0, cpx, cpy, rz);
		nc_write_g_01(0, x, y, rz);
		nc_write_g_01(1, x, y, z);
	}
}

//DXF FILE

FILE* fd;

void open_dxf(char const* dxfile) {
	fd = fopen(dxfile, "r");
	if (fd == nullptr) {
		printf("Error: Failed to open DXF file '%s' for reading.\n", dxfile);
		exit(1); // 프로그램 종료
	}
}

void close_dxf(void) {
	fclose(fd);
}

void nc_write_line(float sx, float sy, float sz, float ex, float ey, float ez) {
	nc_retract_moveto(sx, sy, sz);
	nc_write_g_01(1, ex, ey, ez);
}

void process_line(void) {
	char str[300];
	float sx, sy, sz, ex, ey, ez;
	fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &sx);
	fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &sy);
	fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &sz);
	fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &ex);
	fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &ey);
	fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &ez);

	nc_write_line(sx, sy, sz, ex, ey, ez);
}

void nc_write_circle(float cx, float cy, float cz, float r) {
	nc_retract_moveto(cx, cy - r, cz);
	fprintf(fnc, "G03 J%.3f\n", r); //원호 보간
	cpx = cx;
	cpy = cy - r;
	cpz = cz;
}

void nc_write_arc(float cx, float cy, float cz, float r, float sang, float eang) {
	double ex, ey;
	double sx, sy;
	ex = (double)cx + r * cos(eang * 3.141592 / 180.);
	ey = (double)cy + r * sin(eang * 3.141592 / 180.);
	sx = (double)cx + r * cos(sang * 3.141592 / 180.);
	sy = (double)cy + r * sin(sang * 3.141592 / 180.);

	nc_retract_moveto((float)sx, (float)sy, (float)cz);
	nc_write_g_23(3, (float)ex, (float)ey, cz, cx - (float)sx, cy - (float)sy, cz);
}

void process_circle(void) {
	char str[300];
	float cx, cy, cz, r, sang, eang;
	fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &cx);
	fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &cy);
	fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &cz);
	fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &r);
	fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str);
	if (strcmp(str, "AcDbArc") == 0) {
		fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &sang);
		fscanf(fd, "%s\n", str); fscanf(fd, "%s\n", str); sscanf(str, "%f", &eang);
		nc_write_arc(cx, cy, cz, r, sang, eang);
	}
	else {
		nc_write_circle(cx, cy, cz, r);
	}
}

void dxf_read(void) {
	char str[300];
	while (1)
	{
		fscanf(fd, "%s\n", str);
		if (strcmp(str, "AcDbLine") == 0) process_line();
		if (strcmp(str, "AcDbCircle") == 0) process_circle();
		if (!(strcmp(str, "EOF"))) break;
	}
}

void read_dxf(char const* fname) {
	open_dxf(fname);
	dxf_read();
	close_dxf();
}

//bzr

double bzr_pt[BZR_PT][DIM];
int npt = 0;

void cross_product(double a[], double b[], double* c) {
	// 외적 계산: c = a x b
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void unit_vector(double* a) { //단위 벡터
	double magnitude = 0.0;
	for (int i = 0; i < 3; ++i) {
		magnitude += a[i] * a[i];
	}
	magnitude = sqrt(magnitude);

	if (magnitude != 0) {
		for (int i = 0; i < 3; ++i) {
			a[i] /= magnitude;
		}
	}
}

void bezier_add_pt(double x, double y, double z)
{
	bzr_pt[npt][0] = x;
	bzr_pt[npt][1] = y;
	bzr_pt[npt][2] = z;
	npt++;
}

void bezier_clear_pt(void) {
	npt = 0;
}

void bezier(double u, double* p, double* pu) {
	double pt[BZR_PT][DIM], u1;
	int i, j, j1, k;
	u1 = 1 - u;
	if (npt > 1) {
		for (i = npt - 1; i > 0; i--) {
			if(i ==1)
				for (k = 0; k < DIM; k++) {
					pu[k] = ((double)npt - 1, 0) * (pt[1][k] - pt[0][k]);
				}
			for (j = 0; j < i; k++) {
				j1 = j + 1;
				if (i == npt - 1) {
					for (k = 0; k < DIM; k++) {
						pt[j][k] = u1 * bzr_pt[j][k] + u * bzr_pt[j1][k];
					}
				}
				else {
					for (k = 0; k < DIM; k++) {
						pt[j][k] = u1 * pt[j][k] + u * pt[j1][k];
					}
				}
			}
		}
		for (k = 0; k < DIM; k++) p[k] = pt[0][k];
	}
}

void bezier_offset(double u, double r, double up[], int right, double* op) {
	double p[3], pu[3], offs[3];
	int i;
	bezier(u, p, pu);
	cross_product(pu, up, offs);
	unit_vector(offs);
	if (right == OFFSET_LEFT) r = -r;
	for (i = 0; i < 3; i++) {
		op[i] = p[i] + r * offs[i];
	}
}

// NC TEST //
