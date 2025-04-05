#pragma once

#define object typedef struct
#define objectfn(objname, fnname, type) type objname##_##fnname
#define objectfn_pointer(objname, fnname, type) type (*fnname)()
#define objectfn_setup(objinstance, objname, fnname) objinstance->fnname = objname##_##fnname
#define objectsetup(objname) objname *objname##_ObjectSetupFunction
#define init(objname) ; objname##_ObjectSetupFunction
#define self(objname) struct objname *self