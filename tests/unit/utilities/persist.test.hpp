// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_PERSIST_H
#define CONCEPTRODON_UNIT_TESTS_TEST_PERSIST_H

#include <concepts>
#include "conceptrodon/utilities/persist.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestPersist {




/******************************************************************************************************/
/**** Items ****/
template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<auto...> class...> class...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedPersist = Persist
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
using Result = PackedPersist::Dawn<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
static_assert(PackedPersist::size() == 4);
/******************************************************************************************************/




}}}

#endif