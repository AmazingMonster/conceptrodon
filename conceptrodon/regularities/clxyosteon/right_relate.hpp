// Copyright 2026 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_CLXYOSTEON_RIGHT_RELATE_H
#define CONCEPTRODON_CLXYOSTEON_RIGHT_RELATE_H

#include <type_traits>
#include <memory>
#include "conceptrodon/concepts/mouldivore/confess.hpp"

namespace Conceptrodon {
namespace Clxyosteon {

template<template<typename...> class...>
struct RightRelate {};

template<template<typename...> class Predicate>
struct RightRelate<Predicate>
{
    template<typename Left>
    struct ProtoMold
    {
        struct DetectorConcept
        {
            virtual bool idyl() = 0;
            virtual ~DetectorConcept() = default;
        };

        template<typename Right>
        struct Detector
        : public DetectorConcept
        {
            bool idyl() override
            { return false; }
        };

        template<typename Right>
        requires Conceptrodon::Mouldivore::Confess<Predicate, Left, Right>
        struct Detector<Right>
        : public DetectorConcept
        {
            bool idyl() override
            { return true; }
        };

        template<typename Right>
        struct BrokenDetector
        : public DetectorConcept
        {
            bool idyl() override
            { return Right::value; }
        };
        
        template<typename Right>
        ProtoMold(std::type_identity<Right>)
        : detector {std::make_unique<Detector<Right>>(Detector<Right>{})} {}
        
        ProtoMold(std::true_type)
        : detector {std::make_unique<BrokenDetector<std::true_type>>(BrokenDetector<std::true_type>{})} {}
        
        ProtoMold(std::false_type)
        : detector {std::make_unique<BrokenDetector<std::false_type>>(BrokenDetector<std::false_type>{})} {}

        bool operator()()
        { return detector -> idyl(); }

        std::unique_ptr<DetectorConcept> detector;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

}}

#endif