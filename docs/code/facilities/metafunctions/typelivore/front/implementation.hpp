/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Tyy ****/
template<typename Element>
struct Tyy
{
    using type = Element;
};

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/************************/
/**** Implementation ****/
/************************/

/**** Fore ****/
template<typename>
struct Fore {};

template<size_t...I>
struct Fore<std::index_sequence<I...>>
{
    template<template<typename...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the arguments from the front.
        Prefix<I> auto...targets,
        ...
    )
    -> Operation<typename decltype(targets)::type...>;
};

/**** Front ****/
template<typename First, typename...Elements>
struct Front
{
    template<size_t Amount>
    struct ProtoPage
    {
        template<template<typename...> class...Agreements>
        using Road = decltype
        (
            Fore<std::make_index_sequence<Amount>>
            ::template idyl<Agreements...>(Tyy<First>{}, Tyy<Elements>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<template<typename...> class Operation>
    struct Detail
    {
        using type = Operation<First>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;

    using type = First;
};

/***********************/
/**** First Example ****/
/***********************/

#include <concepts>

/**** SupposedResult ****/
using SupposedResult = int;

/**** Result ****/
using Result = Front<int, int*, int**, int**>::type;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);

/************************/
/**** Second Example ****/
/************************/

/**** Operation ****/
template<typename...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult_1 = Operation<int>;

/**** Result ****/
using Result_1 = Front<int, int*, int**, int**>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);

/***********************/
/**** Third Example ****/
/***********************/

/**** SupposedResult ****/
using SupposedResult_2 = Operation<int, int*, int**>;

/**** Result ****/
using Result_2 = Front<int, int*, int**, int**>::Page<3>::Road<Operation>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_2, Result_2>);