// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_INDEPENDENT_FIND_H
#define CONCEPTRODON_MOULDIVORE_INDEPENDENT_FIND_H

#include "conceptrodon/microbiota/moldiae/find.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class...Containers>
using IndependentFind = Moldiae::Find<Containers...>;

}}

#endif