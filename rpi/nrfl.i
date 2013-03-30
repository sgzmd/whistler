%module nrfl
%{
/* Includes the header in the wrapper code */
#include "nrfl.h"
%}

/* Parse the header file to generate wrappers */
%include "nrfl.h"

%init %{

%}
