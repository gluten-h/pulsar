
#include "grng_bindable.h"


GRNG_PISTON<grng_bindable*, GRNG_MAX_BINDABLE_COUNT>				grng_bindable::local_unbinds;
const GRNG_IPISTON<grng_bindable*, GRNG_MAX_BINDABLE_COUNT>			*grng_bindable::local_iunbinds = grng_bindable::local_unbinds.get_ipiston();

GRNG_PISTON<grng_bindable*, GRNG_MAX_BINDABLE_COUNT>				grng_bindable::global_unbinds;
const GRNG_IPISTON<grng_bindable*, GRNG_MAX_BINDABLE_COUNT>			*grng_bindable::global_iunbinds = grng_bindable::global_unbinds.get_ipiston();
