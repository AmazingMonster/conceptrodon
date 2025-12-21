// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_REVERIE_H
#define CONCEPTRODON_UNIT_TESTS_TEST_REVERIE_H

#include <concepts>
#include "conceptrodon/utilities/reverie.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestReverie {




/******************************************************************************************************/
/**** Items ****/
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<template<typename...> class...>
struct Warehouse_3;

/**** Operation ****/
template<template<template<typename...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedReverie = Reverie
<
    Warehouse_0, 
    Warehouse_1, 
    Warehouse_2, 
    Warehouse_3
>;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    Warehouse_0, 
    Warehouse_1, 
    Warehouse_2, 
    Warehouse_3
>;

/**** Result ****/
using Result = PackedReverie::Snow<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
static_assert(PackedReverie::size() == 4);
/******************************************************************************************************/




}}}

#endif