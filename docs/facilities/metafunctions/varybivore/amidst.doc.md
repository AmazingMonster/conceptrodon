<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Amidst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-amidst">To Index</a></p>

## Description

`Varybivore::Amidst` accepts a list of variables and returns a function. When invoked by an index, the function returns the variable at the index from the list.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> V<sub>I</sub></code></pre>

## Type Signature

```Haskell
Amidst
 :: auto...
 -> template<auto...>
```

## Structure

```C++
template<auto...>
struct Amidst
{
    template<auto>
    alias Page
    {
        static constexpr auto value {RESULT};
    };
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
/**** Metafunction ****/
template<auto...Args>
using At = Amidst<0, 1, 2, 3>::Page<Args...>;

/**** Test ****/
static_assert(At<3>::value == 3);
```

## Implementation

We want to count variables one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose. We will encode value information into types by `Vay` to avoid defining the body of helper functions.

```C++
template<auto Variable>
struct Vay
{
    static constexpr auto value {Variable};
};
```

There are two ways to enumerate the arguments.

- First, we can use `void*` to declare unwanted parameters in the function signature, eventually reaching the target variable.

We will need the desired number of `void*`s in the front of the function's parameter list to enumerate the unwanted arguments.

`PointToVoid` will turn an index into a `void*`.

```C++
template<auto>
using PointToVoid = void*;
```

With its help, we expand a pack of indices to produce `void*`s.
`Midst` will help us extract the pack from a `std::index_sequence`.

```C++
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    static constexpr auto idyl(PointToVoid<I>..., auto* target, auto*...)
    { return target; }
};
```

Finally, we will make a template that generates the `std::index_sequence` and translates the result.

```C++
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
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMzSrgAyeAyYAHI%2BAEaYxCAAbADspAAOqAqETgwe3r4B0umZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZn8YWQ3iwNxM/jcXkctEIAE8YdhgeYwQwIV4oTC3MhxugsFRUeifocbgA1JhIz4HQEETAsVIGRl4pjw1BUlp4JjReiky7jYheBzclGXExJKyXG5ym6zRzIG5oBjjTCqVLEG4cog3ABuYi8mGh0upxF5/MwUruMJlQKStv89uBv3%2B7v2gLdNwAksz6GxBEwGnTPa6PRHTmSrhTlKgwgQACqoSnx9ChqOXRn%2B4PW2G61CCi5eTJGG5xhPJ1N4dMwu4GtO7O3R70AWRr4wzDKZLNzeIISKezDYReFooIN3b6E7UqsjubkqzPdZebcmQAXpgAPoEAB0%2B59o4IIrFU/GeMJIBAYSwqi3SgAjsasauffvd6T/GjJdLgfKFc0SoqgI6qatqBY3DWSK0BAFaCFWaZ4oeX7vqQOqcrsNwTMAmAEGhBa7O%2BSx/vKs43MQuHrAwWEtDhBB2qato/k6LrkrcFwsB2E5fMC2a9my%2Bacu%2B5qWvQChHieE4cVx6K/rK8p8SuF54JuO6%2BkW/5jmKyjEKgRDKEwOEkXKs7Gf%2BAHBngyqqqBWroXqhreCaZn/qZ8nmeZl4gBRLCoPq27pAmcQ7i5HnQrCoVhfKWAQgOTyRVFNwQAliXyme9Gwl5LBMAA1tuN4avemBPi8r6ft%2BFypalV5QTBipWVuojnrC1Ioi1PJ8mJqJNl%2BEAMF4tC0Kkx5LERKVhcR7mJaiV6OcaCU2gulWkfOzrRv%2Bil9oJRDvhcwAUUyjAEOJX5mSWYTAOWhnOf49Y6XpqAGUZsJ7QdgbHe%2Bn4uqtrExpG9Lhrc2CqKwLImjxbH/ZmQKQ5hra4UwVBeFiIYQxcm0CW4Ba7cQwAnRV51luj4X1tJ04ZW4GhoVwaFmGh/gzSAT2rhcuMKJ9p1rYuf37DcibvNxANCoBDVMAoSitBA6N4gzX6zUaN1OvW/jEc6HArLQnAAKy8H4HBaKQqCcG41jWAqawbM5oI8KQBCaOrKw5SAWuSLuGgABxmGYACc3tcFrHvu1wSRJNImscJIvAsBIGhU3rBtGxwvAKCAVN2/r6ukHAsAwIgIBrAQqTwuQlBoMydBxBErBbKo7sJAAtAkkg3MAyDKlIu5mLwmD4EQFroHo/CCCIYjsFIMiCIoKjqBnpC6DTADuxBMKknA8Br2u6/bhucAA8vCRcTqgVA3LXDdNy3bc3B3ZhJR45f0NqGJcEsvDp1oKwQEgZepBXZAUBAH%2Bf8QDACkHTGgtBGTEBThAaI29ohhBaEiNevAEHMGIEiXe0RtCYAcCg0gZd3q7wYLQZBs8sDRC8MALGg0U7cF4FgbKRhxDkLwBRBweB/J0INhqXB8Itg2yCuHA2iJojLwwR4LA29jx4GjvQ0g/liDRAyJgB4TDgCIiMPbFYVADB40pG8Beu8hz4KHsIUQ4hx5mKnmobe899CGGMKbSw%2Bg8DRBTpAFYqBhrZDofXQkdZTCWGsGYBOij%2B7vHgCsOwuCGguAYO4TwHQ9AhDCEMSoIwaZFCyAIKYfgskZByQweYwx4g0xiRwgQfRJhJPyOUuosTegTAGGkhYmTbDNLyXoWYrQSkZLKdEi2mwJAbw4DrUg8deCJ1PnXRuzdW7t1drfCAuBCAkGhNbV%2BtttErAQJgJgWB4gQEdiASQ/hdze38KHDQkgzCSASLHLWCRvb6E4JHUg0d/BcF3AkLgCR3beyDgkF2/tLkJAmdvROydU7bIzp/XOX984H2LgAoBj8q5sE4C0Fg%2Bokj1yYCqAwZYuDe13N8nhvcSA1kHrIEeljpDWKULY2eug6ZLxXig0Z4zJk7w4PvQu8IbjHxmefZuEJHHX1JeSu%2BqAH5xA2f4MwWz36Z0RWiuIJdAGyt/o/FARLQF%2ByphAqBMC4GzzQUg/BFqMFYJwXg%2BRhCjrENIdvChVCaG0DoTbRhjiWEG3wOwxwXDt68OQPw/BQjt6iPEUiSRWwDYyLkTbRRyilBqN9RdbRfA9EKAMZgIxJj5FmLpWPBlsgbEzwNqyhxWiglWBcaIjxxzDY%2BJApwfxBB0CBOcRYUJUzwk1kiZ47ojTnAQFcF0mmqTyilL0Nkhok60iFIaH0xY9SehVM6bU/JI7KmNGaau9pPS2jbu6Qe1ps6X6rHWMMq94duWQs4CKuZhKJUkrJW7JKqy%2B4Kpfm/HZpA9kHJGM28O7zPmkpuUkLW3sQ6BDuU3GmPKoW2BhSq%2BF8BEUF0Ppq9VxAMVbGxRfFgCh9TKn1O%2Blc4xu6Uv7jS4eFjS0T3kEyytOgAikHZavehXKt6z0Tvyw%2BQqT6qGI6R8jlHcydggPfHV8qMQq3/XCrO39tV/1w2p3VZHUipC3BR72W4qMEC3KJhldATWUDNQba1ZCbY2dtbE/BjrBDOrIf6zAlDqFiE9fgn1zD40MLYY04Ns9Q3hvkZG2e0akFxukRaJNvAU0qPTcwzNyndGGVzYY4xjBTG0sYxIMtk9WN2I4/qlAPbXHuKiS2hodDtiXjrSEsJcQIlNuiQ0vd8TEl5B3dO9Ja6l3FGyIu%2Bd2RD1lN3Q0apJ7evdM69N89M7%2Blnv6Iu49E2RnXstlt%2B9fGE5PtMzcEjZGDSScZNJ796zn7KoA0Bw5lBRngZAD7Xc/h/BawDpILgsd3tJH%2BRC/jnBoVpwA07SQWsLnBySLHd2kg/ZcE9mYcF4d/D7amcD2FH9Rld0BwdpOWOHYKLiJkZwkggA%3D%3D)

- Second, we can use concepts from C++20 to constrain the type of unwanted parameters in the function signature, eventually reaching the target variable.

`Prefix` will turn an index into a constraint that evaluates to `true` for every type.

```C++
template<typename, auto>
concept Prefix = true;
```

`Midst` will help us extract the pack from a `std::index_sequence`.

```C++
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    template<typename Target>
    static constexpr auto idyl
    (
        Prefix<I> auto...,
        Target,
        ...
    )
    -> Target;
};
```

Now, we make a template that generates the `std::index_sequence` and translates the result.

```C++
template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value 
        {
            decltype
            (
                Midst<std::make_index_sequence<I>>
                ::idyl(Vay<Variables>{}...)
            )
            ::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMzSrgAyeAyYAHI%2BAEaYxCAA7FykAA6oCoRODB7evgHSaRmOAqHhUSyx8Um2mPbFDEIETMQEOT5%2BgTV1WY3NBKWRMXGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHRztbJhoAgrv7ANQAIpgprozIeJgK1wenF1fHv4df5zOgLM/jCyG8WGuJn8bi8jlohAAntDsEDzKCGOCvJDoW5kGN0FgqCi0d8DtcAGpMREffYAgiYFgpAwM3FMOGoSnNPBMaL0EkXMbELwOLnIi4mBJWC7XWXXGaOZDXNAMMaYVQpYjXdlEa4ANzEXkwUKlVOIPL5mElt2h0sBCRt/jtQJ%2BO2uymImBoqlpe3pjOZTFZMIIiMezDYpG1HIF5xVGxSBHdnu9UP8t2uBGFVqdpMufwL/xd5IAkkz6GxBEGsr6TsXCw2AfW9tcALJ4dBjWv%2B8tBnNuUPh1g51GCrMipPtztJyVWB22vMM3vBtwZABemAA%2BgQAHR7kuxoUTtsdsa4gkgEBhLCqTdKACORsx/ZLe53JP8o/tdrlmYDLP7QdGGHa4ABVmmATACFjX8FTwJUVTVDUtR1TkO0RWggV/CAsN/OUPS9PBVFxA9P2jIg31IXC8LAiCoKomUaOuN9qOuRZWIAWhRWjiEg6DcwlecBMBMkbnOFhTyTT4gSXQMV1Qt8zQtegFEPcdRXEyS0SlVjZIA888A3bdrlIr9YPUpMPVQIhlCYSDWNnVjzOrBCBCQzVyM5A1vGNJy5UcximLlLBwSAvyaJwwKgrwqczxhC8QBYJgAGst2vdU70wR9nhfD8zOimjL3Q2gICpZEYSU3kVJJHSHTfdioqChrzgK2VL28o1wpNR0f38oTnSivS%2BzZDk33OYBPUZRgCFUz9WK8DIjHdOzfPTZNrNQWz7JhcbJsrGaWLm4TrQXCVRIbOlmzdbBVFYZljWk86LrrM78xuVsoKYKgvExepuxk/9hphBS93OXjZq/BawmAa5zhnNbNOnXENCjZJrjMKN/BRS8tv7MHgAUQ7UWOp6wLeKTLrHFzNyYBQlBaCA4dxLHP3aw1VsdDN/HYp0OGWWhOAAVl4PwOC0UhUE4NxrGseVVnWXyQR4UgCE0PnlmSkBBckHcNAADjMMwAE4ja4QX9b1rgEgSaQBY4SReBYCQNBR0XxcljheAUEAUdVsW%2BdIOBYBgRAQFWAgUjhchKDQJk6DiCJh04VQ9YANg41PJGuYBkCVKQdzMXhMHwIhzXQPR%2BEEEQxHYKQZEERQVHUf3SF0ZIAHdiCYFJOB4fmhZFtWJc4AB5OFI6TVAqGuFP08z7Pc%2BufOzGuCAPDj%2BgtXRLhFl4P2tGWCAkFjlJ47ICgIBPs%2BQGAKQMZoWgGWIb2IGiIfojCZpEV73gP%2BYYhEQj2iNoTADgf6kFjvtEeDBaDfxblgaIXhgBuDELQb23BeBYCSkYcQ8C8CegcHgPUbwh7qlAXCTYyswgMjtuLBE0Qu4AI8FgIeWY8BOwwaQYhxBojpEwPcbBwAERGDVssKgBgCYUleO3Ee4ZwGV2EKIcQdcFGNzUEPNu%2BhDDGBlpYfQeBoje0gMsVAiYsjoI4gSaEtxTCWGsGYd23Cy4kOMV0UB9QXAMHcJ4doegQhhEGBUYYyRCiZAEJMPwIT0hhIYHMIY8RRi1HcT0cYrQfF5ESd0AQvQWhxKCQk2wqSIl6BmLkgJ8xgnLAUPLDYEh%2B4cGFqQN2vAPYzzThnLOOc846xXhAXAhASBQiVrvFWojlgIEwEwLA8QIAaxAJIfwO4jb%2BBthoSQZhJCpxdoLVORt9CcAdqQJ2/guA7lTlwVOesjaW1TtrM2yzU5NKHh7L2PtRn%2B0PiHI%2BYdx5RwvlfTeic2CcGaCwPUCQOJMGVAYJaXAjY7lOeLYuAyy4V1kNXZR0hVFKHUS3XQGNO7dx/vUxpzTh4cDHhHOE1wp5tLnlncE2il7wsRavdep9N5DP8GYEZ%2B8A7fIBXEaOl9UAb2GIyowcKuAowfk/F%2Bb8W5/y/uApVACgEgLAZwyB01oGwKHggpBKDaBoPAVg7RuDxb4AIY4Yh6CkWqHIQycB1DahD3oYwxEzDNjizYRw5W3DeFKAEea6Goi%2BASIUFIzAMi5GcIURi2uWLZBqObuLfFWiRG2KsHo%2BhRjZkSzMW5TgliCDoGsVm%2Bxji4jOLzVUpJhDnAQFcMU5I/iyjxL0KE%2BoLbUjRPqHkhYmTknZKKekyJbiG0NFSQO4JhS%2Bg9tKf0cpHad4rDWLU1ddtSXPM4HSjp0KmVwoRbrVe/TS5cp3nvMZpAJlTOGPmu2hzjnwrWQkQWRtraBA2ZnZIZKXm2DeXyz58BvnhwnsKwVxAgWbFBfPFgCg9RKj1EegCYwi4lxIB2NFVclGJvrvIHFqadABFIISnuGCSWDxbh7SlE8aXT1UHBhDSGUN9i7GvUVHK4hcu5lej5gdj6cbPhBoTm8QCIZSCkTcyGjablQwQTcjGsV0DlZQBV4tVVwOVpp9V7jwHasELquBlrMCIOQag9ByszU4O9Zg/ByTbWkIdcgChzrBCupbu6r%2BXrWHmj9bwANfDg04NDfx8RdlI3SNkYweR6LcMSCTQ3QjGiSMwp0XYnNBja0FvqOgrYF4K2WAcS0pxHYXH5rsMOvwTavE9rbYEwdvaihZB7V2rIM6CmVcnTktJuRx1dfqD1jrJTR19ZG7MZd%2BS6lroVtNrdVH3a7qU9ceDiH9SsYZOxs9gzt68uvbe6ZlB6lPpAMbHc/h/CC3NpIaVGgLsJEuU86jnBXm%2B2vZrSQgsllWwSC7PWkhTZcANmYR5dt/ALZaS995B96mFye4tz20P1ZcLiBkZwkggA%3D%3D)

The function is implemented using concept expansion in this library.

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/amidst/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/amidst.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/amidst.test.hpp)
