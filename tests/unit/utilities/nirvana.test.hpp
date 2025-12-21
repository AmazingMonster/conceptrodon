// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_NIRVANA_H
#define CONCEPTRODON_UNIT_TESTS_TEST_NIRVANA_H

#include "conceptrodon/utilities/nirvana.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestNirvana {




/******************************************************************************************************/
/**** Items ****/
template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedNirvana = Nirvana
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedNirvana::size() == 4);
/******************************************************************************************************/




}}}

#endif