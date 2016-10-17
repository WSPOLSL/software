#include<stdio.h>
#include<iostream>
using namespace std;
const int length = 180;
void filter(int xin[], int xout[], int n, float h[]);
static float h[19] = {
	0.01218354, -0.009012882, -0.02881839, -0.04743239, -0.04584568, -0.008692503, 0.06446265, 0.1544655, 0.2289794, 0.257883,
	0.2289794, 0.1544655, 0.06446265, -0.008692503, -0.04584568, -0.04743239, -0.02881839, -0.009012882, 0.01218354
};
static int x1[length + 20];
void filter(int xin[], int xout[], int n, float h[]){
	int i, j;
	float sum;
	for (i = 0; i < length; i++) x1[n + i - 1] = xin[i];
	for (i = 0; i < length; i++){
		sum = 0.0;
		for (j = 0; j < n; j++) sum += h[j] * x1[i - j + n - 1];
		xout[i] = (int)sum;
	}
	for (i = 0; i < (n - 1); i++)x1[n - i - 2] = xin[length - 1 - i];
}
int main(){
	FILE *fp1, *fp2;
	int frame, indata[length], outdata[length];
	int i;
	fp1 = fopen("aa.wav", "rb");
	fp2 = fopen("outsp.dat", "wb");
	frame = 0;
	while (feof(fp1) == 0){
		frame++;
		printf("frame=%d\n", frame);
		for (i = 0; i < length; i++) indata[i] = _getw(fp1);
		filter(indata, outdata, 19, h);
		for (i = 0; i < length; i++) _putw(outdata[i], fp2);

	}
	_fcloseall();
	//return 0;
	system("pause");
	return 0;
}
