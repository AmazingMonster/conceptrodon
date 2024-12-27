/**********************/
/**** Dependencies ****/
/**********************/

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** ExtendBack ****/
// We will use this function to
// concatenate the preserved and recursed parts.
template<typename...>
struct ExtendBack {};

template<
    template<auto...> class Sequence,
    auto...Variables
>
struct ExtendBack<Sequence<Variables...>>
{
    template<auto...Agreements>
    using Page = Sequence<Variables..., Agreements...>;
};

/**** TypicalReiterate ****/
template<auto...Variables>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Shuttle<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Shuttle<Variables...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Page<Variables..., Variables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct Reiterate
{
    template<auto...Agreements>
    using Page = TypicalReiterate<Variables...>
    ::template Page<Agreements...>
    ::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Shuttle ****/
template<auto...>
struct Shuttle;

/**** SupposedResult ****/
using SupposedResult = Shuttle<
    0, 1,
    0, 1,
    0, 1,
    0, 1
>;

/**** Result ****/
using Result = Reiterate<0, 1>
::Page<4>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);