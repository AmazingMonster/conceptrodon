<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Amid`

## Description

`Typelivore::Amid` accepts a list of elements and returns a function. When invoked by an index, the function returns the element at the index from the list.

<pre><code>...Element<sub><i>i</i></sub>... -> I -> Element<sub><i>i</i></sub></code></pre>

## Type Signature

```Haskell
Amid :: typename... -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Amid
{
    template<auto>
    alias Page = RESULT;

    template<auto>
    alias UniPage = RESULT;
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
using SupposedResult = int***;

using Result = Amid<int, int*, int**, int***>::Page<3>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will label each element by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding element from the roster.

First, we need to create a label class:

```C++
template<typename Element, size_t I>
struct Label
{ 
    static constexpr auto idyl
    (std::integral_constant<size_t, I>) -> Element;
};
```

We can pull out the element of a given index by asking `decltype` the return type of `idyl` if invoked by `std::integral_constant<size_t, I>`.
Here, we convert an index into a type via `std::integral_constant` for argument-dependent lookup.

Now, we will assemble an overload set and instruct compilers to pull the element out when provided with an index. Here's the entire implementation:

```C++
template<typename...Elements>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Elements, I>...
    {
        // We bring every `idyl` from its base class to the current scope.
        using Label<Elements, I>::idyl...;
    };

    template<size_t I>
    struct Hidden
    {
        // We ask the compiler to find an `idyl` that
        // declares a parameter of type `std::integral_constant<size_t, I>`.
        // If found, the return type of such `idyl` is the element
        // of index I in the list.
        using type = decltype
        (Detail<std::make_index_sequence<sizeof...(Elements)>>::idyl(std::integral_constant<size_t, I>{}));
    };

    template<auto...Agreements>
    using Page = Hidden<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxAEArKQADqgKhE4MHt6%2BASlpGQKh4VEssfH%2BSXaYDplCBEzEBNk%2BfoHVtQL1jQTFkTFxibYNTS257SO9Yf1lg5UAlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnofYJhoAgpvbu5gHR8gKBOhYVFc393cEmBYyQMAMObgI52SjFYz2w9DYglIe3SAC9MAB9Ah7ACSPzu72IXgce2CTFitF%2BJgA7BYDnc9gzkQ1HMg9mgGO9MKpksQ9kwTqg9nh0OcKfTGRB3ugQCAwgDgMQxOj2e9DAQwaiMQQkbj/Nh5nsALRXPZwwGMdX%2BKx3akAEUO1r%2BtwBQJBmDBEKhzDYADo/WaEQQFHjbgSiVjbixhZSab9GXsXcCmKCjp7oWwQ/Gw8TbZgGnQDrGqfarZTxQzE26NXg0Zi/T7dddy0zCTm80w6BqPjKwlhVOilABHLyMNZg7H1n56uOMkB7ZJeaJnVmk8lggMWhQ6q6T5vU2ledJGElkzAUo4bwRbnFXHsi2iTq2FkuOmcVwFJlNuTWYm/T5vZliAASwpYAwb6Fo68bxoeYTAAmkLPIctp7FgOxphB8YQLm%2Bbnt%2B3YgCwTAANYYr2XIDpgw6ju6RyaqgVD1hAl5BvMU7YHeoqSgRcqYAqSoqg0gjVrW2p/tcRa2vMbGlnuxYOmWtzxpWya0W4/JEPWtwKpg5pXpmjKwceyhMMASH%2BChIGfIwYLacQumBgoj4cSAGGyU6ykflWdE1lq4kQUZ8FyAweAmWZLwoWhtAYc22Htp2dEEURpHouR/ZDiODBjj5aIMUxLEKDJ1x6pxtDcdKsqCHxiq0MqAiqsJOVatu06SdJCk2vJ7m/AA9AAVANg1DT1vWDQAKtgQhjYNI13P1Q0LbNToPFlTwvG47JrMkQYhr8gV7EIXjJKkSjoAASpgCheNFEVCoIg0dU6%2B0XVdN3IXskbRkccpInKfW/fd/13QQD0lSAYVqf4U6vvizJ4Mg6JMAoShNOVMoKDCiPBkcL3XWJh3HWkmDnZdeNXDJjocIstCcAkvB%2BNwvCoJwbjWNYyLLKsSFmP4PCkAQmhU4sxEgAkkg%2BhokhcFS/gaAkGhmAAbIrZgAByq/onCSLwLASBoGikAzWikMzHC8AoIAGwLHBaIscCwDAiAgMsBALtqFAQGgQJ0HEEQwpwqiq4rhqK5IezAMgrJSD6Zi8MThAkMKej8IIIhiOwUgyIIigqOoNs6HoADuirJJwPDU7T9OCybnAAPInG7ewMXsgfB6H4eR3s0dmHsEAeN79C8psXDzLw1u26QEBIF7yQ%2B2QHsz3PIDAFIZh8HQALEBbEDRNX0RhI05xl7w%2B/MMQ5y19E2g1NbfNe4GtcMLQR/56QWDRF4wDqbQtAW4zb%2BAkMMAcQr98D2VqAAN0utXLkNQTjrD5rxGmr8zjREVOfDwWBq4EGIHgXW/8oHEGiETXMREjBnCMILRYVADDAAUAANTwJgQutcvTHyzsIUQ4hM4p3kEoNQ1ddBcH0EAlAbNLD6DwNEC2kBFioG2pkP%2BhopTIVMJYawZhjaoEIbgrAMiICLA6I4ZwEBXBjD8MIkI0xSjlD0CdQoWRPCtDsQUYxDA%2Bg2MGMIoxdRJjmL0D4rokwPEDHiN4vxTjcjhJ6CE2YYTDGczWBICuHA6aG2rqbFuQcQ5hwjlHcWPdmL4CIEPHmI8x5UMWAgTATAsDxAMaQEWkh/A%2BgAJz%2BCpJISWZhJCK31gkRWrTNYcG1qQXWvMfSKy4IrVWrTVbTLFlwBI7TFbpNfqbc2lt%2BZUMno7KezsG4nHIJQReg8/ZsE4I0FgECqSGiYGyAwx4uCtJ9FwCWcdimJ2lMI3haduHSF4TnARr9dBr2LkwUujMUlpKNkzOuhysTNyuTcu5DygFdxeW8jQvd%2B6z0HgcHmZhR7bPznbaeqAB5xGOZ7CleLBjItuTsIBzyuAGxoNFOI29d6v1PofdhvLz6X2vg4dh98LSP2ftXd%2Bn9v6/3YVgMhwD1jGzATfPAUC/7G1gcgeB7CkHV1Qeg84mDlVj1wfgvmhDiFKFIUAihoBSV8FoQwphLC2H/1%2BVwjOALZBArzsbUFIjKFqKsBI1B%2Bi5EKPqpwZRHxVHiIsJopmOjhTQNkbYM8aqTFmMiRYoIDB0CxNscI%2Bxbj/EltcZkItXiM32Dcd0UYuaAmZs6AwBtUwSihICREnIebVRNGrfEpYKwkkj2GTCjJnA%2BTEGubc%2B5TKnmYolr3XACdSm82JePIWpBqm1MGA05BozxkvMllSZZVIZaSB6aHYRsKa5m1sFsrdds9lIBdm7alpzfb%2Bw4Fc9uLAFAQNZBA55Po3TvA%2BWupOPzZB/O9Rwv1gi8jgsheXcdVd1nwtdicJuVBp0sH/YB4DoHwNYj7rSueBL/D%2BE3Ts/ZX754nIo4PEAQHjrohA609EpHEYztDuvDlW9KDcuNgKl%2BfMxNCpvqKilD8n4vxVZgD%2BX8xByv/gqu1pq354HAY4DVMDVBwIBHqqqyDjaGsPia7B5r2FWpIYA8hcEdk0NMi65hrDGDsM9enCQPrs78P9QXQIjzjAJskdI%2BAka3F/x6lKMR6jLBJpNimvRkXa1Zr8KYgt5b82FusV2it6Qy1NsKw4wdza62%2BJ6DlwJbbgn5bid26rJXhgxIa8WhJI6M7Qow1oqdf6w4AaA3sTjYHVLvBXZ89d5SSW2yqTUuplAUlHpAGYF51GEjyylvrajVIZlrL6w%2Bi2VtKmNJAJIBIbSEiqyVq0yQrSZYdK4MFzg/hetwofc%2BlJscDsfYqaSxYhD0jOEkEAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/amid.hpp)
- [unit test](../../../../tests/unit/typelivore/amid.test.hpp)
