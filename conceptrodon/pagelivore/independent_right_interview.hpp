// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_PAGELIVORE_INDEPENDENT_RIGHT_INTERVIEW_H
#define CONCEPTRODON_PAGELIVORE_INDEPENDENT_RIGHT_INTERVIEW_H

#include "conceptrodon/microbiota/pagelis/right_interview.hpp"

namespace Conceptrodon {
namespace Pagelivore {

template<template<auto...> class...Sequences>
using IndependentRightInterview = Pagelis::RightInterview<Sequences...>;


}}

#endif