// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_SUNRISE_H
#define CONCEPTRODON_UNIT_TESTS_TEST_SUNRISE_H

#include "conceptrodon/utilities/sunrise.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestSunrise {




/******************************************************************************************************/
/**** Items ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedSunrise = Sunrise
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedSunrise::size() == 4);
/******************************************************************************************************/




}}}

#endif