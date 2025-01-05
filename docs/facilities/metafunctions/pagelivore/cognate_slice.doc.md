<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateSlice`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-slice">To Index</a></p>

## Description

`Pagelivore::CognateSlice` accepts an operation.

- Suppose its first layer is instantiated with an index.
In that case, it returns a function.
When invoked, the function collects all arguments with indices greater or equal to the given index from its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I-1</sub>, Arg<sub>I</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>I</sub>, ..., Arg<sub>n</sub>&gt;</code></pre>

- Suppose its first layer is instantiated by two indices, which indicate a left-closed-right-open interval.
In that case, it returns a function.
When invoked by an operation, the function collects all arguments of indices within the interval from its argument list and instantiates the operation with the collection.

<pre><code>   Oper
-> I, J
-> Arg<sub>0</sub>, Arg<sub>1</sub>, ..., Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>, ..., Arg<sub>n</sub>
-> Oper&lt;Arg<sub>I</sub>, ..., Arg<sub>J-1</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateSlice
 :: template<auto...> class...
 -> auto...
 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
alias CognateSlice
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};


template<template<auto...> class>
alias CognateSlice
{
    template<auto, auto>
    alias Page
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will see two examples that demonstrate two different use cases.

- In the first example, we will collect all variables from `0, 1, 2 ,2` starting from index two.
Then, we instantiate `Operation` with the resulting list.

```C++
/**** Operation ****/
template<auto...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<2, 2>;

/**** Result ****/
using Result = CognateSlice<Operation>
::Page<2>
::Page<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult, Result>);
```

- In the second example, we will collect variables between indices one and three from `0, 1, 2, 2`. Then, we instantiate `Operation` with the resulting list.

```C++
/**** SupposedResult ****/
using SupposedResult_1 = Operation<1, 2>;

/**** Result ****/
using Result_1 = CognateSlice<Operation>
::Page<1, 3>
::Page<0, 1, 2, 2>;

/**** Test ****/
static_assert(std::same_as<SupposedResult_1, Result_1>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` as in the implementation of `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `CognateSlice` using concept expansion.

We will expand the constraint `Prefix<***>` alongside the arguments.

```C++
template<typename, auto>
concept Prefix = true;
```

We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

- In the case where the second layer of `CognateSlice` only accepts an amount, we want to remove the variables of the given amount from the front of the list.

```C++
template<typename>
struct Shear {};

template<size_t...I>
struct Shear<std::index_sequence<I...>>
{
    template
    <
        template<auto...> class Operation,
        typename...Targets
    >
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the uwanted arguments.
        Prefix<I> auto...,
        // Collect the rest.
        Targets...
    )
    -> Operation<Targets::value...>;
};
```

- In the case where the second layer of `CognateSlice` accepts two indices, we want to collect the variables between them.

```C++
template<typename, typename>
struct Incise {};

template<size_t...I, size_t...J>
struct Incise<std::index_sequence<I...>, std::index_sequence<J...>>
{
    template<template<auto...> class Operation>
    static consteval auto idyl
    (
        // Expand `Prefix<I>` to count the uwanted arguments.
        Prefix<I> auto...,
        // Expand `Prefix<J>` to collect the proper number of arguments.
        Prefix<J> auto...targets,
        // Remove the rest.
        ...
    )
    -> Operation<decltype(targets)::value...>;
};
```

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<template<auto...> class Operation>
struct CognateSlice
{
    template<size_t...>
    struct ProtoPage {};

    template<size_t Amount>
    struct ProtoPage<Amount>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Shear<std::make_index_sequence<Amount>>
            ::template idyl<Operation>(Vay<Variables>{}...)
        );
    };

    template<size_t Start, size_t End>
    requires (Start <= End)
    struct ProtoPage<Start, End>
    {
        template<auto...Variables>
        using Page = decltype
        (
            Incise
            <
                std::make_index_sequence<Start>,
                std::make_index_sequence<End-Start>
            >
            ::template idyl<Operation>(Vay<Variables>{}...)
        );
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEEgDM/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJXCm2mPalDEIETMQEeT5%2BQfWNOS1tBOXRcQnJqQqt7Z0FPZODw5XV4wCUtqhexMjsHAD0AFSHR8cnp/u7JhoAggdHANQAIphprozIeJgKd8cX17dnAJOvyulxBZiSEWQ3iwdxMSTcXkctEIAE84dhQeYIQwoV4YXC3MhJugsFR0Zi/sc7spiJgaKpvkdgQRMCw0gYWQSCCiXsw2KQ7kxEahydc0DjngRqbT6bCkg87gRiF5MHCrNdQf99ncAGpMFGMw7M1nspic%2BFCoi6tp4Jixeiiq6TZUOa1ojWBCx3eaOZB3cWTTCqNLEQXCu4ANzEKthnr1xFt9tVgQeatjqaS6pBlMBuZ%2BmqpAEk2fQ2IIzTlDecC3na8Ca4c7kIEJg2lXjSWzar4dzeaxuxjrs6vK7m63QyZPZOM1nQSzO%2Ba3FkAF6YAD6BAAdNvC47h6OW20CcSQCAIlhVGulABHFUSgmF7eb8lJQcgqfXO5fxUmjmqz/fgSoLfiBP4Lt2biWqgT7ov6BgKF8ADyLzEBWAikMBoFfr2jD9k%2BAAqbTAJgBAKJhX6OiBPp4H6AYslGtBhlaeDoCitDkXcEAcSBuy7Hc2DBoY6CwgAbBoNJ0ngqgPuSYmKqg/obIIiotncXgAO6GCywlET4jCkc%2BAFYRJ9Iya%2BTHQduGFGaBvF3HkjQqZgdy0pMhlXFhX6EcQxEGduHErBxAC0sHIQkaEMAS3m%2BQop4MSqMGvmqmIpslGo5o2hY4ngSjtnOv5dlyPK4fyirFXyA6gvuUpZe8uWTlYqWZhSVzzqai4ruuW47gKnUbk%2BABSe5KiONXZUox4EOgp7nkGV6YLebwQY%2B/mvr1U0zQwF7zYt97wgNiUYklHpZiBbV/lyBWLlBh1wUwCF3GFqFNJR37UbRAiBgxFl3CxbEcVxNk8XxAlpEJoniTKUlmRiclWmgXjKQQqkaVpmA6T5emCAo7medKknSfCu7mTdVncd%2Bdmg%2BDJhiSZ0P7bJGjyYptCOcjzkhqgKF3AwoyhqgVCCpjZYGeTX504TbhDSTwpPlMMXWR5nl2QASqyqARs57MuZ8W5i3cME2YFNkheZT0RQSWBQjhEDyyRCgrHF0aYIdaXvjOLVavZqDAMwLJCMi2x5dc52FT2V0QaTz7mVC91IShFvHU6I2uh4vtdgHNH/u%2Bp3fqHHV4Ku/WrW%2BVEp1KNKoEQyhMMRsaNR76VK9hEfHoXXV3FcLBKQQr1ftV0pV6gNfEQSXc9339f6/nkey9u8aJvQZFJ3jXhZEY1K185cIKlbtA4frgPN3jTaHsQk3TSALBMAA1uus2Xjed7bGP3eI73SUryfX6njPv2sexeE5sXqvggHqNE8IF52iXuSKcKYnzG2PiBQKzUbLTjdhxGebci5SgGO0Xq7cNz8S2pPWkt48CuU4ngqUQF5TEPQIgsuLoK7ECHiPCC1CBTYBIV/CiH4kF51bhaOem4oFJmXqXTya8IjAE3nXHedw94HyBt%2BI%2B38vy1RytndRco3D6zxieK%2Bt975bTmk/JaBJqHokVjosul9r53zXA/Haz8ILcPQEFKxvCT6Tzxr/CO/9/pAITiA7AYD9QEjETApKcCHgIP1ig3OfDG7ZmPlg4RRAnxXGALSVk%2BkJEcWkRvdhcoFSV2rlvMeOTMB5Oxq7VB7sMEZVrACYEXsABiFDJj8VUKwdkzl8zNJaacesGpwSQmhNveE4pthpFIo6Bs2pgGVkGa1IRkERHDWYY9EJOQmk3CpEILwaRijozVgoLw%2B9g5XCKbIo5JzMhnM%2BJcmhdDlkCAJGYAUZgXyzmaXcc5Lzrm3IBc8q5Ci05%2B0wJnF%2BwTwqhNBKedhnzHRIsqfCDQAouDfO%2Bb8z2VJ8K62ue9NcccEgEAgIYhQ/ZSXLzcPc056BAX7wFMyj%2B2BEn4uGYCNphzMDimEgJPp9Brlam5UCLljYGWPKZWCqUqyQXSqULKi5%2B81xcFKTs%2BFez4TYruD8z%2BfyDn3DZcC9esi2Xqs1ZCjOgcILvMiknNFo9dUCiSKikAyKMVYpxfqvFTcvaEu6asklZL2iUo2iAalbBaWWOOYyy1erE3okSRwNYtBOD%2BF4H4DgWhSCoE4Hoyw1hvQbC2NvcEPBSAEE0GmtYN8AiSE3BoAAHGYMwABODtXB/CtpbVwQIgRpAZo4JIXgLAJAaExTmvNBaOC8Fipimtua02kDgLAGAiAQAbAIGkRE5BKBoDZHQBIUR%2BycFUC2kSQURKSDuMAZAfopCbjMLwdGhASAsT0PwQQIgxDsCkDIQQigVDqBXaQXQ2L1KoTSJwHg6bM3ZtrfmzgiFER7qlALO4l7r23vvY%2Bu4z6zCcQ8Me%2BgE5K0rF4MurQawIBICPWkE9ZAKAQEY8xkAwApBfJoPvBIsUICxGQ7ECIbQURwd4CJ5gxAUSIViNofly6q1HpFohBgtBxPgawLELwwBIKs1itwXgWBr5GHEFpihim8Ca0M3moM/LEQ7CrREFkI683IliKhGTHgsDIaVHgCdRnSCa2ILER5TxTPAGREYWtawqAGGAAoHUHx1JhRzVWn9whRDiEA5lkDahkOQf0IYYw1hrD6DwLEWKkA1hcyaIZoKxId6mGLZYMws6QsJiwNViAaw7BWecBAVwMw/DYrCBEEYVQxjYuKNkAQI29CzaaIsPmeh%2BsOH6FMDonguhrYaAN5oW2VtTZqLYLbC3sXzHaMd5YXA%2Btlu2BIBDHAs2kBnbwOd2Gr03rvQ%2Bp9TbiMQFwB%2BijSQ7vUdi2sQ8WBEi9dIA2yQSRNwdqSEOjQkgzCSDEhofwIkO36E4GO0gE6webhElwESLaO39pEv4SQPaUciTe8hudC6QBLti2uzd9Ht3of3ax9j5Gz1sE4G0FgEZAhBSYHdDeXAO2bi4M2t9%2BAiBde/bIP9OXpB5aUAV8DugvnQaYLBozz3XvvZQxwNDu7ER3Cwzhn7MvZFy4V82kjqAyMJFhOCMwVHq2c554LhIB62Me6Y%2BRlABgjBy64Ji3jLJiACaE%2BBqTYmJOkFTzJuTCmHDp5U/pNTGnkPad0/p2ghmq0mZK%2BZvN%2BBaQbZs8h%2BzyBHPp5cw0ZDHmvMoh8zsPN/nAtVpC2FpQEXq8yM5/F2uSWUtpfT5lzXAHteyHy2BvNBvisxZa1YSwFWqvwFq3MnIDWmvym39YdrH3OssU%2BAf3oB2XBbQuyELaN3pvpEyHN3IO2Cgzc/8tibJYd/dbJoahZ/EAzbBYQA1bS7c7H/UbM7KAioGA%2B7TYR7O7AnF7JDcDT7B3PDWOWXeXRXJmIHFXEgb3MHP3GjOtUgaHMYOHEdInEneXdHQIfwDtQdJIDHLHenZnHAzgNnDnFdOjbnJAHdDDEPIPYgYXHYMXPDFgBQCMP0CMF3P8SYZXEHL9bFBfbLJfIDeQXXNfHQEAJIUgI3E3eDTA83FnVDPnTDQWVQeQxQ5Q1QrsbpCAUjcPL3LEJIKggPBjMPZjSQwIiPJQk5NcFQjtNcNQggNcRw7XOgBPJPYTUTGTdPTPWTeTRTPPD3VTdTTTWvTAHTPTMQcvdPKvMzPvYzSzBvW/cDZvVvILdvNzXgLvMTXvPzBMQfXgYfcLVkcfGLYQvgBLGfTAVLXkefDXXQiQZfYDQwwrEwzfUrVrGwDzHrQ/erTgXYE8c/NrDrBILrW/Gre/DbQbYbeAvQcbZAk7Rbf/HIZ/JbHIN/U7CAgQMAi4y7fbU4w7JAybW7RA6YD4gEoYaAm4jAhQB7ADM3bA2dTgbDJwpQyMVwlkdw4HVXCg8Hf3YQqHVsGHSgZ7JgkATtTcJIFIXtenKdUkwISnPg2E%2BdWwdnLE2jetEASQfwZHAdQIKdFtSQbtLgNtMwJnEdJIGEj7AQpkmgkdV9WksU%2Bk6glYNYELLIZwSQIAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/pagelivore/cognate_slice/implementation.hpp)
- [Source code](../../../../conceptrodon/pagelivore/cognate_slice.hpp)
- [Unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_slice.test.hpp)
