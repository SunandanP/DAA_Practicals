#include<iostream>

using namespace std;

class Container{
public:
	static int count;	

	int index;
	int profit;
	int weight;
	float ratio;
	float quantity;

		
	Container(){
		index = count++;
		profit = 0;
		weight = 0;
		ratio = 0;
		quantity = 0;
	}
	
	Container(int weight, int profit){
		index = count++;
		this->profit = profit;
		this->weight = weight;
		ratio = float(profit/float(weight));
		quantity = 0;
	}
	
	void printContainer(){
		cout<<index<<") Profit : "<<profit<<", Weight : "<<weight<<", Ratio : "<<ratio<<", Quantity :  "<<quantity<<endl;
	}
};

int Container::count = 0;

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
	
	void print(){
		for(int i = 0; i < size; i++){
			containers[i].printContainer();
		}
	}
	
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
	
	void selectContainers(){
		int count = 0;
		int currIndex;

		for(currIndex = 0; currIndex < size; currIndex++){
			if(count + containers[currIndex].weight <= capacity){
				count += containers[currIndex].weight;
				containers[currIndex].quantity++;
			}
			if(count + containers[currIndex + 1].weight >= capacity){
				currIndex++;
				break;
			}
		}
		
		if(count < capacity){
			containers[currIndex].quantity += float((capacity - count)/float(containers[currIndex].weight));
			count += (capacity - count);
		}
	}
	
	void runApp(){
		sortDescinding();
		selectContainers();
		printProfit();
	}
	
	void printProfit(){
		float sum = 0;
		
		cout<<"Selected items : "<<endl;
		for(int i = 0; i < size; i++){
			sum += containers[i].profit * containers[i].quantity;
			cout<<i+1<<"] Index : "<<containers[i].index<<", Profit : "<<containers[i].profit * containers[i].quantity<<", Quantity : "<<containers[i].quantity<<endl;
		}
		cout<<"Total profit : "<<sum<<endl;
	}
	
};


int main(){
	Container containers[] = {
		Container(2,10),
		Container(3,5),
		Container(5,15),
		Container(7,7),
		Container(1,6),
		Container(4,18),
		Container(1,3)
		
	};
	
	App app(containers, 7, 15);
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
