/*
 * GENANN - Minimal C Artificial Neural Network
 *
 * Copyright (c) 2015, 2016 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */


#ifndef __GENANN_H__
#define __GENANN_H__
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GENANN_RANDOM
/* We use the following for uniform random numbers between 0 and 1.
 * If you have a better function, redefine this macro. */
#define GENANN_RANDOM() (((double)rand())/RAND_MAX)
#endif

struct genann;

typedef double (*genann_actfun)(const struct genann *ann, double a);

typedef struct genann {
    /* How many inputs, outputs, and hidden neurons. */
    int inputs, hidden_layers, hidden, outputs;

    /* Which activation function to use for hidden neurons. Default: gennann_act_sigmoid_cached*/
    genann_actfun activation_hidden;

    /* Which activation function to use for output. Default: gennann_act_sigmoid_cached*/
    genann_actfun activation_output;

    /* Total number of weights, and size of weights buffer. */
    int total_weights;

    /* Total number of neurons + inputs and size of output buffer. */
    int total_neurons;

    /* All weights (total_weights long). */
    int_fast8_t *weight;

    /* Stores input array and output of each neuron (total_neurons long). */
    int_fast8_t *output;

    /* Stores delta of each hidden and output neuron (total_neurons - inputs long). */
    int_fast8_t *delta;

} genann;

/* Creates and returns a new ann. */
genann *genann_init(int inputs, int hidden_layers, int hidden, int outputs);

/* Creates ANN from file saved with genann_write. */
genann *genann_read(FILE *in);

/* Sets weights randomly. Called by init. */
void genann_randomize(genann *ann);

/* Returns a new copy of ann. */
genann *genann_copy(genann const *ann);

/* Frees the memory used by an ann. */
void genann_free(genann *ann);

/* Runs the feedforward algorithm to calculate the ann's output. */
int_fast8_t const *genann_run(genann const *ann, int_fast8_t const *inputs);

/* Does a single backprop update. */
void genann_train(genann const *ann, int_fast8_t const *inputs, int_fast8_t const *desired_outputs, double learning_rate);

/* Saves the ann. */
void genann_write(genann const *ann, FILE *out);

void genann_init_sigmoid_lookup(const genann *ann);
double genann_act_sigmoid(const genann *ann, double a);
double genann_act_sigmoid_cached(const genann *ann, double a);
double genann_act_threshold(const genann *ann, double a);
double genann_act_linear(const genann *ann, double a);


#ifdef __cplusplus
}
#endif

#endif /*__GENANN_H__*/