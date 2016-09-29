#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 100000
int input(char *str1, char op, char opnext){//�ж������ʽ
	int i;
	if (opnext != '\n') return 0;//�жϲ��������Ƿ���
	else{
		if (op == '+' || op == '-' || op == '*'){//�Ӽ��˲������ж�
			if (str1[0] == '+' || str1[0] == '-' || str1[0] <= '9' && str1[0] >= '0'){//�ж����ַ��Ƿ���ϸ�ʽ
				for (i = 1; str1[i] != '\0'; i++){
					if (str1[i] <= '9'&&str1[i] >= '0');
					else return 0;//�м��ַ����ϸ�
				}
				return 1;
			}
			else return 0;//���ַ����ϸ�
		} 
		else if(op=='/'){//�����������ж�
			if (str1[0] == '+' || str1[0] <= '9' && str1[0] >= '0'){//�ж����ַ��Ƿ���ϸ�ʽ
				for (i = 1; str1[i] != '\0'; i++){
					if (str1[i] <= '9'&&str1[i] >= '0');
					else return 0;
				}
				return 1;
			}
			else return 0;
		}
		else return 0;//���������ϸ�
	}
}
void form(char *str1,int *num1){//�������ʽ�������ַ�Ϊ1Ϊ��Ϊ0��������λ���λ��
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
void output(int *num){//��׼���num��ʾ����
	
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
void add(int *num1, int *num2){//�����������ӷ�
	int i;
	for (i = 1; i < M; i++){
		num1[i] = num1[i] + num2[i];
		if (num1[i] > 9){
			num1[i] = num1[i] - 10;
			num1[i + 1]=num1[i+1]+1;
		}
	}
}
int cmp(int *num1, int *num2,int s1,int s2){//�Ƚϻ����������ֵ�ϴ��
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
void min(int *num1, int *num2,int s1){//��������������
	int i;
	for (i = 1; i < s1+1; i++){
		num1[i] = num1[i] - num2[i];
		if (num1[i] < 0){
			num1[i] = num1[i] + 10;
			num1[i + 1] = num1[i + 1] - 1;
		}
	}
}
void multi(int *num1, int *num2, int *num3, int s1, int s2){//�˷�
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
void leftmove(int *num4, int *num2, int a,int s2){//���ƻ��ԭ����10��a�η���
	int i;
	for (i = s2; i > 0; i--){
		num4[i + a] = num2[i];
	}
}
void div(int *num1, int *num2, int *num3, int *num4, int s1, int s2){//������num1������num3��
	int i, j;
	int a=1;
	i = cmp(num1, num2, s1, s2);
	if (i == 0){ num3[1] = 1; for (j = 0; j < M; j++){ num1[j] = 0; } }//�����ͱ��������
	else if (i == 2){
		for (j = 1; j < s1 + 1; j++){
			num4[j] = num1[j];
		}
	}//������С�ڳ���
	else{//���������ڳ���
		i = s1 - s2;//i�洢�������ȳ������λ��
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
	char *str1, *str2;//������
	
	char op,opnext,lsl;//������
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
		str2[i] = '\0';//���������ַ�
		
		//getchar();//�������з�
		op = getchar();//���������
		opnext = getchar();//�����������һλ
		if (opnext != '\n'){
			lsl = getchar();
			while (lsl != '\n'){
				lsl = getchar();
			}
		}//���ղ�����������ַ�
		a = input(str1, op, opnext);
		b = input(str2, op, opnext);
		if (a != 1 || b != 1){ printf("ERROR INPUT!\n"); }//�ж������ʽ����ȷ������㣬�������������Ϣ
		else{
			num1 = (int *)malloc(M * sizeof(int));
			num2 = (int *)malloc(M * sizeof(int));
			num4 = (int *)malloc(M * sizeof(int));
			num3 = (int *)malloc(2*M * sizeof(int));
			for (i = 0; i < M; i++){ num1[i] = 0; }
			for (i = 0; i < M; i++){ num2[i] = 0; }
			for (i = 0; i < 2 * M; i++){ num3[i] = 0; }
			for (i = 0; i < M; i++){ num4[i] = 0; }//�����ֵˢ0
			form(str1,num1);
			form(str2,num2);
			for (i = M - 1; i > 0 && (num1[i] == 0); i--);
			s1 = i;
			for (i = M - 1; i > 0 && (num2[i] == 0); i--);
			s2 = i;//��������λ��
			switch (op){
			case '+':{
				if (num1[0] == 0 && num2[0] == 0){ add(num1, num2); output(num1); }//�����������
				else if (num1[0] == 1 && num2[0] == 1){ add(num1, num2); output(num1); }//�����������
				else if(num1[0] == 0 && num2[0] == 1){
					a = cmp(num1, num2, s1, s2);
					if (a == 2){ min(num2, num1, s2); output(num2); }
					else{ min(num1, num2, s1); output(num1); }
				}
				else{//����һ��һ��������ֵ��ļ�ȥ����ֵС��
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
				if (num1[0] == 0 && num2[0] == 0 || num1[0] == 1 && num2[0] == 1){//�жϷ���
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