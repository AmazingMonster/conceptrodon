/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct Plume
{
    // Multiple Variables
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetics<Variables>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    // Multiple Variables
    // One Sequence
    template<template<auto...> class Cosmetic>
    struct ProtoRail<Cosmetic>
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetic<Variables>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};

template<auto Variable>
struct Plume<Variable>
{
    // One Variable
    // Multiple Sequences
    template<template<auto...> class...Cosmetics>
    struct ProtoRail 
    { 
        template<template<typename...> class Operation>
        struct Detail
        {
            using type = Operation<Cosmetics<Variable>...>;
        };

        template<template<typename...> class...Agreements>
        using Road = Detail<Agreements...>::type;
    };

    template<template<auto...> class...Cosmetics>
    using Rail = ProtoRail<Cosmetics...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <type_traits>
#include <concepts>

/**** Transformations ****/
template<auto I>
using ZeroStar = std::integral_constant<int, I>;

template<auto I>
using OneStar = std::integral_constant<int, I>*;

template<auto I>
using TwoStars = std::integral_constant<int, I>**;

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 0>**
>;

/**** Result ****/
using Result = Plume<0>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);

/************************/
/**** Second Example ****/
/************************/

/**** SupposedResult ****/
using SupposedResult_1 = Operation
<
    std::integral_constant<int, 0>*,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>*
>;

/**** Result ****/
using Result_1 = Plume<0, 1, 2>
::Rail<OneStar>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_1, SupposedResult_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation
<
    std::integral_constant<int, 0>,
    std::integral_constant<int, 1>*,
    std::integral_constant<int, 2>**
>;

/**** Result ****/
using Result_2 = Plume<0, 1, 2>
::Rail<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);