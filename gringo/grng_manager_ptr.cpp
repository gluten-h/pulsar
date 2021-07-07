
#include "grng_manager_ptr.h"


std::unordered_map<GRNG_BINDABLE_TYPE, GRNG_MANAGER_PTR_BINDABLE>			grng_manager_ptr::bindable_ptr;
std::unordered_map<GRNG_ENTITY_TYPE, GRNG_MANAGER_PTR_ENTITY>				grng_manager_ptr::entity_ptr;
std::unordered_map<GRNG_LIGHT_TYPE, GRNG_MANAGER_PTR_LIGHT>					grng_manager_ptr::light_ptr;
std::unordered_map<GRNG_COMPONENT_TYPE, GRNG_MANAGER_PTR_COMPONENT>			grng_manager_ptr::component_ptr;
