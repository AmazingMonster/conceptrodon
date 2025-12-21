// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_TRAVAIL_H
#define CONCEPTRODON_UNIT_TESTS_TEST_TRAVAIL_H

#include <concepts>
#include "conceptrodon/utilities/travail.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestTravail {




/******************************************************************************************************/
/**** Items ****/
template<template<template<auto...> class...> class...>
struct Item_0;

template<template<template<auto...> class...> class...>
struct Item_1;

template<template<template<auto...> class...> class...>
struct Item_2;

template<template<template<auto...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<auto...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedTravail = Travail
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Result ****/
using Result = PackedTravail::Calm<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
static_assert(PackedTravail::size() == 4);
/******************************************************************************************************/




}}}

#endif