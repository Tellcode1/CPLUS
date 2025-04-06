#include "oop.h"

#define namespace object
#define namespacefn_pointer(fnname, type) type (*fnname)()
#define namespacefn(namespace, fnname, type) type NAMESPACE_##namespace##_##fnname
#define namespacefn_name(namespace, fnname) NAMESPACE_##namespace##_##fnname
#define namespacesetup(namespace) namespace *namespace##_NamespaceSetupFunction(namespace *space )

#define namespace_create(namespace_, name) namespace_ name =