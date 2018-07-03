#include<stdio.h>
#include<math.h>
#include "genann.h"
int main()
{
	int i,j;
   // float num = 5.48958123;
 
   // // 4 digits after the decimal point
   // num = floor(10000*num)/10000;
 
   // printf("%f", num);
   // return 0;
	/* Not shown, loading your training and test data. */
	double **training_data_input, **training_data_output, **test_data_input;

	/* New network with 2 inputs,
	 * 1 hidden layer of 3 neurons each,
	 * and 2 outputs. */
	genann *ann = genann_init(2, 1, 3, 2);

	/* Learn on the training set. */
	for (i = 0; i < 300; ++i) {
	    for (j = 0; j < 100; ++j)
	        genann_train(ann, training_data_input[j], training_data_output[j], 0.1);
	}

	/* Run the network and see what it predicts. */
	double const *prediction = genann_run(ann, test_data_input[0]);
	printf("Output for the first test data point is: %f, %f\n", prediction[0], prediction[1]);

	genann_free(ann);


for (j = 0; j < 100; ++j) {
        const double *guess_test = genann_run(ann, input + j*4);
        if (class[j*3+0] == 1.0) {if (guess_test[0] > guess_test[1] && guess_test[0] > guess_test[2]) ++correct;}
        else if (class[j*3+1] == 1.0) {if (guess_test[1] > guess_test[0] && guess_test[1] > guess_test[2]) ++correct;}
        else if (class[j*3+2] == 1.0) {if (guess_test[2] > guess_test[0] && guess_test[2] > guess_test[1]) ++correct;}
        else {printf("Logic error.\n"); exit(1);}
    }





}





