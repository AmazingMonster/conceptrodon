/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

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

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct TypicalConjureSet
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    {
        template<typename Inspecting>
        static consteval auto idyl
        (
            Prefix<I> auto...front_args,
            Inspecting,
            ...
        )
        -> std::conditional_t
        <
            (...||std::is_same_v<Inspecting, decltype(front_args)>),
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
                ::idyl(std::type_identity<Elements>{}...)
            )...
        >::type;
    };

    using type = Hidden<std::make_index_sequence<sizeof...(Elements)>>::type;
};

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
using Result = TypicalConjureSet<int, int*, int**, int**>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);