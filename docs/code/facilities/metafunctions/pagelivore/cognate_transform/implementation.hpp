/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct CognateTransform
{
    template<template<auto...> class...Puberty>
    struct ProtoRail
    {
        struct Slash
        {
            template<template<auto...> class Hormone>
            struct ProtoRail
            {
                template<auto Variable>
                struct Hidden 
                {
                    static constexpr auto value
                    {Variable};
                };

                // `Puberty...` are the predicates.
                // This partial specialization will be selected
                // if `(...&&Puberty<Variable>::value) == true`.
                template<auto Variable>
                requires (...&&Puberty<Variable>::value)
                struct Hidden<Variable>
                {
                    // `Hormone` is the transformation.
                    static constexpr auto value
                    {Hormone<Variable>::value};
                };

                template<auto...Variables>
                using Page = Operation<Hidden<Variables>::value...>;
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = Slash::template ProtoRail<Agreements...>;
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** DivisibleByTwo ****/
template<auto I>
struct DivisibleByTwo
{
    static constexpr bool value
    {I % 2 == 0};
};

/**** DivisibleByThree ****/
template<auto I>
struct DivisibleByThree
{
    static constexpr bool value
    {I % 3 == 0};
};

/**** UnaryMinus ****/
template<auto I>
struct UnaryMinus
{
    static constexpr auto value
    {-I};
};

/**** Operation ****/
template<auto...>
struct Operation;

/**** Metafunction ****/
template<auto...Args>
using Metafunction = CognateTransform<Operation>
::Rail<DivisibleByTwo, DivisibleByThree>
::Rail<UnaryMinus>
::Page<Args...>;

/**** SupposedResult ****/
using SupposedResult = Operation<1, -12, 2, -6, 15>;

/**** Result ****/
using Result = Metafunction<1, 12, 2, 6, 15>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);