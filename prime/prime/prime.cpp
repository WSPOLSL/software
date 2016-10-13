#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<math.h>
#define true 1
#define flase 0

int N;
int Firstpri_num;
void Get_first_prime(int *Firstpri){//获得根号x前的所有素数
	bool array[60001];
	int i, j;
	array[0] = 0; 
	for (i = 1; i <= 60000; i++){//给初始筛赋初值
		/*if (i % 2 == 0 || i % 3 == 0){
			array[i] = flase;
		}
		else{ array[i] = true; }*/
		array[i] = true;
	}
	array[1] = flase; array[2] = true; array[3] = true;
	for (i = 2; i <= 60000; i++){
		if (array[i] == true){
			/*for (j = i + 1; j <= 60000 ; j++){
				if (j%i == 0) {
					array[j] = flase;
				}
			}*/
			
			int temp4 = i + i;
			while (temp4 <= 60000){
				array[temp4] = flase;
				temp4+=i;
			}
		}
	}
	j = 0;
	for (i = 1; i <= 60000; i++){
		if (array[i] == true){ Firstpri[j] = i; j++; }
	}
}
int Get_N_prime(int *Firstpri){
	bool sieve[60001];
	int i, j;
	int sieve_num=1;
	int sqrt_num;
	int pri_num = Firstpri_num;
	int pre_pri_num = Firstpri_num;
	int number=60000;
	if (N <= Firstpri_num){
		printf("第%d个素数是%d\n", N, Firstpri[N - 1]);
		return 1;
	}
	else{
		while (1){
			int temp7 = 60000;
			for (i = 1; i <= 60000; i++){//给筛赋初值，能被2，3整除的提前筛
				/*if (i % 2 == 0 || i % 3 == 0){
					sieve[i] = flase;
				}
				else{ sieve[i] = true; }*/
				sieve[i] = true;
			}
			sieve[0] = flase;
			
			sqrt_num = (int)sqrt((float)60000 * (sieve_num + 1)) + 1;
			int temp = 60000 * sieve_num;
			int temp2=Firstpri[2];
			
			for (i = 0; temp2 < sqrt_num; i++){//刷筛子，将合数筛掉				
				/*for (j = 1; j <= 60000; j++){
					if ((j + temp) % temp2 == 0){
						sieve[j] = flase;
					}
				}*/
				temp2 = Firstpri[i];
			
				/*for (j = 1; j<=60000&&(j+temp)%temp2!=0; j++)
				{
				}*/
				int temp5 = temp / temp2;

				//sieve[j] = flase;
				int temp3 = temp2*(temp5+1)-temp;
				while(temp3<=60000){
					sieve[temp3] = flase;
					temp3 +=  temp2;

				}
			}
			for (i = 1; i <= 60000; i++){//统计素数的个数
				if (sieve[i] == true){ pri_num++; }
			}
			if (pri_num >= N){//找到需要的素数
				j = N - pre_pri_num;

				for (i = 1; j > 0; i++){
					if (sieve[i] == true){ j--; }
				}
				printf("第%d个素数是%d\n", N, i + 60000 * sieve_num-1);
				return 1;
			}
			sieve_num++;
			pre_pri_num = pri_num;
		//	if (sieve_num % 100 == 0) printf("%d   ",sieve_num);
		}
	}

}



int main(){
	
	int i;
	int Firstpri[7000];
	for (i = 0; i < 7000; i++){ Firstpri[i] = 0; }
	float time_start, time_end;
	printf("请输入1到100000000的数,输入0结束\n");
	scanf("%d", &N);
//	while (N){
		if (N < 1 || N>100000000) {
			printf("ERROR\n"); 
		}
		else{

			time_start = GetTickCount();//计时 
			//Prime(N);
			Get_first_prime(Firstpri);
			for (i = 0; Firstpri[i] != 0; i++){}
			Firstpri_num = i;
			Get_N_prime(Firstpri);
			time_end = GetTickCount();
			printf("Time costs: %.2f seconds\n\n", (time_end - time_start) / 1000);
			/*for (i = 0; Firstpri[i] != 0; i++){}
			Firstpri_num = i;
			printf("%d\n", i);
			printf("%d\n", Firstpri[i-1]);*/

		//	printf("请输入1到100000000的数,输入0结束\n");
			//scanf("%d", &N);
		}
		//scanf("%d", &N);
	//}
	//return 0;
	system("pause");

}




