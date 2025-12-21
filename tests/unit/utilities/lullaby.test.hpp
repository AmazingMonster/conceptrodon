// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_LULLABY_H
#define CONCEPTRODON_UNIT_TESTS_TEST_LULLABY_H

#include "conceptrodon/utilities/lullaby.hpp"
#include <concepts>

namespace Conceptrodon {
namespace UnitTests {
namespace TestLullaby {




/******************************************************************************************************/
/**** Items ****/
template<template<template<template<typename...> class...> class...> class...>
struct Item_0;

template<template<template<template<typename...> class...> class...> class...>
struct Item_1;

template<template<template<template<typename...> class...> class...> class...>
struct Item_2;

template<template<template<template<typename...> class...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedLullaby = Lullaby
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
using Result = PackedLullaby::Grit<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
static_assert(PackedLullaby::size() == 4);
/******************************************************************************************************/




}}}

#endif