// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_PURSUIT_H
#define CONCEPTRODON_UNIT_TESTS_TEST_PURSUIT_H

#include <concepts>
#include "conceptrodon/utilities/pursuit.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestPursuit {




/******************************************************************************************************/
/**** Items ****/
template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<typename...> class...> class...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedPursuit = Pursuit
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Result ****/
using Result = PackedPursuit::Glow<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
static_assert(PackedPursuit::size() == 4);
/******************************************************************************************************/




}}}

#endif