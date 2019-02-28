#include<stdio.h>

#define SIZE 3
#define TIMES_MAX 2500

int func(double *x, double t, double *y);
int rk(double *x, double t, double h, double *ans);
int RK(double *x, double t, double h);

int main(void){
	int i,j,k;
	double init[SIZE], t=0.0;
	for(i=-1;i<=1;i++){
	for(j=-1;j<=1;j++){
	for(k=-1;k<=1;k++){
		init[0]=(double)i;
		init[1]=(double)j;
		init[2]=(double)k;
		RK(init, t, 0.01);
		printf("\n");
	}}}
	return 0;
}

int func(double *x, double t, double *y){
	double r=0.475;
	y[0]=-10.0*(x[0]-x[1]);
	y[1]=r*x[0]-x[1]-x[0]*x[2];
	y[2]=-8/3*x[2]+x[0]*x[1];
	return 0;
}

int rk(double *x, double t, double h, double *ans){
	int i;
	double k[SIZE];
	double tmp[SIZE];
	func(x, t, k);
	for(i=0;i<SIZE;i++){
		ans[i]=x[i]+k[i]*h/6;
		tmp[i]=x[i]+k[i]*h/2;
	}
	func(tmp, t+h/2, k);
	for(i=0;i<SIZE;i++){
		ans[i]+=k[i]*h/3;
		tmp[i]=x[i]+k[i]*h/2;
	}
	func(tmp, t+h/2, k);
	for(i=0;i<SIZE;i++){
		ans[i]+=k[i]*h/3;
		tmp[i]=x[i]+k[i]*h;
	}
	func(tmp, t+h, k);
	for(i=0;i<SIZE;i++){
		ans[i]+=k[i]*h/6;
	}
	return 0;
}

int RK(double *x, double t, double h){
	int i, times=0;
	double ans[SIZE];
	printf("%f ",t);
	for(i=0;i<SIZE;i++){
		printf("%f ", x[i]);
	}
	printf("\n");
	while(1){
		if(times>=TIMES_MAX)return 0;
		rk(x, t, h, ans);
		printf("%f ",t);
		for(i=0;i<SIZE;i++){
			printf("%f ", ans[i]);
			x[i]=ans[i];
		}
		printf("\n");
		t+=h;
		times++;
	}
	return 0;
}
