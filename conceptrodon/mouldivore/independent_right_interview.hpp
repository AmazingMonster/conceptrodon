// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_INDEPENDENT_RIGHT_INTERVIEW_H
#define CONCEPTRODON_MOULDIVORE_INDEPENDENT_RIGHT_INTERVIEW_H

#include "conceptrodon/microbiota/moldiae/right_interview.hpp"

namespace Conceptrodon {
namespace Mouldivore {

template<template<typename...> class...Containers>
using IndependentRightInterview = Moldiae::RightInterview<Containers...>;

}}

#endif