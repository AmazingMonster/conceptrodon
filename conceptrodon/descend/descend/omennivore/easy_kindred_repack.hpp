// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EASY_KINDRED_REPACK_H
#define CONCEPTRODON_OMENNIVORE_EASY_KINDRED_REPACK_H

#include "conceptrodon/descend/omennivore/concepts/all_moldful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_roadful.hpp"
#include "conceptrodon/descend/omennivore/concepts/all_railful.hpp"
#include "conceptrodon/descend/cotanivore/kindred_repack.hpp"
#include "conceptrodon/descend/sequnivore/kindred_repack.hpp"
#include "conceptrodon/descend/warehivore/kindred_repack.hpp"
#include "conceptrodon/descend/stockivore/kindred_repack.hpp"

namespace Conceptrodon {
namespace Omennivore {

template<typename...Packages>
struct EasyKindredRepack
: public Sequnivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires AllMoldful<Packages...>
struct EasyKindredRepack<Packages...>
: public Cotanivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires AllRoadful<Packages...>
struct EasyKindredRepack<Packages...>
: public Warehivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires AllRailful<Packages...>
struct EasyKindredRepack<Packages...>
: public Stockivore::KindredRepack<Packages...>
{};

}}

#endif