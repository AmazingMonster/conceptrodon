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