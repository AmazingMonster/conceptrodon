// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_FORLORN_H
#define CONCEPTRODON_UNIT_TESTS_TEST_FORLORN_H

#include <concepts>
#include "conceptrodon/utilities/forlorn.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestForlorn {




/******************************************************************************************************/
/**** Items ****/
template<template<template<typename...> class...> class...>
struct Item_0;

template<template<template<typename...> class...> class...>
struct Item_1;

template<template<template<typename...> class...> class...>
struct Item_2;

template<template<template<typename...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<typename...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedForlorn = Forlorn
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
using Result = PackedForlorn::Cool<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
static_assert(PackedForlorn::size() == 4);
/******************************************************************************************************/




}}}

#endif