/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Label ****/
template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
};

/************************/
/**** Implementation ****/
/************************/

/**** VoidPointer ****/
template<auto>
using VoidPointer = void*;

/**** Midst ****/
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    // We use `VoidPointer<I>...` to enumerate unwanted arguments.
    static constexpr auto idyl(VoidPointer<I>..., auto* target, auto*...)
    { return target; }
};

/**** Amidst ****/
template<typename...Elements>
struct Amidst
{
    template<size_t I>
    struct Detail
    {
        using type = decltype
        (
            Midst<std::make_index_sequence<I>>
            ::idyl(static_cast<Elements*>(nullptr)...)
        );
    };

    template<auto...Agreements>
    using Page = std::remove_pointer_t
    <typename Detail<Agreements...>::type>;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** SupposedResult ****/
using SupposedResult = int***;

/**** Result ****/
using Result = Amidst<int, int*, int**, int***>::Page<3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
