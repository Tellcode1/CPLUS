#pragma once

#define object typedef struct

/**
 * Why the static? It makes sure that
 */
#define objectfn(objname, fnname, type) type objname##_##fnname
#define objectfn_pointer(objname, fnname, type) type(*fnname)
#define objectfn_setup(objinstance, objname, fnname) objinstance->fnname = objname##_##fnname
#define objectsetup(objname) objname* objname##_ObjectSetupFunction
#define init(objname)                                                                                                                                \
    ;                                                                                                                                                \
    objname##_ObjectSetupFunction
#define self(objname) struct objname* self
#define inherit(objname) struct objname* inherited
#define inherit_setup(instance, objectfrom) init(objectfrom)
#define objectfn_name(objname, fnname) objname##_##fnname
#define selftype struct
#define initself(instance)                                                                                                                           \
    ;                                                                                                                                                \
    instance.self = &instance
#define setupself(instance) instance->self = instance
