// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIS_RIGHT_INSPECT_H
#define CONCEPTRODON_PAGELIS_RIGHT_INSPECT_H

#include "conceptrodon/prefix.hpp"
#include <utility>

namespace Conceptrodon {
namespace Pagelis {

template<typename>
struct RightInspect {};

template<size_t...I>
struct RightInspect<std::index_sequence<I...>> 
{
    template<template<auto...> class Predicate, Prefix<I>..., typename OnDuty, typename...RestVariables>
    static consteval auto idyl()
    -> std::bool_constant<(...&&Predicate<RestVariables::value, OnDuty::value>::value)>;
};

}}

#endif