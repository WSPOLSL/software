#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 100000
int input(char *str1, char op, char opnext){//判断输入格式
	int i;
	if (opnext != '\n') return 0;//判断操作符后是否换行
	else{
		if (op == '+' || op == '-' || op == '*'){//加减乘操作符判断
			if (str1[0] == '+' || str1[0] == '-' || str1[0] <= '9' && str1[0] >= '0'){//判断首字符是否符合格式
				for (i = 1; str1[i] != '\0'; i++){
					if (str1[i] <= '9'&&str1[i] >= '0');
					else return 0;//中间字符不合格
				}
				return 1;
			}
			else return 0;//首字符不合格
		} 
		else if(op=='/'){//除法操作符判断
			if (str1[0] == '+' || str1[0] <= '9' && str1[0] >= '0'){//判断首字符是否符合格式
				for (i = 1; str1[i] != '\0'; i++){
					if (str1[i] <= '9'&&str1[i] >= '0');
					else return 0;
				}
				return 1;
			}
			else return 0;
		}
		else return 0;//操作符不合格
	}
}
void form(char *str1,int *num1){//将输入格式化，首字符为1为负为0则正，低位存低位数
	int s1 = strlen(str1);
	int i, j;
	int a, b;
	if (str1[0] == '+' || str1[0] == '-'){
		for (i = 1,j=s1-1; i <= j; i++,j--){
			a = str1[i] - '0';
			b = str1[j] - '0';
			num1[j] = a;
			num1[i] = b;
		}
		num1[s1] = 0;
		if (str1[0] == '+'){ num1[0] = 0; }
		else{ num1[0] = 1; }
	}
	else{
		for (i = 1, j = s1 - 1; i <= j; i++, j--){
			a = str1[i] - '0';
			b = str1[j] - '0';
			num1[j] = a;
			num1[i] = b;
		}
		num1[s1] = str1[0] - '0';
		num1[0] = 0;
	}
}
void output(int *num){//标准输出num表示数字
	
	int i;
	if (num[0] == 1){ printf("-"); 
	for (i =M-1; i > 0 && (num[i] == 0); i--);
	if (i > 0){
		for (; i > 0; i--) { printf("%d", num[i]); }
		printf("\n");
	}
	}
	else{
		for (i = M-1; i > 0 && (num[i] == 0); i--);
		if (i > 0){
			for (; i > 0; i--) { printf("%d", num[i]);  }
			printf("\n");
		}
		else printf("0\n");
	}
}
void add(int *num1, int *num2){//计算两正数加法
	int i;
	for (i = 1; i < M; i++){
		num1[i] = num1[i] + num2[i];
		if (num1[i] > 9){
			num1[i] = num1[i] - 10;
			num1[i + 1]=num1[i+1]+1;
		}
	}
}
int cmp(int *num1, int *num2,int s1,int s2){//比较获得两数绝对值较大的
	int i;
	if (s1 > s2){ return 1; }
	else if (s1 < s2){ return 2; }
	else {
		for (i = s1; i > 0; i--){
			if (num1[i] > num2[i]){ return 1; }
			else if (num1[i] < num2[i]){ return 2; }
		}
		return 0;
	}
}
void min(int *num1, int *num2,int s1){//计算两正数减法
	int i;
	for (i = 1; i < s1+1; i++){
		num1[i] = num1[i] - num2[i];
		if (num1[i] < 0){
			num1[i] = num1[i] + 10;
			num1[i + 1] = num1[i + 1] - 1;
		}
	}
}
void multi(int *num1, int *num2, int *num3, int s1, int s2){//乘法
	int i, j;
	for (i = 1; i < s2 + 1; i++){
		for (j = 1; j < s1 + 1; j++){
			num3[i + j-1] += num2[i] * num1[j];
		}
	}
	for (i = 1; i < 2 * M; i++){
		if (num3[i] >= 10){
			num3[i + 1] += num3[i] / 10;
			num3[i] %= 10;
		}
	}
}
void leftmove(int *num4, int *num2, int a,int s2){//左移获得原数的10的a次方倍
	int i;
	for (i = s2; i > 0; i--){
		num4[i + a] = num2[i];
	}
}
void div(int *num1, int *num2, int *num3, int *num4, int s1, int s2){//除法，num1余数，num3商
	int i, j;
	int a=1;
	i = cmp(num1, num2, s1, s2);
	if (i == 0){ num3[1] = 1; for (j = 0; j < M; j++){ num1[j] = 0; } }//除数和被除数相等
	else if (i == 2){
		for (j = 1; j < s1 + 1; j++){
			num4[j] = num1[j];
		}
	}//被除数小于除数
	else{//被除数大于除数
		i = s1 - s2;//i存储被除数比除数大的位数
		for (; i >= 0; i--){
			for (j = 0; j < M; j++){ num4[j] = 0; }
			leftmove(num4, num2, i, s2);
			a = cmp(num1, num4, s1, s1);
			while (a == 1){
				//leftmove(num4, num2, i, s2);
				min(num1, num4, s1);
				num3[i + 1]++;
				a = cmp(num1, num4, s1, s1);

			}

		}
	}
}






int main(){
	char *str1, *str2;//操作数
	
	char op,opnext,lsl;//操作符
	char end;
	end = getchar();
	int a, b;
	int i;
	int s1,s2;
	int *num1, *num2,*num3,*num4;
	
	
	while (end != EOF){
		str1 = (char *)malloc(M * sizeof(char));
		str2 = (char *)malloc(M * sizeof(char));
		
		str1[0] = end;
		for (i = 0; str1[i] != '\n'; i++){ 
			str1[i+1] = getchar(); }
		str1[i] = '\0';
		str2[0] = getchar();
		for (i = 0; str2[i] != '\n'; i++){ str2[i+1] = getchar(); }
		str2[i] = '\0';//读入输入字符
		
		//getchar();//读出换行符
		op = getchar();//读入操作符
		opnext = getchar();//读入操作符下一位
		if (opnext != '\n'){
			lsl = getchar();
			while (lsl != '\n'){
				lsl = getchar();
			}
		}//吸收操作符多余的字符
		a = input(str1, op, opnext);
		b = input(str2, op, opnext);
		if (a != 1 || b != 1){ printf("ERROR INPUT!\n"); }//判断输入格式，正确进入计算，错误输出错误信息
		else{
			num1 = (int *)malloc(M * sizeof(int));
			num2 = (int *)malloc(M * sizeof(int));
			num4 = (int *)malloc(M * sizeof(int));
			num3 = (int *)malloc(2*M * sizeof(int));
			for (i = 0; i < M; i++){ num1[i] = 0; }
			for (i = 0; i < M; i++){ num2[i] = 0; }
			for (i = 0; i < 2 * M; i++){ num3[i] = 0; }
			for (i = 0; i < M; i++){ num4[i] = 0; }//数组初值刷0
			form(str1,num1);
			form(str2,num2);
			for (i = M - 1; i > 0 && (num1[i] == 0); i--);
			s1 = i;
			for (i = M - 1; i > 0 && (num2[i] == 0); i--);
			s2 = i;//计算数字位数
			switch (op){
			case '+':{
				if (num1[0] == 0 && num2[0] == 0){ add(num1, num2); output(num1); }//两个正数相加
				else if (num1[0] == 1 && num2[0] == 1){ add(num1, num2); output(num1); }//两个负数相加
				else if(num1[0] == 0 && num2[0] == 1){
					a = cmp(num1, num2, s1, s2);
					if (a == 2){ min(num2, num1, s2); output(num2); }
					else{ min(num1, num2, s1); output(num1); }
				}
				else{//两数一正一负，绝对值大的减去绝对值小的
					a = cmp(num1, num2, s1, s2);
					if (a == 1){ min(num1, num2, s1); output(num1); }
					else{ min(num2, num1, s2); output(num2); }
				}
			}; break;
			case'-':{
				if (num1[0] == 0 && num2[0] == 1){ add(num1, num2); output(num1); }
				if (num1[0] == 1 && num2[0] == 0){ add(num1, num2); output(num1); }
				else if (num1[0] == 0 && num2[0] == 0){
					a = cmp(num1, num2, s1, s2);
					if (a == 2){ min(num2, num1, s2); num2[0] = 1; output(num2); }
					else{ min(num1, num2, s1); output(num1); }
				}
				else{
					a = cmp(num1, num2, s1, s2);
					if (a == 1){ min(num1, num2, s2); output(num1);}
					else{ min(num2, num1, s2); num2[0] = 0; output(num2); }
				}
			}; break;
			case'*':{
				if (num1[0] == 0 && num2[0] == 0 || num1[0] == 1 && num2[0] == 1){//判断符号
					multi(num1, num2, num3, s1, s2);
					output(num3);
				}
				else{
					multi(num1, num2, num3, s1, s2);
					num3[0] = 1;
					output(num3);
				}
			}; break;
			case'/':{
				div(num1, num2, num3, num4, s1, s2);
				output(num3);
				output(num1);
			}; break;
			}
			free(num1);
			free(num2);
			free(num3);
			free(num4);
		}
		free(str1);
		free(str2);
		
		end = getchar();
	}
	
	return 0;

}