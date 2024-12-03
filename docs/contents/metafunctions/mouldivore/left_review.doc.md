<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::LeftReview`

<p style='text-align: right;'><a href="../../../index.md#list-examinations">To Index</a></p>

## Description

`Mouldivore::LeftReview` accepts a predicate and returns a function. When invoked, the function returns true if the predicate evaluates to true for every relative-order-preserving pair of its arguments and returns false if otherwise.

<pre><code>   Predicate
-> Arg<sub>0</sub>, Arg<sub>1</sub>, Arg<sub>2</sub>, ..., Arg<sub>i</sub>, Arg<sub>i+1</sub>, ..., Arg<sub>n-1</sub>, Arg<sub>n</sub>
->   Predicate&lt;Arg<sub>0</sub>, Arg<sub>1</sub>&gt; && Predicate&lt;Arg<sub>0</sub>, Arg<sub>2</sub>&gt; && ... && Predicate&lt;Arg<sub>0</sub>, Arg<sub>i</sub>&gt; && Predicate&lt;Arg<sub>0</sub>, Arg<sub>i+1</sub>&gt; && ... && Predicate&lt;Arg<sub>0</sub>, Arg<sub>n-1</sub>&gt; && Predicate&lt;Arg<sub>0</sub>, Arg<sub>n</sub>&gt;
  && Predicate&lt;Arg<sub>1</sub>, Arg<sub>2</sub>&gt; && ... && Predicate&lt;Arg<sub>1</sub>, Arg<sub>i</sub>&gt; && Predicate&lt;Arg<sub>1</sub>, Arg<sub>i+1</sub>&gt; && ... && Predicate&lt;Arg<sub>1</sub>, Arg<sub>n-1</sub>&gt; && Predicate&lt;Arg<sub>1</sub>, Arg<sub>n</sub>&gt;
              &vellip;
  && Predicate&lt;Arg<sub>i</sub>, Arg<sub>i+1</sub>&gt; && ... && Predicate&lt;Arg<sub>i</sub>, Arg<sub>n-1</sub>&gt; && Predicate&lt;Arg<sub>i</sub>, Arg<sub>n</sub>&gt;
              &vellip;
  && Predicate&lt;Arg<sub>n-1</sub>, Arg<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
LeftReview ::   template<typename...> class...
             -> typename...
             -> auto
```

## Structure

```C++
template<template<typename...> class>
struct LeftReview
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };
};
```

## Example

- We will check if every relative-order-preserving pair of `Vay<0>, Vay<1>, Vay<2>, Vay<2>` satisfies `IsNoGreater`.

```C++
template<auto I>
struct Vay
{ static constexpr auto value {I}; };

template<typename L, typename R>
struct IsNoGreater
{
    static constexpr bool value
    { L::value <= R::value };

};

static_assert
(
    LeftReview<IsNoGreater>
    ::Mold<Vay<0>, Vay<1>, Vay<2>, Vay<2>>
    ::value
);
```

- Note that the order matters when the predicate is not commutative.

```C++
// Reverse Vay<0> and Vay<1>
static_assert
(
    ! LeftReview<IsNoGreater>
    ::Mold<Vay<1>, Vay<0>, Vay<2>, Vay<2>>
    ::value
);
```

## Implementation

For every element in the list, we will check if it satisfies the predicate if paired with every element behind it.
We will implement this process in two steps.

First, when given an index, we query the predicate with the pairs consisting of the element at the index and every element behind it.

```C++
template<typename, size_t>
concept Prefix = true;

template<typename>
struct LeftInspect {};

template<size_t...I>
struct LeftInspect<std::index_sequence<I...>> 
{
    template<template<typename...> class Predicate, Prefix<I>..., typename OnDuty, typename...RestElements>
    static consteval auto idyl()
    // We combine the results using a fold expression over `&&`.
    // The pack we are folding is `RestElements...`.
    -> std::bool_constant<(...&&Predicate<OnDuty, RestElements>::value)>;
};
```

Second, we perform the first step with every index and combine the results.

```C++
// Immediately invoked lambda.
[]<size_t...I>(std::index_sequence<I...>)
{
    return
    (...&&(
        decltype
        (
            LeftInspect<std::make_index_sequence<I>>
            ::template idyl<Predicate, Elements...>()
        )::value
    ));
}(std::make_index_sequence<sizeof...(Elements) - 1>{})
```

Here is the entire implementation:

```C++
template<template<typename...> class Predicate>
struct LeftReview
{
    template<typename...Elements>
    struct ProtoMold
    {
        static constexpr bool value
        {
            []<size_t...I>(std::index_sequence<I...>)
            {
                return
                (...&&(
                    decltype
                    (
                        LeftInspect<std::make_index_sequence<I>>
                        ::template idyl<Predicate, Elements...>()
                    )::value
                ));
            }(std::make_index_sequence<sizeof...(Elements) - 1>{})
        }; 
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxCBmpAAOqAqETgwe3r4ByanpAqHhUSyx8Yl2mA4ZQgRMxARZPn5cgZXVArX1BEWRMXEJtnUNTTmtQ929JWUJAJS2qF7EyOwc5gDMYcjeWADUJutuXo60hACeB9gmGgCCG1s7mPuHyAoE6FhUl9d3twD0ACogQDdspiJgaKpdsCAX8fgRMCwkgYEQc3AQzklGKxMKRdmkAF6YAD6BG%2BtzQDBWSQIoPBkOeABFdgRiF5MAcrLcfoDgbtghCCABJBgKLEOaHAuG3BFIlEcw4YrHMNjkm5vNkSgVUYWi8W0kwAdishsZnJ%2B8MRyKYqMOhJJBAAdM6hWqNV4tYKRWKqmS7e8QCAwlhVMSlABHdlUhVuIXOx3fdbYfbc40/XYZllW%2BVo2XW23ozHYtjxy67bZMBQKOmYfCiBF4sEQvCqNGupPxvFK4tPADyDEZxzOXaLKsw8YASpg3th6GxBAo1Zn8XVHMhywI3pgAG5iXZMY6oXZ4dBnWgQWbpzN/P67ADqTzQpTCTwICCe4IUXloBGrXjSRj7rs/C0OguyYKoSSfmkAi7Kg25xPsABsGjmEhaEmChCa3MuN67AAKu%2BuxJEwyAANa7AA7k89RPCB%2BCAXg1aYRoU4znOjC/qWWFXhmAC0ZZvOggbRKgnjEpSbyGH6bgQKWZjoQpTZ1jaMb9oOGJ4mxBCzoinGLkmga7t4mCXkm5qpma6xcr8Ny8kC/KClO254JglGSkC0o3HmOaKtmqm5qOOKlkm5YGFWNYqbaVy3O6no6s5rmURaaY4ZmPkBYqQUls6unzr%2BS6ZnFtJgqgRAALKeOgvH7KlNzLsuUlrhuooIpBxC7KJni7MZ7I1cuRo2Q1w37AArFYo1WW49qkvG7bYBAQmBsGEFhpgkaMCsbYhdgl5pSNmaDf1B2ZuCBBLAwx0nbscnOhhCkQFd12Zlg2zdk9z03R9n2Ztquo%2Bg4aJLSALBMGRJIraGEZRlthzzYVP0nYGGUIsep60Giyl4PWuK7Hl%2Bk7Re33XbMRliH1%2B0/bMZlDc9RqMotAYg2DEMMCGa0bdGQN4ESqBUPGED4wusy7HxuxcN8aamnt9UjfTnIprLGby9ZFqUyjMbdmO8ZCwV5mU/%2BYTALslWgUydJlagpvVYcusKDtFl3Kajs8jCbvu159kgvh06/h5sKu%2B7QcB9y3JmJsVKPM8RwnOcaqWnKmVuAeRC7PDsWsh6tKVQwlsMBcqYWCuNrYy1W7tfuh49eTTyDa6zvWbVVk2Qn%2Baa9lTzBCOyo4rsE5upnEpCgoESoAA4uCqnECltMZk1peSW1UGdWJtDVyZNWDfyZMmdHBzMhOO/sk3LuWafdkwrsABieDEG8eOqKwyJPDCXnz8gxKVkoDQ/I9lN/YlNybYR7j0ngiae%2Bsla7EDNbNEOc84XEOKhJMeJ4FEHzmiCWKCTYCAQWiMwlxUG4PQYgtwBDzKQOXEfDktwaZqwvnyIQVQBBgWwI/OUL8pQ8lvM5OISgcG5xIWiZByZDBgTQQIUhWCYrqlXNjT%2BVY4hkluH/KBYAwCOQSjuJKwDR4T0wFPBG0CQCwMOBIjBhxpFEMEZI4RhCBF4MOOQ7A1jHFkMTDIqhIBeo0JuDTDg8xaCcFGrwPwHAtCkFQJwNw1hrD4kWMsWu4ceCkAIJoAJ8wyIgFGmYR0hozCSAAByFNGhofwOSNBIUKesfQnBJC8BYBIDQGhSBhIiVEjgvAFAgBaWk8JATSBwFgDARAIBFgECSMccglAnxJDoHECIOJOCqEKUhPiSFJC7GAMgdcUhHRmF4LWQgJATx6H4IIEQYh2BSBkIIRQKh1D9NILoLgpBKLECYEkTgPBAnBNCekyJnBezHEmbSPmuwVlrI2VsnZ4tJD7Juh4JE8yOobC4LMXgfStDzAgEgWZKLpkQHxfQeIwApCJBoD%2BPhlBogAuiGEeoZxvm8HpcwYgZxezRG0L6ZlpAnz5X7LQJlTysDRC8MAZOtBaDdO4LwLAoMjDiBFbfX0eAEIyoiRBKoxxVgpLCAiIJTzTjRA%2BeyjwWAAWsjwI02VpAELEFEkoRkiJDDAFOEYdJ8wqAGGAAoAAaklXsypeXnOEKIcQNzQ33LUACl5%2BhXUoFiZYfQeBojdMgPMVANIMgyr4kJfephLDWDMO0%2B1xATzTngPMdojhnAQFcKMFoQQ2ZTH6PEV5KQ0i1syJ4ZoehO0FAYK20oAxXk1pqMMRovaxi2EwPYbtXQGjDpmGOydja9BSSXS%2BaYo7q0JJWBIX5HAQmtIBR0iFqz1mbO2bs%2BFZgbq4GOai5JGLUmevmO%2BJgWB4gXlIFkyQ6xHT%2BHWIaSQGhJAFJQhoUaSFAiGvqaQRp6wuCOiQlwKp/hCnodGpILgo1gNIVPU8jpXSelvv6TikZuKxkgqmRQIlqBkUksWWwTg9QWDbkNHxJgYVXXi38I6FDmr8BEHLcJV5obLkRukFGpQManm6ESO8z5zKj0nrabwDpwKJnHDglQfcxAONcZ4xWQCrRBOOg0IixjcySX7HDmYV9WKBnUeJXEQlbn4jsc43xUzZL/BcBaZS8B3SIC0qeayxlvLIvss5dyhwvL%2BWcUFcKiJorxWSulby%2BVrqlVpZVdUdVAKtXIB1by/Vc6AXGtNWcc1qwIlWptSk%2B1jrMDOoVW6o2nq%2BA%2Bv9YG4NtrJPhuuTJ2Q0bHkRMU/Gj1harDJuNem39Wbu25vzesRks3i2lriGJytGbZ3zoyC4Nm67XkhG3W2/t%2BRu2nbyF2jIy7R0HdVZ0Nd06m3jte5MC7I720TBGO9jdk7Hvtr3UsA96LanHv%2BcRzgBmjPcd42ZgTQmH0iZIPZ5DTn32kE/d%2BygR6ENIYE%2BBw0%2BHDSGnWBByQGzXkacBZ02wZHnOUfgNR8ZoKPM2ZRSx1Y7HoUsAUNudc25zPyjeIc9HYmzmyCkyN258g5MTZ0CAGpymvmyrUzD9pQLaNgv0/zzZgvhc9TF6pe%2BEAkW2cQhsdY2OKODLxdzklXOmMDGF0kJIxJRf%2BGJOLggn9DMbL4HQELNK6UMvZdFyPHKuU8ttUlwQKWAXpYlWILLtqcuKvq3KgrjgitPJK2V21FXDUROq4yurlry1Nd4C11IbWXWKq6w771TBfUBrckGxgIbZfDYkKNu5SvY2q%2Bm8YJNNgFtVsidmzcnA/hLU25YEtmmy0VsW9WudL2/D1pO4Ds7Lafsrru4O27A7u0g43VvjoDBF1TuyB96/C7gdH6e5u%2B/fbV3feKJdyHCh93XJa5EY64cDw4C5C4i5m4IgW6PqiaY7oqYo4544DC/rwYNIJACbrDrCjSlK4bNJYGGhVLAGaacCka9I47/qGj7Jk5cBSD%2BCk7AZcCGhQ7rDa4kGM4s5HoHLEEM6IEUbzD2owR%2BCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/mouldivore/left_review.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/left_review.test.hpp)
