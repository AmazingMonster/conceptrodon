/************************/
/**** Implementation ****/
/************************/

template<auto...Variables> 
struct SensibleClassicPlume
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // Multiple Variables
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        struct Detail
        {
            using type = Operation
            <typename Cosmetics<Variables>::type...>;
        };

        // Multiple Variables
        // One Sequence
        template<template<auto...> class Cosmetic>
        struct Detail<Cosmetic>
        {
            using type = Operation
            <typename Cosmetic<Variables>::type...>;
        };

        template<template<auto...> class...Cosmetics>
        using Rail = Detail<Cosmetics...>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};


template<auto Variable>
struct SensibleClassicPlume<Variable>
{
    template<template<typename...> class Operation>
    struct ProtoRoad
    {
        // One Variable
        // Multiple Sequences
        template<template<auto...> class...Cosmetics>
        using Rail = Operation
        <typename Cosmetics<Variable>::type...>;
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

/***********************/
/**** First Example ****/
/***********************/

#include <type_traits>
#include <concepts>

/**** Transformations ****/
template<auto I>
struct ZeroStar
{ using type = std::integral_constant<int, I>; };

template<auto I>
struct OneStar
{ using type = std::integral_constant<int, I>*; };

template<auto I>
struct TwoStars
{ using type = std::integral_constant<int, I>**; };

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
using Result = SensibleClassicPlume<0>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

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
using Result_1 = SensibleClassicPlume<0, 1, 2>
::Road<Operation>
::Rail<OneStar>;

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
using Result_2 = SensibleClassicPlume<0, 1, 2>
::Road<Operation>
::Rail<ZeroStar, OneStar, TwoStars>;

/**** Test ****/
static_assert(std::same_as<Result_2, SupposedResult_2>);