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

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Cotanivore::TypicalPaste ****/
namespace Cotanivore {

template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedContainer>
struct TypicalPaste<PackedContainer>
{
    using type = PackedContainer;
};

// Recursive Case:

template
<
    template<typename...> class ContainerA,
    template<typename...> class ContainerB,
    typename...ElementAs, 
    typename...ElementBs,
    typename...Others
>
struct TypicalPaste<ContainerA<ElementAs...>, ContainerB<ElementBs...>, Others...>
{
    using type = TypicalPaste
    <
        ContainerA<ElementAs..., ElementBs...>,
        Others...
    >::type;
};

}

/**** TypicalConjureSet ****/
template<typename...Elements>
struct TypicalConjureSet
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    {
        template<typename Inspecting, typename...BackArgs>
        static consteval auto idyl
        (
            Prefix<I> auto...,
            Inspecting,
            BackArgs...
        )
        -> std::conditional_t
        <
            (...||std::is_same_v<Inspecting, BackArgs>),
            Capsule<>,
            Capsule<typename Inspecting::type>
        >;
    };

    template<typename>
    struct Hidden {};

    template<size_t...I>
    struct Hidden<std::index_sequence<I...>>
    {
        using type = Cotanivore::TypicalPaste
        <
            decltype
            (
                Detail<std::make_index_sequence<I>>
                ::idyl(Tyy<Elements>{}...)
            )...
        >::type;
    };

    using type = Hidden<std::make_index_sequence<sizeof...(Elements)>>::type;
};

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
using ConjureSet = TypicalConjureSet<Elements...>::type;

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = ConjureSet<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);