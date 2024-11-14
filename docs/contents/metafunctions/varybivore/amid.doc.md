<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Amid`

## Description

`Varybivore::Amid` accepts a list of variables and returns a function. When invoked by an index, the function returns the variable at the index from the list.

<pre><code>...Variable<sub><i>i</i></sub>... -> I -> Variable<sub><i>i</i></sub></code></pre>

## Type Signature

```Haskell
Amid :: auto... -> auto... -> auto
```

## Structure

```C++
template<auto...>
struct Amid
{
    template<auto>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };

    template<auto>
    static constexpr auto Page_v
    {RESULT};
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
static_assert(Amid<0, 1, 2, 3>::Page<3>::value == 3);
```

## Implementation

We will label each variable by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding variable from the roster.

First, we need to create a label class.
We will pack each variable into a `Monotony` so that we can use it as a return type:

```C++
template<auto Variable>
struct Monotony
{ static constexpr auto value {Variable}; };

template<auto Variable, size_t I>
struct Stamp
{ 
    static constexpr auto idyl
    (std::integral_constant<size_t, I>) -> Monotony<Variable>;
};
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by `std::integral_constant<size_t, I>`.
Here, we convert an index into a type via `std::integral_constant` for argument-dependent lookup.

Now, we will assemble an overload set and instruct compilers to pull the variable out when provided with an index. Here's the entire implementation:

```C++
template<auto...Variables>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Stamp<Variables, I>...
    {
        // We bring every `idyl` from its base class to the current scope.
        using Stamp<Variables, I>::idyl...;
    };

    template<size_t I>
    struct ProtoPage
    {
        // We ask the compiler to find an `idyl` that
        // declares a parameter of type `std::integral_constant<size_t, I>`.
        // If found, the value result of the return type
        // of such `idyl` is the variable of index I in the list.
        static constexpr auto value 
        {
            decltype
            (
                Detail<std::make_index_sequence<sizeof...(Variables)>>
                ::idyl(std::integral_constant<size_t, I>{})
            )::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCCSAJykAA6oCoRODB7evnppGY4CoeFRLLHxkma2mPZFDEIETMQEOT5%2BgXaYDlmNzQQlkTFxCckKTS1teVy2EwNhQ%2BUjVQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeZ9gmGgCCewdHmKfnyOPoWFT3jxezwImBYKQMILObiYl1QxwAas08ExovQAc9xsQvA5jgBZASoIgMO7PEwAdgsx3GTEcyGOaAY40wqhSxGOMKIxwAbmIvB9yRZEcRkajMOSACJnSkSqWAwEgsEQsXnDlwoUi%2BikKl4ABemAA%2BgRjgBJdFPTHYo19MFyimnZ7HR1Upq0%2BkCJkstmq454dA3WiAp3HCA/EAgMIg4DEMT6hnUwRQjJ6w1a03%2BbArY4AWnueIJRLu53VKLR6dlpLJkv8VlJwNB4JpyuhsIAdG3i6KFGaLTinixfbaa08gwqG5DzgQbilGKxlQ8HU6e0bxZgmnRThSZdW5QvHaOlYndQaCG2W2n58PFwQsTiV2uA%2BdQ%2BGGFhVPqlABHPkMbZQ42ngEy13Y4AHoQOOAB1D5kGITBG3ZBhjlQLk4loVAmHQKlVyQqhTgANg0X1/RMAjjgIBBiA2YAEB9BgEDiQhDG2FtAydEBjhSLxUTwOlrRSKEO3oBRU3uADgIFVig0dMDII%2BaJhSMY5MBQ4gbnwwi/QDUiqEolgfQIBRjmiJglHpAwFEMzlyOgzZYMEKk0GnFjgKDLwMkUviBKREtMGEk17jDIjaAA7dxMrcsgUvPd6wPR8j0NfygKi50byNZRKKIZQmGAMUwqHKSnRkqD2QUABrMj6LdME6DiMi4RoF8EPUoKSI0CqaUkqSZKwQ5ml89kOOaWcQTZVBcMnad1KfCNMCjGM4yaBM4uTAgRLLAjnOSoMZONXD%2BC8F8tWs7leQ%2BWCFC8WgjTGiqztXTZEIm3KtsK8Cbou5AaNalrSLwSzKp5YUfJw2jXxNWjbuOa5xk2grHWpV0FuZVl2VhE7vH5FynQkrGCp6q6p2euGpIgTriaDO8mDoRMCHQMMWCYUqDTCV930wL9GF/ZbMDG08IEE3yVkAi9ybhwLNJDWnAsEWbo1oWN3UWghDxWtaHk3SshdxqSVjDHkMbJ7HwtC5KtyHTr90bKFVVPJ4o0wUFGAMs1XPc4BjiynLPnFD2MtQT2mzt2DHcEBQQoeE2zZ3J4QIAKnjhPE5AwE4/jgAVbAhDThPk%2BeVPE6T6PXh/d5PjcBlthSZ2ksBBGeP1EylBaCA%2BwHc4NC1GZjmqY5/ACkAA6hPv0z107vbOH3/CFk2ODWWhOAAVl4PwOC0UhUE4NxrGsKkNi2fkzH8HhSAITRZ7WUqQAXyQWw0SQuDJfwNAXjQzDwvCzAADk//ROEkXgWASA0B3Fea8N4cF4AoEAHdT6r1nqQOAsAYCIBABsAgnFVoUAgGgaq9BiARFnJwVQn88JZjwpIY4wBkB0ikC2MwvBMD4CIMKOmMx%2BCCBEGIdgUgZCCEUCodQcDSC6BmAAd2jCkTgPA56L2XmfdenAADylwMEg2IaQ8hlDqHHFoWYYMHhcG1T2FwFYvBYFaDWBAJAOCUg1TIFgmxdiQDACkNUGgV04hQIgNEeR0QwjNBuFI3gfjmCqUUdEbQ3RYHHxwWwQQiiGC0ECUIrA0QvDAGhLQWgUDuC8CwAzIw4gUl4Fgj0FCOS17Mm6JcHYx8ZrzyEdceSASPBYHkdePAgDcmkBUtEdImAVwFOANcIwZ81hUAMMABQ8I8CYFEYo6cK9j7sOEKIcQPCVn8LUPIkR%2BhDDGG3pYfQeBohQMgGsVAVcsg5KzD8CephLDWDMGAlSLDfLwDWF0HozgICuCmH4GYIQFhlAqPkdImQBD/LBYULIgwQUjBmF8%2BofRJieHaHoJFvQ5hwuGPERFcwoX4v6DipYeLPl722BIGRHAl6kFAbwcBxx1FkIoVQmhN89EQFwIQEgpxD4mLMWMtY9EMIjAgBfBI/gWyJH8GSSQd8zCSAIs/PCyQGn/1IIAo%2BLY8JcDwp/RIn89XXy4AvGVeE6XyPAZA6BJ8xkIOQVY1BKjLjkEoI4vBBC2CcGaCwLkZIsxMDMvsnRiQWxcFvgwphJBfR6BWZw9Z0hNlKG2UI3Q1RxFMEkbk6ltL6UKI4Mo9BlwQa%2Bv9YG4NikuBhojW1CABjbF4L5f4Mwpi7VwMsdY1Ahj7Huu7Y2kYZaA29SMNWrgHd3EjS8T4oRISAlBNIHOsJESokLtiU7BJST5GpPSZk7JC78n7KKWvfApTHDlPkVU5ANSF31PkU06MqlWk7DXh0rpx9en9MGUesIoAO18EmdM2Z8zFkLvjWs7hSbZBbMEWvdNezRkPKsEcppZzxXryue6Tgtzab3MORYZ5DLXm%2BneecmodQsguBfISoIL4SWgpmAUCF2Q0XTFSOC%2Bo9GEXkaiVi/oNHMUCBRfMUouKMUEtYwC2YxLgViZMesTYlL5MNLzVazg7JiB%2BoDUGkd7tq3htvsGblzDm0CvbRY4VcEsDxHQ%2BqgBAQw13zJGaskj8qhKvvpaoR1rbC2vMfAxBKC0EYLddg/tdivU7F9ZolgCguR0i5PppU4wo08pYXG2QCbIO8PkCm2DOgAikEzdm6Rv8aVyO80ol111cLRYobF%2BL3IkuNnGPo8LTa9hT0Ff%2Bp1Hq4ihb6/EeLKQUj6kS4kfUyWCAN00%2BQvgdAp2UBnWvJdyTj6rfCZEhwa7u1xIIJu5JJ7MBpIyWIfd3TD2FJfXkkpvGL1CKvTe7pd7GknMfTcZ97ThTvt4J%2BpQ37Cm/vtRM7KQG5kLMYGBzLEGJBQb4XlnZhWDCIfw8c05HyMP1BySBUMSGnkvLiG8tDnzai8Z%2BX8yTeggWidJdC5jNGmOcdk7TxFpPvkNAk7kKTgmOcyZpwx6TqKufib54sBj5LFPcNzRVsB6m6vHAawl5rIJWtcujWyYxbb/MrEs6Kmz1KNWALMGG/w/gF4v3vsA03ZJ9VedlxA3zMChWkEvpIBe0qF6fzfokJIj9ZVcECA0/wMuGWcG6xZsr9C7eh4d9rtYKkMjOEkEAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/varybivore/amid.hpp)
- [unit test](../../../../tests/unit/varybivore/amid.test.hpp)
