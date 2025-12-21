// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_CARRIER_H
#define CONCEPTRODON_UNIT_TESTS_TEST_CARRIER_H

#include <concepts>
#include "conceptrodon/utilities/carrier.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestCarrier {




/******************************************************************************************************/
/**** Items ****/
template<auto...>
struct Sequence_0;

template<auto...>
struct Sequence_1;

template<auto...>
struct Sequence_2;

template<auto...>
struct Sequence_3;

/**** Operation ****/
template<template<auto...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedCarrier = Carrier
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Sequence_0, 
    Sequence_1, 
    Sequence_2, 
    Sequence_3
>;

/**** Result ****/
using Result = PackedCarrier::Sail<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
static_assert(PackedCarrier::size() == 4);
/******************************************************************************************************/




}}}

#endif