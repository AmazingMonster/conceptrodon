<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Inject`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-inject">To Index</a></p>

## Description

`Varybivore::Inject` accepts a list of variables.
Its first layer accepts an index, which indicates a location in the list.
Its second layer accepts a list of new variables and returns a function.
When invoked by an operation, the function injects new variables into the location and instantiates the operation with the result.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> Args...
-> Oper
-> Oper&lt;V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I-1</sub>, Args..., V<sub>I</sub>, ..., V<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
Inject
 :: auto...
 -> auto...
 -> auto...
 -> template<template<auto...> class...>
```

## Structure

```C++
template<auto...>
alias Inject
{
    template<auto>
    alias Page
    {
        template<auto...>
        alias Page
        {
            template<template<auto...> class>
            alias Rail = RESULT;
        };
        
    };
}；
```

## Examples

We will inject `10, 11` into index one of `0, 1, 2`. Then, we will instantiate `Operation` with the resulting list.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 10, 11, 1, 2>;

using Result = Inject<0, 1, 2>
::Page<1>
::Page<10, 11>
::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The implementation is similar to `Varybivore::Amidst`.
We want to count variables one by one up to the desired number.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
Note that using `void*` like when we implement `Varybivore::Amidst` is impossible since `void*` erases the type characteristics of the arguments, which, however, are the things we want to keep.
Therefore, we will only implement `Inject` using concept expansion.

We will transform variables into types so that we can avoid defining the body of the helper function `idyl`.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Enrich {};

template<size_t...I>
struct Enrich<std::index_sequence<I...>>
{
    template<auto...NewVariables>
    struct ProtoPage
    { 
        template
        <
            template<auto...> class Operation,
            // We use `Prefix<I>...` to enumerate `FrontTargets`.
            Prefix<I>...FrontTargets,
            typename...BackTargets
        >
        static consteval auto idyl() ->
        // `NewVariables...` are injected in the return type.
        // Note that `Operation` is invoked by values
        // extracted from the template parameters.
        // This is because we will pack every item
        // of `Variables...` into `Vay`.
        Operation<FrontTargets::value..., NewVariables..., BackTargets::value...>;
    };

    template<auto...NewVariables>
    using Page = ProtoPage<NewVariables...>;
};
```

`Prefix<I>...FrontTargets` tells compilers that this function template is only allowed when `FrontTargets` satisfies `Prefix<FrontTargets, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

Finally, we will make an interface to accept arguments and generate the `std::index_sequence`:

```C++
template<auto...Variables>
struct Inject
{
    template<size_t Index>
    struct ProtoPage
    {   
        struct Slash
        {
            template<auto...NewVariables>
            struct ProtoPage
            {
                // Note that we use a parameter pack in the template head
                // even though the function only allows one operation.
                template<template<auto...> class...Agreements>
                using Rail = decltype
                (
                    Enrich<std::make_index_sequence<Index>>
                    ::template ProtoPage<NewVariables...>
                    ::template idyl<Agreements..., Vay<Variables>...>()
                );
            };
        };

        template<auto...NewVariables>
        using Page = Slash::template ProtoPage<NewVariables...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAbAAcpAAOqAqETgwe3r566ZmOAqHhUSyx8f4AnLaY9sUMQgRMxAS5Pn6BdpgO2c2tBKWRMXGJKQotbR35XLZTQ2EjFWM1AJS2qF7EyOwc5v5hyN5YANQm/m5ejrSEAJ4X2CYaAIIHRyeY55fIk%2BhYVEezzeZkODGOXjOFzcBDuqUwAH0CMQmIQFEDXsCCJgWKkDNjoUxrqhTgA1Vp4JjRegYl6TYheBynACyAlQRAYD0xAHYLKdJkxHMhTmgGJNMKpUsRTkSiKcAG5iLxfEy88nESnUzCqgAiFz5uv1wKxOLxgu1l1h8OYbFIMuJtNFu1SBFOymImBoqm%2BOtOyOVRsxr2xuPxFphcMYrAtT1e9MZruwDA1yAQ515hv8ViDLxDZoJl0yAC9EQQAHQVgCStPjTKTKYQ0L%2BIBAYSwqgRSgAjsrweHKxWy0D/LG3hnXqdJ37TWHCcTBxFMAB3dWa%2BjokfAqf8/1M93s1DKJjAbUTqeqg1n7eTvOzq/X6Fb6/P2/mudEQePEUGBQKU4AeXhFFGlIJ9n23AB6CDTgAdS%2BLwlHOBINHdT08FUaFqxHT9kL9ElGB8OJzSQjQADFiFkAAVVoTwIdFkKHe9wLdD0vUwx5B3IqiaMwOjQKY8CrSjNhBwsJhkAAa2o4haPRATJ1pZiBSFEUBHFRVaHtOU8HQO5aAgNZTgAWkU8CoJIxcVwpKl1xwjQZQ9U4wm0XpsXQJyGD9BAvg9Ahtk8oTGJeZjzIidkvgIBBBRIwCiMaExcLwP8wnlVAJMwdzojuBUlUwOTgrM6CJWRcS3NOKgKJYLyIpnYjUlaaNsWIBQguY2LgOyaEuMEaTZJbDTlUHO1LNXGy8qG04xMk3reIUfrcs/TcszA9M9WWnNt1fAs3FlVAF2XUatQ3UdtwQsJgDdY8VX8X19yII8T2hEbrKOxannWsc1uzN5g1q7bdsHQ71xrXdXUrBgXIcY1xwKm8/vDYtS1OcH21Myda1dO7DyulaL3PeSdwZJkhB/RsCYvFbmK28MAYrZ6NTG47KfAjGWIPB7T1h5j02%2B7nCtOMLsS86Kl3gxCmFOeqUTYJrJfEiSPOq6dQ2I7ymHQZm%2BfMzB5UYLytmANNIq%2BKgvHBRpTgEWhsrEWhUCXP8BC%2BVAgMFbJWr569qehb3LlpocR2/Jhf0HF5gA9HFGDotHPcnM6jFOAAlVFNIuX0sGOITNe5iBs9j%2Bs8FTJsCHQFsWCYdKETbCVO0wHtGF2TCGFRpaTtj8CW2ptn7pxy56bXcaKxj9up07%2BGnN02hoTDiO2EEFqKztVkGAPTloSBvKOKHkcDLz8C1kDLnmMzXnwJP40Cd9nb5zpg6XuBzcCfji6OZ9U4SeDpAQC7rGOaeu%2BGavW3u9U%2BCluRfQvlzK%2B/sZ6YEjvPGOz9Lonjfr/XubhYHwLom9Q%2B58cwQQAFREOISQiCwJCFEMotgIQlFiFkNeBQkhpDIHvHBJ8b4bgnSYBdEzHM0Cb4B1HKzdqbsBC4NeEgoQXhUiFAyonPKXhaCujTgBV28VLgaDtFwTRpwuBzF0XaMww5vrAiQfIhQijlE3WRhDVy0IdH6KMY/F4LY/6XC4LSVx6DtFaI8c4lsyc6DQhEeokBkDlKFwRMHJQbQIDNhAAoaMUSNxuHMZYu0UiZEZDkQopRjwD5Zg4BsWgnAACsvA/AcC0KQVAnA3DWGsPyLYOwVSgh4KQAgmgikbAkiAUpSQywJH8JIMw3JJCSH6f4DQpTqgpBKRwSQvAWASA0Joyp1TakcF4HNTRnSqlFNIHAWAMBEAgC2AQVI1xyCUDQLiOgcQIjRk4KoJICQjIJEkKcYAyBhRSDLGYXgGVCAkB0nofgggRBiHYFIGQghFAqHUPs0gug5hLhRKkTgPBillIqV0mpnB/zXEua6VAVBTgvLeR8r5PzdGSH%2BacCAHg7n0GlAcLgaxeB7K0BsCASBbmpHuWQCgEB%2BWCpAMAKQZg%2BB0CanNCA0Q8XRDCK0O4mLeBKuYMQO4/5oiQz2e025c8CD/gYNbPFWBoheGADtWgtA5rcF4FgcuRhxBIvwB6Pout7XVIlL0a4ex2lhGxPM6ptxogoi1R4LAeLkR4GWQ60gutiDRGyTqHEhhgC3CMF0jYVADDAAUKSPAy5YqVPaeC4QohxAworfCtQeKUX6AzSgBplh9B4GiHNSAGwXaNHtUZP4adTCWGsGYDZSaNRYC7QZOoDRsguGbjMPwcwQhLHKJUAoGQsgCCXZuoo2RhjrrGHMHofQBADGmJ4ToehT2NAvYsMoox4gnoWLul9gxD1PokBsBQzTdjfv0Di0g6zeCbPJa895nzvm/LpWYBluBgWsraRyjpOaNhqywPEGdvTJD%2BDLNUfwYyNAjMkMhaZCRajzMWaQZZ/guCDK4MkWZjHSmSC4DM/wCRgN4s2dskAuyc2HJObys5RKrnCtFSyx5bBOCtBYPKbkRkJbHAzbo6oZZ6M%2BvwEQSdYLZCQurdIWtSh61It0FKtFTAMUOuxRwcp3GkWbMJRc64lsyVyYU0poOCcuDqc0wyplAqWXnFBGYFDXKDkick3Ea5IrUDMrGB5xTKmjC%2BZ8TQJRcQ5UKqRRqlVarSB5a1TqvVBXDVRxNWat1mBLXWttva9pTqM2uuqe61yeAvV4t9cgf1BWg31DxWGiNdwo17GqbG%2BN7Sk0pqUGm51mbzqCbzceQtxalyloKxWgz0KjOyDrYi6p5mm3ZuHVYNtYbp09pdNkftg6bqndHeOuIk68rwB/fUdrzgICuDfUEZun6VjPrSFuxov3CjboYADjdJ6PtnqaK%2Bq9sxZ2ffhx%2BtdX732XryMu%2BYaPH2A4A7%2B7Y/72WAbs7ixznAHLycU8pgwPm/NlnshABDOmQt0fC2h0gGGxgzqo0sgI6niPchmdybkwyzCkbYw5jZnA%2BMCf2Ty4TSBznEti9F4g0m9hyapSwBQ8phTyl82WMMkxAXaZBaXOYW2q07dhfIEzB2dABFIJZ6zWKyf2ZA/ijgzniVuep7r/Xhvjem9dIy%2BLQW4js/8JzxXhy%2BWR8FerpPLKQAG5kQiI31QERh6icQFgHzpWZeapQHL1SiuqoTZXkrrkyvxaNZVqvrWatWptXagrTWXVjcdXgD1jhOtIu671hN/WQ28CGyq0bMaNSTd4NN1N6aXWLfj8tgtRaS3Wk2/p23Ehdtwsdw2l39PjCtpsBdt7NTrtqU4BBZsD3LBjtAxOnSr3u3I7hwu9wiOcervx9D4HfdHdH/PdCHKHY9D/O9BHbHG9WHKAvHZYAAgULHa9THB9RA49H9P9aFWzL3HjKnHXT5PXA3BUUPc0SYeDC3JDDnTlLnHnLDWzajZZMwdTfwfwUpUpYjbRDQNg7kZIGXUDOXWwfjVDRXHpEANjMsTjUpbkMwDgtjCjSQDQKVeZfwCnWXLZUQ7lWzAFAQn3WgsQxNLLedSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/inject.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/inject.test.hpp)
