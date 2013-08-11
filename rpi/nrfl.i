%module nrfl
%{
/* Includes the header in the wrapper code */
#include "nrfl.h"
#include "../common/arpix/arpix.h"
%}

/* Parse the header file to generate wrappers */
%include "nrfl.h"
%include "../common/arpix/arpix.h"

%include "cpointer.i"
%pointer_functions(ArPiMessage ,ArPiMessageP)

%init %{

%}
