#include "UUID.h"

u64 UUID::record = 0;
u64 UUID::get() { return record++; }