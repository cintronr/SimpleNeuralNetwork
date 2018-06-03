/*
Rico Cintron
Simple Neural Network from  "Code your Own Neural Network".
5/28/2018
*/

#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include<iostream>
#include <thread>       


using namespace std;

//constants
const int NUMINPUTNODES = 2;   // Number of Input Nodes
const int NUMHIDDENNODES = 2;  //Number of Hidden Nodes
const int NUMOUTPUTNODES = 1;  //Number of Output Nodes
const int NUMNODES = NUMINPUTNODES + NUMHIDDENNODES + NUMOUTPUTNODES; //Sum of all nodes
const int ARRAYSIZE = NUMNODES + 1; //1 added for offset. Positions start at 0, so having a 1 added enables us to have "Node 1", Node 2, et cetra.
const int MAXITERATIONS = 100000; //Integer for maximum iterations.
const double E = 2.71828; //const double for value of 'E'.
const double LEARNINGRATE = 0.2; //const double for learning rate.

//Function Prototypes
void initialize(double[][ARRAYSIZE], double[], double[], double[]);
void connectNodes(double[][ARRAYSIZE], double[]);
void trainingExample(double[], double[]);
void activateNetwork(double[][ARRAYSIZE], double[], double[]);
double updateWeights(double[][ARRAYSIZE], double[], double[], double[]);
void displayNetwork(double[], double);
void introduction();

int main() {

	cout << "Neural Network Program!" << endl;

	//Arrays for weight, values, expected values, and thresholds
	double weights[ARRAYSIZE][ARRAYSIZE];
	double values[ARRAYSIZE];
	double expectedValues[ARRAYSIZE];
	double thresholds[ARRAYSIZE];

	//Program introduction.
	introduction();

	//Function call to initiallize variables to 0.0 and connect nodes
	initialize(weights, values, expectedValues, thresholds);
	connectNodes(weights, thresholds);

	//While loop, operates while counter is less than max iterations.
	int counter = 0;
	while (counter < MAXITERATIONS)
	{
		//Function calls and one assignment 
		trainingExample(values, expectedValues);
		activateNetwork(weights, values, thresholds);
		double sumOfSquaredErrors = updateWeights(weights, values, expectedValues, thresholds); //Populates sumOfSquaredErrors with return from updateWeights function
		displayNetwork(values, sumOfSquaredErrors);
		cout << "Count: " << counter << endl;//Displays loop count, not included in the original program.
		counter++;//Increments counter variable.
		cout << "--------------------------------------" << endl;
	}

	//


	system("pause");
	return 0;
}

//Initialize Function. Initalizes arrays with value of 0.0
void initialize(double weights[][ARRAYSIZE], double values[], double expectedValues[], double thresholds[])
{
	for (int x = 0; x <= NUMNODES; x++)
	{
		values[x] = 0.0; //values set to 0.0
		expectedValues[x] = 0.0; //expectedValues set to 0.0
		thresholds[x] = 0.0; //thresholds set to 0.0
		for (int y = 0; y <= NUMNODES; y++)
		{
			weights[x][y] = 0.0;//weights set to 0.0
		}
	}

}
//Initialize Function ends


//Connect Nodes Function. Populates weights and thresholds with random values.


	void connectNodes(double weights[][ARRAYSIZE], double thresholds[])
	{
		for (int x = 1; x <= NUMNODES; x++) 
		{
			for (int y = 1; y <= NUMNODES; y++)
			{
				weights[x][y] = (rand() % 200) / 100.0;//Initiallizes weights to random genrated numbers with a value between 0.0 and 2.0
			}
		}
		//Thresholds set to random values between 0.0 and 2.0
		thresholds[3] = rand() / (double)rand();
		thresholds[4] = rand() / (double)rand();
		thresholds[5] = rand() / (double)rand();
		//Displays weight and threshold values
		cout << "weights[1][3] Value: " << weights[1][3] << endl;
		cout << "weights[1][4] Value: " << weights[1][4] << endl;
		cout << "weights[2][3] Value: " << weights[2][3] << endl;
		cout << "weights[2][4] Value: " << weights[2][4] << endl; 
		cout << "weights[3][5] Value: " << weights[3][5] << endl;
		cout << "weights[4][5] Value: " << weights[4][5] << endl;
		cout << endl;
		cout << "thresholds[3] Value: " << thresholds[3] << endl;
		cout << "thresholds[4] Value: " << thresholds[4] << endl; 
		cout << "thresholds[5] Value: " << thresholds[5] << endl;
	}


	
	//Training Example Function. A clever function that takes advantage of switch casing to provide desired values, for our neural network to compare to.

	void trainingExample(double values[], double expectedValues[])
	{
		static int counter = 0;//Static integer enables retention of value for the life of the program.

		switch (counter % 4) // counter modulo 4 enables straight forward iteration.
		{
		//For XOR, we expect the following...  
		/*
		  1+1 = 0
		  0+1 = 1,
		  1+0 = 1, 
		  0+0 = 0
		*/
		case 0:	    //1+1 should equal 0. We feed that in with this.
			values[1] = 1;
			values[2] = 1;
			expectedValues[5] = 0;
			break;
		case 1:		//0+1 should equal 1. We feed that in with this.
			values[1] = 0;
			values[2] = 1;
			expectedValues[5] = 1;
			break;
		case 2:		//1+0 should equal 1. We feed that in with this.
			values[1] = 1;
			values[2] = 0;
			expectedValues[5] = 1;
			break;
		case 3:		//0+0 should equal 0. We feed that in with this.
			values[1] = 0;
			values[2] = 0;
			expectedValues[5] = 0;
			break;
		}
		counter++;
	}

	void activateNetwork(double weights[][ARRAYSIZE], double values[], double thresholds[])
	{

		//This for loop performs a calculation for each hidden node.
		for (int h = 1 + NUMINPUTNODES; h < 1 + NUMINPUTNODES + NUMHIDDENNODES; h++)
		{
			//Variable for weightedInput.
			double weightedInput = 0.0;
			//Perfom calculation to determine total weighted input
			for (int i = 1; i < 1 + NUMINPUTNODES; i++)
			{
				//Weighted Input calculated by multiplying weights and values from nodes.
				weightedInput += weights[i][h] * values[i]; 
			}
			//Threshold handling. We subtract the threshold value from the weighted input.
			weightedInput += (-1 * thresholds[h]);
			//Sigmoid Function. We apply the sigmoid function to obtain a useable value for the output node.
			values[h] = 1.0 / (1.0 + pow(E, -weightedInput));
		}

		//This for loop performs a calculation for each output node.
		for (int o = 1 + NUMINPUTNODES + NUMHIDDENNODES; o < 1 + NUMNODES; o++)
		{
			//Variable for weightedInput.
			double weightedInput = 0.0;
			//Perfom calculation to determine total weighted input
			for (int h = 1 + NUMINPUTNODES; h < 1 + NUMINPUTNODES + NUMHIDDENNODES; h++)
			{
				//Weighted Input calculated by multiplying weights and values from nodes.
				weightedInput += weights[h][o] * values[h];
			}
			//Threshold handling. We subtract the threshold value from the weighted input.
			weightedInput += (-1 * thresholds[o]);
			//Sigmoid Function. We apply the sigmoid function to output node.
			values[o] = 1.0 / (1.0 + pow(E, -weightedInput));
		}
	}

	double updateWeights(double weights[][ARRAYSIZE], double values[], double expectedValues[], double thresholds[])
	{
		double sumOfSquaredErrors = 0.0; //Double variable for measuring overall  error in program.

		//For loop performing calculations on each output node. We will calculate the following in this loop...
		/*
		Absolute Error: Expected error minus the value generated by our Neural Network.
		Sum of Squared Error: Calculation for figuring out the error in our Neural Network.
		Error Gradient: A slightly complex calculation, which helps us determing the severity of an error. 
		*/

		/*
		Weights are updated with various calculations in the below for loops, using back propagation.
		*/

		for (int o = 1 + NUMINPUTNODES + NUMHIDDENNODES; o < 1 + NUMNODES; o++)
		{
			double absoluteerror = expectedValues[o] - values[o]; //Absolute Error calculation as mentioned above.
			sumOfSquaredErrors += pow(absoluteerror, 2);		  //Sum of Squared calculation.
			double outputErrorGradient = values[o] * (1.0 - values[o]) * absoluteerror; //Error Gradient.

			//update each weighting from the hidden layer
			for (int h = 1 + NUMINPUTNODES; h <1 +NUMINPUTNODES + NUMHIDDENNODES; h++) 
			{
				double delta = LEARNINGRATE*values[h] * outputErrorGradient; //double delta vairiable initalized by calculating LearningRate*Values*errorGradient
				weights[h][o] += delta; // Weights set with delta.
				double hiddenErrorGradient = values[h] * (1 - values[h])*outputErrorGradient*weights[h][o]; //Hidden Error Gradient initialized by this calculation
					for (int i = 1; i < 1 + NUMINPUTNODES; i++)
					{
						double delta = LEARNINGRATE*values[i]*hiddenErrorGradient; //Another variable initialization with calculation.
						weights[i][h] += delta; // weights [i][h] populated with delta values.
					}
				double thresholdDelta = LEARNINGRATE*-1 * hiddenErrorGradient; //Variable initalized with this calculation.
				thresholds[h] += thresholdDelta;//thresholds populated with thresholdDelta values.
			}

			//update each weighting for the theta
			double delta = LEARNINGRATE*-1 * outputErrorGradient;//Variable intialized with this calculation.
			thresholds[o] += delta;//Threshold popluated with delta values
		}
		return sumOfSquaredErrors;
	}

	//Function for displaying network. Pretty self explanitory.
	void displayNetwork(double values[], double sumOfSquaredErrors)
	{
		static int counter = 0; //int variable with program lifecycle retention (static).
		if ((counter % 4) == 0)
		
			cout << "--------------------------------------" << endl;
			cout << "Input 1: " << values[1] << "| ";
			cout << "Input 2: " <<values[2] << "| ";
			cout << "Output: " <<values[5] << "| ";
			cout <<"Err:"<<sumOfSquaredErrors << "|"<<endl;
			
			counter++; //counter post increment
	}

	void introduction() {

		int counter = 5;

		cout << "This is a basic Neural Network Program." << endl;
		cout << endl;
		cout << "We will feed values in for correct XOR functionallity" << endl;
		cout << "The program will learn/adjust to have correct XOR operation." << endl;
		cout << endl;
		cout << "Program will continue in: ";
		while (counter != 0)
		{
			cout << counter; cout << "...";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			counter--;
		}



	

	}