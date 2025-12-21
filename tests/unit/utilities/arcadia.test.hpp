// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_ARCADIA_H
#define CONCEPTRODON_UNIT_TESTS_TEST_ARCADIA_H

#include "conceptrodon/utilities/arcadia.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestArcadia {




/******************************************************************************************************/
/**** Items ****/
template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_0;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_1;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_2;

template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
struct Item_3;

/**** Packed Vessel ****/
using PackedArcadia = Arcadia
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Test ****/
static_assert(PackedArcadia::size() == 4);
/******************************************************************************************************/




}}}

#endif