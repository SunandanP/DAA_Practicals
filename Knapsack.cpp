#include<iostream>

using namespace std;

struct Object{
	int profit;
	int weight;
	int quantity;
	
	Object(int profit, int weight){
		this->profit = profit;
		this->weight = weight;
		this->quantity = 0;
	}	
	
	Object(){
		profit = 0;
		weight = 0;
		quantity = 0;
	}
};

struct PWR {
	int index;
	float ratio;
	
	PWR(){
		index = -1;
		ratio = 0;
	}
	
	PWR(int index, float ratio){
		this->index = index;
		this->ratio = ratio;
	}
	
};

PWR* getProfitToWeight(Object objects[], int num){
	PWR ratios[num];
	PWR temp;
	for(int i = 0; i < num; i++){
		ratios[i].index = i;
		ratios[i].ratio = float(objects[i].profit/objects[i].weight);
	}
	
	
	for(int i = 0; i < num; i++){
		for(int j = 0; j < num; j++){
			if(ratios[i].ratio <= ratios[j].ratio){
				temp = ratios[i];
				ratios[i] = ratios[j];
				ratios[j] = temp;
			}
		}
	}
	
	return ratios;
}

int getIndex(PWR ratios[], int index){
	return ratios[index].index;
}

float getRatio(PWR ratios[], int index){
	return ratios[index].ratio;
}

void selectObjects(Object objects[], int num, int capacity){
	PWR* ratios = getProfitToWeight(objects, num);
	
	int count = 0, index = 0;
	
	while(count <= capacity){
		count += objects[ratios[index].index].weight;
		objects[ratios[index].index].quantity++;
		index++;
	}
	
	if(count < capacity){
		int reqIndex = getIndex(ratios, index);
		if(reqIndex != -1){
			objects[reqIndex].quantity += float(count/objects[reqIndex].weight);
		}
		
	}
	
	int totalWeight = 0, tW = 0;
	float totalProfit = 0, tP = 0;
	
	index = 0; 
	
	for(int i = 0; i < num; i++){
		tP = objects[i].quantity * getRatio(ratios, i);
		tW = objects[i].weight * objects[i].quantity;
		cout<<"index : "<<i<<" , Quantity : "<<objects[i].quantity<<" , Profit : "<<tP<<" , Considered Weight : "<<tW<<endl;
		totalWeight += tW;
		totalProfit += tP;
	}
	
	cout<<"Total Weight : "<<totalWeight<<" , Total Profit : "<<totalProfit<<endl;
	
}

int main(){
	Object objects[] = {
		Object(2,10),
		Object(3,5),
		Object(5,15),
		Object(7,7),
		Object(1,6),
		Object(4,18),
		Object(1,3)
		
	};
	
	selectObjects(objects,7, 15);
	
	return 0;
	
	
}
