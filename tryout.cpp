#include<iostream>

using namespace std;

void printPattern(){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if(j <= i){
				cout<<"*";
			}
		}
		cout<<endl;
	}
}

void fibonacci(){
	int a = 0;
	int b = 1;
	
	int sum;
	
	cout<<a<<" "<<b<<" ";
	
	for(int i = 0; i < 5; i++){
		sum = a + b;
		cout<<sum<<" ";
		a = b;
		b = sum; 
	}
	cout<<endl;
	 
}

void recurFibonacci(int a, int b,int i, int j){
	if(i > 0){
		if(j == i)
			cout<<a<<" "<<b<<" ";
		cout<<a+b<<" ";
		recurFibonacci(b, a+b, i - 1, j);
	}
	else{
		cout<<endl;
	}
	
}

int factorial(int num){
	if(num > 0){
		return num * factorial(num - 1);
	}
	else
		return 1;
}

void fact(int num){
	int result = 1;
	
	while(num >= 1 ){
		result *= num;
		num--; 
	}
	
	cout<<result<<endl;
}

void arrRead(int arr[], int n){
	for(int i = 0; i < n; i++){
		cout<<arr[i]<<" "; 
	}
	cout<<endl;
}

void readArrDesc(int arr[], int n){
	int index = n - 1;
	if(index >= 0){
		cout<<arr[index]<<" ";
		readArrDesc(arr, index);
	}
	else{
		cout<<endl;
	}
}

void readArrAsc(int arr[], int n){
	int index = n - 1;
	if(index >= 0){
		readArrAsc(arr, index);
		cout<<arr[index]<<" ";
	}
	
}

int main(){
	printPattern();
	fibonacci();
	cout<<factorial(5)<<endl;
	fact(5);
	
	int arr[] = {1,2,3,4,5,6};
	
	arrRead(arr, 6);
	readArrDesc(arr, 6);	
	readArrAsc(arr, 6);
	cout<<endl;
	recurFibonacci(0,1,5,5);
}

/*
OUTPUT

*
**
***
****
*****
0 1 1 2 3 5 8 
120
120
1 2 3 4 5 6 
6 5 4 3 2 1 
1 2 3 4 5 6 
0 1 1 2 3 5 8 


*/

