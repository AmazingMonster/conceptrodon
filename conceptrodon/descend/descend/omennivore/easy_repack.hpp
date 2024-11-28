// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_EASY_REPACK_H
#define CONCEPTRODON_OMENNIVORE_EASY_REPACK_H

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
struct EasyRepack
: public Sequnivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires AllMoldful<Packages...>
struct EasyRepack<Packages...>
: public Cotanivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires AllRoadful<Packages...>
struct EasyRepack<Packages...>
: public Warehivore::KindredRepack<Packages...>
{};

template<typename...Packages>
requires AllRailful<Packages...>
struct EasyRepack<Packages...>
: public Stockivore::KindredRepack<Packages...>
{};

}}

#endif