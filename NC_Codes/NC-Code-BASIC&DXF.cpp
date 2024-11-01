#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define EQZ 10e-4 //기본 단위 mm
#define NSET 0xff

FILE* fnc;
float rz = 5.0; //안전 이동 평면(임의 설정)
float cpx, cpy, cpz; //공구 현위치
int modal_g0 = 0, modal_g1 = 0;
unsigned char modal_g01 = NSET;

// NC CODE GEN.
void nc_wopen(char const* fname) {
	fnc = fopen(fname, "w");
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
}

void close_dxf(void) {
	fclose(fd);
}

void nc_write_line(float sx, float sy, float sz, float ex, float ey, float ez) {
	nc_retract_moveto(sx, sy, sz);
	nc_write_g_01(1, ez, ey, ez);
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
	cpy = cy;
	cpz = cz;
}

void nc_write_arc(float cx, float cy, float cz, float r, float sang, float eang) {
	double ex, ey, sx, sy;
	ex = (double)cx + r * cos(eang * 3.1415926535 / 180.);
	ey = (double)cy + r * sin(eang * 3.1415926535 / 180.);
	sx = (double)cx + r * cos(sang * 3.1415926535 / 180.);
	sy = (double)cy + r * sin(sang * 3.1415926535 / 180.);

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
	while (10)
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

// NC TEST //

void nc_test_me(void) {
	float z = -0.5; // 가공 위치
	float yc = 1.0;

	nc_wopen("me.nc");
	nc_write_header(0, 0, rz, 100);
	nc_write_g_01(1, 0, 0, z);
	nc_write_g_01(1, 0, yc, z);
	nc_write_g_23(2, 1, yc, z, 0.5, 0, 0);
	nc_write_g_01(1, 1, 0, z);
	nc_retract_moveto(1, yc, z);
	nc_write_g_23(2, 2, yc, z, 0.5, 0, 0);
	nc_write_g_01(1, 2, 0, z);

	nc_retract_moveto(3, yc, z);
	nc_write_g_01(1, 4, yc, z);
	nc_write_g_23(3, 3, yc, z, -0.5, 0, 0);
	nc_write_g_01(1, 3, 0.5, z);
	nc_write_g_23(3, 4, 0.5, z, 0.5, 0, 0);

	nc_retract_moveto(0, 0, rz);
	nc_write_tail();
	nc_wclose();
	getchar();
	
}

int main(void) {
	nc_test_me();
	return 0;
}