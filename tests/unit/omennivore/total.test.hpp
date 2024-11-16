// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_TOTAL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_TOTAL_H

#include "conceptrodon/omennivore/total.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"
#include "conceptrodon/forlorn.hpp"
#include "conceptrodon/travail.hpp"
#include "conceptrodon/lullaby.hpp"
#include "conceptrodon/halcyon.hpp"
#include "conceptrodon/pursuit.hpp"
#include "conceptrodon/persist.hpp"
#include "conceptrodon/sunrise.hpp"
#include "conceptrodon/morning.hpp"
#include "conceptrodon/arcadia.hpp"
#include "conceptrodon/nirvana.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"
#include <utility>

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestTotal {




/******************************************************************************************************/
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...>
struct GlowHolder {};

template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...>
struct DawnHolder {};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    4

EQUAL_VALUE(Total<Capsule<int, int*, int**, int***>>::value);
EQUAL_VALUE(Total<Shuttle<0, 1, 2, 3>>::value);
EQUAL_VALUE(Total<std::index_sequence<0, 1, 2, 3>>::value);
EQUAL_VALUE(Total<Reverie<Capsule, Capsule, Capsule, Capsule>>::value);
EQUAL_VALUE(Total<Phantom<Shuttle, Shuttle, Shuttle, Shuttle>>::value);
EQUAL_VALUE(Total<Forlorn<Reverie, Reverie, Reverie, Reverie>>::value);
EQUAL_VALUE(Total<Travail<Phantom, Phantom, Phantom, Phantom>>::value);
EQUAL_VALUE(Total<Lullaby<Forlorn, Forlorn, Forlorn, Forlorn>>::value);
EQUAL_VALUE(Total<Halcyon<Travail, Travail, Travail, Travail>>::value);
EQUAL_VALUE(Total<Pursuit<Lullaby, Lullaby, Lullaby, Lullaby>>::value);
EQUAL_VALUE(Total<Persist<Halcyon, Halcyon, Halcyon, Halcyon>>::value);
EQUAL_VALUE(Total<Sunrise<Pursuit, Pursuit, Pursuit, Pursuit>>::value);
EQUAL_VALUE(Total<Morning<Persist, Persist, Persist, Persist>>::value);
EQUAL_VALUE(Total<Arcadia<Sunrise, Sunrise, Sunrise, Sunrise>>::value);
EQUAL_VALUE(Total<Nirvana<Morning, Morning, Morning, Morning>>::value);
EQUAL_VALUE(Total<GlowHolder<Arcadia, Arcadia, Arcadia, Arcadia>>::value);
EQUAL_VALUE(Total<DawnHolder<Nirvana, Nirvana, Nirvana, Nirvana>>::value);

#undef SUPPOSED_VALUE
/******************************************************************************************************/

}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif