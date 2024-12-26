/**********************/
/**** Dependencies ****/
/**********************/

/**** ExtendBack ****/
template<typename...>
struct ExtendBack {};

template<
    template<typename...> class Container,
    typename...Elements
>
struct ExtendBack<Container<Elements...>>
{
    template<typename...Agreements>
    using Mold = Container<Elements..., Agreements...>;
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** TypicalReiterate ****/
template<typename...Elements>
struct TypicalReiterate
{
    template<auto...>
    struct ProtoPage {};

// Base Case:
    template<auto I>
    requires (I == 0)
    struct ProtoPage<I>
    {
        using type = Capsule<>;
    };

    template<auto I>
    requires (I == 1)
    struct ProtoPage<I>
    {
        using type = Capsule<Elements...>;
    };

// Recursive Case:
    template<auto I>
    requires (2 <= I)
    struct ProtoPage<I>
    {
        using type = ExtendBack<typename ProtoPage<I - 2>::type>
        ::template Mold<Elements..., Elements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct Reiterate
{
    template<auto...Agreements>
    using Page = TypicalReiterate<Elements...>
    ::template Page<Agreements...>
    ::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<
    int, int*,
    int, int*,
    int, int*,
    int, int*
>;

/**** Result ****/
using Result = Reiterate<int, int*>
::Page<4>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);