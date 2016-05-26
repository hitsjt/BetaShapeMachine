#include <mex.h>
#include <string.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

    // Make sure we have the correct # of input args
    if (nrhs != 2)
        mexErrMsgTxt("Incorrect # of input arguments.\n");
    
    // Get the size of the input
    int nps = mxGetN(prhs[0]);
    int nqs = mxGetN(prhs[1]);
    int d   = mxGetM(prhs[0]);
    
    if (d != mxGetM(prhs[1]))
        mexErrMsgTxt("Dimensions of input points do not match.\n");
    
    // Create a new Matlab matrix for distances
    plhs[0] = mxCreateNumericMatrix(nps, nqs, mxSINGLE_CLASS, mxREAL);
    
    float* ps     =  (float*)mxGetData(prhs[0]);
    float* qs     =  (float*)mxGetData(prhs[1]);
    float* sqdist =  (float*)mxGetData(plhs[0]);
    
    int i, j, k;
    double diff, sqdist_acc;
    
    // for all pairs of points
    for (i = 0; i < nps; i++) {
        for (j = 0; j < nqs; j++) {

            // calculate their square distance
            sqdist_acc = 0;
            for(k = 0; k < d; k++) {
                diff = ps[k + i*d] - qs[k + j*d];
                sqdist_acc += diff*diff;
            }
            
            // store result
            sqdist[i + j*nps] = sqdist_acc;
        }
    }
}
