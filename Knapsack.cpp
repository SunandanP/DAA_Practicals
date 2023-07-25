#include<iostream>

using namespace std;

//global
int objectCount = 0;

// Class to store the data regarding the object
class Container{
public:
	int index;
	int profit;
	int weight;
	float ratio;
	float quantity;

		
	Container(){
		index = objectCount++;
		profit = 0;
		weight = 0;
		ratio = 0;
		quantity = 0;
	}
	
	Container(int weight, int profit){
		objectCount = index++;
		this->profit = profit;
		this->weight = weight;
		ratio = float(profit/float(weight));
		quantity = 0;
	}
	
	void printContainer(){
		cout<<"Profit : "<<profit<<", Weight : "<<weight<<", Ratio : "<<ratio<<", Quantity :  "<<quantity<<endl;
	}
};


// Wrapper class to implement array of containers and operations based on it
class App{
	public:
	int size;
	int capacity;
	Container *containers;
	
	App(Container containers[], int size, int capacity){
		this->containers = containers;
		this->size = size;
		this->capacity = capacity;
	}
	
	//To print all the containers contents in the array of the objects.
	void print(){
		for(int i = 0; i < size; i++){
			containers[i].printContainer();
		}
	}
	
	//To sort the containers array in descending order of p/w ratios
	void sortDescinding(){
		Container temp,tempI, tempJ;
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				tempI = containers[i];
				tempJ = containers[j];
				if(tempI.ratio > tempJ.ratio){
					temp = containers[i];
					containers[i] = containers[j];
					containers[j] = temp;
				}
			}
			
		}
		print();
	}
	
	
	// For selecting the containers with high p/w ratio till the capacity is fulfilled
	void selectContainers(){
		int count = 0; // total weight of selected containers
		int currIndex; // current container index in the array 

		for(currIndex = 0; currIndex < size; currIndex++){
			if(count + containers[currIndex].weight <= capacity){
				count += containers[currIndex].weight;
				containers[currIndex].quantity++;
			}
			
			// When the next container weight exceeds the maximum capacity
			if(count + containers[currIndex + 1].weight > capacity){
				currIndex++;
				break;
			}
		}
		
		
		if(count < capacity){
			// Broken from last iteration will have to add partial quantity of the container to the knapsack
			containers[currIndex].quantity += float((capacity - count)/float(containers[currIndex].weight));
			count += (capacity - count);
		}
	}
	
	void selectContainers2(){
		int count = 0; // total weight of selected containers
		int currIndex; // current container index in the array 

		for(currIndex = 0; currIndex < size; currIndex++){
			if(count + containers[currIndex].weight <= capacity){
				count += containers[currIndex].weight;
				containers[currIndex].quantity++;
			}
			
			// When the next container weight exceeds the maximum capacity
			if(count + containers[currIndex + 1].weight > capacity){
				currIndex++;
			}
		}
	}
	
	void runApp(){
		int input;
		sortDescinding();
		cout<<"1. Fractional (Greedy), 2. Complete (Dynamic)"<<endl;
		cout<<"Select mode of opeartion : ";
		cin>>input;
		if(input == 1){
			selectContainers();
		}
		else{
			selectContainers2();
		}
		printProfit();
	}
	
	void printProfit(){
		float sum = 0;
		
		cout<<"Selected items : "<<endl;
		for(int i = 0; i < size; i++){
			sum += containers[i].profit * containers[i].quantity;
			cout<<i+1<<"]"<<" Profit : "<<containers[i].profit * containers[i].quantity<<", Quantity : "<<containers[i].quantity<<endl;
		}
		cout<<"Total profit : "<<sum<<endl;
	}
	
};


int main(){
	int size, capacity;
	cout<<"Enter the number of items : ";
	cin>>size;
	cout<<endl;
	
	cout<<"Enter the capacity of the containers : ";
	cin>>capacity;
	cout<<endl;
	
	Container containers[size];
	
	int profit, weight;
	for(int i = 0; i < size; i++){
		cout<<"Enter profit from  "<<i<<"th item : ";
		cin>>profit;
		cout<<endl;
		
		cout<<"Enter the weight of  "<<i<<"th item : ";
		cin>>weight;
		cout<<endl;
		
		containers[i] = Container(weight, profit);
	}
	
	App app(containers, size, capacity);
	app.runApp();
}


/* OUTPUT
4) Profit : 6, Weight : 1, Ratio : 6, Quantity :  0
0) Profit : 10, Weight : 2, Ratio : 5, Quantity :  0
5) Profit : 18, Weight : 4, Ratio : 4.5, Quantity :  0
2) Profit : 15, Weight : 5, Ratio : 3, Quantity :  0
6) Profit : 3, Weight : 1, Ratio : 3, Quantity :  0
1) Profit : 5, Weight : 3, Ratio : 1.66667, Quantity :  0
3) Profit : 7, Weight : 7, Ratio : 1, Quantity :  0
Selected items : 
1] Index : 4, Profit : 6, Quantity : 1
2] Index : 0, Profit : 10, Quantity : 1
3] Index : 5, Profit : 18, Quantity : 1
4] Index : 2, Profit : 15, Quantity : 1
5] Index : 6, Profit : 3, Quantity : 1
6] Index : 1, Profit : 3.33333, Quantity : 0.666667
7] Index : 3, Profit : 0, Quantity : 0
Total profit : 55.3333

*/
