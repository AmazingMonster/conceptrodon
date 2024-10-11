// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_CACHE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_CACHE_H

#include "conceptrodon/descend/omennivore/cache.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestCache {

#define SUPPOSED_TYPE   \
    Cache<Capsule<int>, Capsule<int*>, Shuttle<0>, Shuttle<1>, Reverie<Capsule>, Phantom<Shuttle>>

SAME_TYPE(Cache<>::Mold<int>::Mold<int*>::Page<0>::Page<1>::Road<Capsule>::Rail<Shuttle>);

#undef SUPPOSED_TYPE

}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif