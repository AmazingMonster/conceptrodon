/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Vay ****/
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};

/************************/
/**** Implementation ****/
/************************/

/**** Prefix ****/
template<typename, auto>
concept Prefix = true;

/**** Midst ****/
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    // We use `Prefix<I> auto...` to enumerate unwanted arguments.
    static constexpr auto idyl(Prefix<I> auto..., auto target, auto...)
    { return target; }
};

/**** Amidst ****/
template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value 
        {
            std::remove_pointer_t
            <
                decltype
                (
                    Midst<std::make_index_sequence<I>>
                    ::idyl(static_cast<Vay<Variables>*>(nullptr)...)
                )
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<auto...Args>
using At = Amidst<0, 1, 2, 3>::Page<Args...>;

/**** Test ****/
static_assert(At<3>::value == 3);