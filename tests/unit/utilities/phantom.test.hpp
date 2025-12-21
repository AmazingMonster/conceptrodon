// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_PHANTOM_H
#define CONCEPTRODON_UNIT_TESTS_TEST_PHANTOM_H

#include "conceptrodon/utilities/phantom.hpp"
#include <concepts>

namespace Conceptrodon {
namespace UnitTests {
namespace TestPhantom {




/******************************************************************************************************/
/**** Items ****/
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

template<template<auto...> class...>
struct Stockroom_3;

/**** Operation ****/
template<template<template<auto...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedPhantom = Phantom
<
    Stockroom_0, 
    Stockroom_1, 
    Stockroom_2, 
    Stockroom_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Stockroom_0, 
    Stockroom_1, 
    Stockroom_2, 
    Stockroom_3
>;

/**** Result ****/
using Result = PackedPhantom::Hail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
static_assert(PackedPhantom::size() == 4);
/******************************************************************************************************/




}}}

#endif