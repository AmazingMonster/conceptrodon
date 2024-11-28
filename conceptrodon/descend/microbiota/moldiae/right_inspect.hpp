// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOLDIAE_RIGHT_INSPECT_H
#define CONCEPTRODON_MOLDIAE_RIGHT_INSPECT_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Moldiae {

template<typename>
struct RightInspect {};

template<size_t...I>
struct RightInspect<std::index_sequence<I...>> 
{
    template<template<typename...> class Predicate, Prefix<I>..., typename OnDuty, typename...RestElements>
    static consteval auto idyl()
    -> std::bool_constant<(...&&Predicate<RestElements, OnDuty>::value)>;
};

}}

#endif