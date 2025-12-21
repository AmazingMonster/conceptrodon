// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_TOTAL_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_TOTAL_H

#include <utility>

#include "conceptrodon/metafunctions/omennivore/total.hpp"

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/utilities/vehicle.hpp"
#include "conceptrodon/utilities/carrier.hpp"
#include "conceptrodon/utilities/reverie.hpp"
#include "conceptrodon/utilities/phantom.hpp"
#include "conceptrodon/utilities/forlorn.hpp"
#include "conceptrodon/utilities/travail.hpp"
#include "conceptrodon/utilities/lullaby.hpp"
#include "conceptrodon/utilities/halcyon.hpp"
#include "conceptrodon/utilities/pursuit.hpp"
#include "conceptrodon/utilities/persist.hpp"
#include "conceptrodon/utilities/sunrise.hpp"
#include "conceptrodon/utilities/morning.hpp"

#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestTotal {




/******************************************************************************************************/
template<template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...> class...>
struct GlowVessel {};

template<template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...> class...>
struct DawnVessel {};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE  \
    4

EQUAL_VALUE(Total<Capsule<int, int*, int**, int***>>::value);
EQUAL_VALUE(Total<Shuttle<0, 1, 2, 3>>::value);
EQUAL_VALUE(Total<std::index_sequence<0, 1, 2, 3>>::value);
EQUAL_VALUE(Total<Vehicle<Capsule, Capsule, Capsule, Capsule>>::value);
EQUAL_VALUE(Total<Carrier<Shuttle, Shuttle, Shuttle, Shuttle>>::value);
EQUAL_VALUE(Total<Reverie<Vehicle, Vehicle, Vehicle, Vehicle>>::value);
EQUAL_VALUE(Total<Phantom<Carrier, Carrier, Carrier, Carrier>>::value);
EQUAL_VALUE(Total<Forlorn<Reverie, Reverie, Reverie, Reverie>>::value);
EQUAL_VALUE(Total<Travail<Phantom, Phantom, Phantom, Phantom>>::value);
EQUAL_VALUE(Total<Lullaby<Forlorn, Forlorn, Forlorn, Forlorn>>::value);
EQUAL_VALUE(Total<Halcyon<Travail, Travail, Travail, Travail>>::value);
EQUAL_VALUE(Total<Pursuit<Lullaby, Lullaby, Lullaby, Lullaby>>::value);
EQUAL_VALUE(Total<Persist<Halcyon, Halcyon, Halcyon, Halcyon>>::value);
EQUAL_VALUE(Total<Sunrise<Pursuit, Pursuit, Pursuit, Pursuit>>::value);
EQUAL_VALUE(Total<Morning<Persist, Persist, Persist, Persist>>::value);
EQUAL_VALUE(Total<GlowVessel<Sunrise, Sunrise, Sunrise, Sunrise>>::value);
EQUAL_VALUE(Total<DawnVessel<Morning, Morning, Morning, Morning>>::value);
EQUAL_VALUE(Total_v<DawnVessel<Morning, Morning, Morning, Morning>>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/

}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif