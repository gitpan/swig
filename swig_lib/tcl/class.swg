/* cgetcode.swg : Code for processing cget methods */

 } else if (strcmp(argv[1],"cget") == 0) {
            if (argc == 3) {
                if (strcmp(argv[2],"-length") == 0) {
                    cmd = _wrap_List_length_get;
                }  else if (strcmp(argv[2],"-this") == 0) {
                SWIG_MakePtr(interp->result,(void *) clientData, "_List_p");
                return TCL_OK;
            }	
            if (cmd) {
                oldarg = argv[2];
                argv[2] = &temp[0];
                rcode = (*cmd)(clientData,interp,argc-1,&argv[1]);
                argv[2] = oldarg;
                return rcode;
            } else {
                Tcl_SetResult(interp,"Invalid cget option. Must be { -this -length }",TCL_STATIC);
                return TCL_ERROR;
            }
            } else {
            Tcl_SetResult(interp,"{ -this -length }", TCL_STATIC);
            return TCL_ERROR;
        }
    }
    if (!cmd) {
        Tcl_SetResult(interp,"List methods : { configure cget search insert remove get }",TCL_STATIC);
        return TCL_ERROR;
    }
    oldarg = argv[1];
    argv[1] = &temp[0];
    rcode = (*cmd)(clientData,interp,argc,argv);
    argv[1] = oldarg;
    return rcode;
}

static int TclListCmd(ClientData clientData, Tcl_Interp *interp, int argc, char **argv) {
    void (*del)(ClientData) = 0;
    char *name = 0;
    int (*cmd)(ClientData, Tcl_Interp *, int, char **) = 0;
    List *newObj = 0;
    int firstarg = 0;
    int thisarg = 0;
    if (argc == 1) {
        cmd = _wrap_new_List;
    } else {
        if (strcmp(argv[1],"-this") == 0) thisarg = 2;
        else if (strcmp(argv[1],"-args") == 0) {
            firstarg = 1;
            cmd = _wrap_new_List;
        } else if (argc == 2) {
            firstarg = 1;
            name = argv[1];
            cmd = _wrap_new_List;
        } else if (argc >= 3) {
            name = argv[1];
            if (strcmp(argv[2],"-this") == 0) thisarg = 3;
            else {
                firstarg = 1;
                cmd = _wrap_new_List;
            }
        }
    }
    if (cmd) {
        int result;
        result = (*cmd)(clientData,interp,argc-firstarg,&argv[firstarg]);
        if (result == TCL_OK) {
            SWIG_GetPtr(interp->result,(void **) &newObj,"_List_p");
        } else { return result; }
        if (!name) name = interp->result;
        del = TclDeleteList;
    } else if (thisarg > 0) { 
        if (thisarg < argc) {
            char *r;
            r = SWIG_GetPtr(argv[thisarg],(void **) &newObj,"_List_p");
            if (r) {
                interp->result = "Type error. not a List object.";
                return TCL_ERROR;
            }
        if (!name) name = argv[thisarg];
        } else {
            interp->result = "wrong # args.";
            return TCL_ERROR;
        }
    } else {
        interp->result = "No constructor available.";
        return TCL_ERROR;
    }
    Tcl_CreateCommand(interp,name, TclListMethodCmd, (ClientData) newObj, del);
    return TCL_OK;
}

EXPORT(int,List_Init)(Tcl_Interp *interp) {
	 if (interp == 0) 
		 return TCL_ERROR;
	 Tcl_CreateCommand(interp, "rand", _wrap_rand, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	 Tcl_CreateCommand(interp, "new_List", _wrap_new_List, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	 Tcl_CreateCommand(interp, "delete_List", _wrap_delete_List, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	 Tcl_CreateCommand(interp, "List_search", _wrap_List_search, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	 Tcl_CreateCommand(interp, "List_insert", _wrap_List_insert, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	 Tcl_CreateCommand(interp, "List_remove", _wrap_List_remove, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	 Tcl_CreateCommand(interp, "List_get", _wrap_List_get, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	 Tcl_CreateCommand(interp, "List_length_set", _wrap_List_length_set, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	 Tcl_CreateCommand(interp, "List_length_get", _wrap_List_length_get, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	 Tcl_CreateCommand(interp, "List_print", _wrap_List_print, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	 Tcl_CreateCommand(interp, "List_print1", _wrap_List_print1, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
	 Tcl_CreateCommand(interp,"List",TclListCmd, (ClientData) NULL, NULL);
/*
 * These are the pointer type-equivalency mappings. 
 * (Used by the SWIG pointer type-checker).
 */
	 SWIG_RegisterMapping("_signed_long","_long",0);
	 SWIG_RegisterMapping("_long","_unsigned_long",0);
	 SWIG_RegisterMapping("_long","_signed_long",0);
	 SWIG_RegisterMapping("_unsigned_long","_long",0);
	 SWIG_RegisterMapping("_List","_class_List",0);
	 SWIG_RegisterMapping("_signed_int","_int",0);
	 SWIG_RegisterMapping("_unsigned_short","_short",0);
	 SWIG_RegisterMapping("_signed_short","_short",0);
	 SWIG_RegisterMapping("_unsigned_int","_int",0);
	 SWIG_RegisterMapping("_short","_unsigned_short",0);
	 SWIG_RegisterMapping("_short","_signed_short",0);
	 SWIG_RegisterMapping("_int","_unsigned_int",0);
	 SWIG_RegisterMapping("_int","_signed_int",0);
	 SWIG_RegisterMapping("_class_List","_List",0);
	 return TCL_OK;
}
