// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_UNIT_TESTS_TEST_VEHICLE_H
#define CONCEPTRODON_UNIT_TESTS_TEST_VEHICLE_H

#include <concepts>
#include "conceptrodon/utilities/vehicle.hpp"

namespace Conceptrodon {
namespace UnitTests {
namespace TestVehicle {




/******************************************************************************************************/
/**** Items ****/
template<typename...>
struct Container_0;

template<typename...>
struct Container_1;

template<typename...>
struct Container_2;

template<typename...>
struct Container_3;

/**** Operation ****/
template<template<typename...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedVehicle = Vehicle
<
    Container_0, 
    Container_1, 
    Container_2, 
    Container_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Container_0, 
    Container_1, 
    Container_2, 
    Container_3
>;

/**** Result ****/
using Result = PackedVehicle::Flow<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
static_assert(PackedVehicle::size() == 4);
/******************************************************************************************************/




}}}

#endif