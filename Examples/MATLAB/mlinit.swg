
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
	char *command;
	int   len;
	int   status;
	static int module_init = 0;
	if (!module_init) {
		initialize_module();
		module_init = 1;
		if (nrhs < 1) return;
	}
	if (nrhs < 1) {
		return;
               /*mexErrMsgTxt("Must give a method name\n");*/
	}
	if (nlhs > 1) {
		mexErrMsgTxt("At most one output argument allowed\n");
	}
	len = (mxGetM(prhs[0])*mxGetN(prhs[0]))+1;
	command = mxCalloc(len, sizeof(char));
	status = mxGetString(prhs[0], command, len);
	if (status)
		mexErrMsgTxt("Could not convert command name.\n");
	
	
