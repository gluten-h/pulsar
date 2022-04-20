
#include "bindable.h"


PULSAR::fixed_vector<PULSAR::BINDABLE*, PULSAR::MAX_BINDABLE_COUNT>		PULSAR::BINDABLE::local_unbinds;
PULSAR::fixed_vector<PULSAR::BINDABLE*, PULSAR::MAX_BINDABLE_COUNT>		PULSAR::BINDABLE::global_unbinds;
