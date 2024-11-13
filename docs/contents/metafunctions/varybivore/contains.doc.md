<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Contains`

## Description

`Varybivore::Contains` accepts a list of variables and returns a predicate.
When invoked by an argument, the predicate returns true if the argument is in the previously provided list and returns false if otherwise.

<pre><code>   Variables...
-> Argument
-> Argument &in; Variables... ?
   true : false</code></pre>

## Type Signature

```Haskell
Contains ::   auto...
           -> auto...
           -> auto
```

## Structure

```C++
template<auto...>
struct Contains
{
    template<auto>
    alias Page = RESULT;

    template<auto>
    static constexpr bool Page_v = RESULT;
};
```

## Examples

We will check whether `1` or `-1`  is inside `0, 1, 2, 2`.

```C++
template<auto...Args>
using Metafunction = Contains<0, 1, 2, 2>
::Page<Args...>;

static_assert(Metafunction<1>::value);
static_assert(! Metafunction<-1>::value);
```

## Implementation

`Varybivore::Contains` uses `Varybivore::IsSame` to compare variables and a fold expression to combine results.

Here's the entire implementation:

```C++
template<auto...Variables>
struct Contains
{
    template<auto Inspecting>
    struct ProtoPage
    {   
        static constexpr bool value 
        {(...||(IsSame<Variables, Inspecting>::value))};
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISVykrgAyeAyYAHI%2BAEaYxCAAnKQADqgKhE4MHt6%2B/oGp6Y4CoeFRLLHxSXaYDplCBEzEBNk%2BfgG2mPZFDPWNBCWRMXGJtg1NLbntCmP9YYPlwwkAlLaoXsTI7BzmAMxhyN5YANQmO24EAJ7JmAD6BMRMhAqn2CYaAIJv7wSYLMkGP1ObiYXiIpCOIKILy%2B02IXgcRwAkgohKxMF8TAB2CxHaZMRzII5oBjTTCqZLEI7RVCeI4ANzEXkwJ2xVDESixABFTjiuTyMR8fn8AeizpDUEcAGqNPBMaL0aEfWHwghIlFooHS4iy%2BWYcFanUKnavD5YnF4glEgSk8mU6m0hneZlm%2B5Mvk7XmY7kegXfX7/fGi4Gg1AAOnDBrl9GexphroRHkEjxJGOxXyOGaOQoDgLFIaRJOutSMivemdx8dVymIqCIyiYwHRH3LZsz6fLmYteEJxJtFKpNNo9MZzubHYzZog4dDWLcs4gyNRbE1MqjmAU4MRhZqjhLxpAIEdTKWS3dVjHE69/NNF6z/pFQPF0/ewGImF%2BjAIMZNZczXnSRhHPWjYnDsnJATWdYNkGL5vh%2BggKNO0I%2BqaV4oZ8HwAPQAFS4Xh%2BGYV8OG4QAKtgQgkXhhFYfhtHYdRGGfGYewMAcXjHECxKbMkX6ll82YPnmRDPsQwDfl8/5hMARwALKYA0VBeKx3SgeBiYNGEMZuBo4KBEcZjgmYpYHsBMGiYh4bIeejFdsgNxMAoShNBAckKUptQCECXAvAeR6YKe6G2fZjlxAQEBgGAsnyUwinKZkQIALTefuh4jgFFgcCstCcAArLwfgcFopCoJwc6WNYuJrBszrMTwpAEJomUrAA1iAOWSKGGgBJiOwaDlGhmAAbINZgAByjfonCSLwLASBoOkFUVJUcLwCggDpDWFZlpBwLAMCICAawEMkoLkJQaB/HQcQRGinCqKNg0JYNkhHMAyCElIoZmLwmD4EQ2roHo/CCCIYjsFIMiCIoKjqFtpC6IEADuDzJJwPBZbl%2BWNcVnAAPKgidqqoFQRz3Y9z2ve9RyfWYRwQB4l30JSuxcEsvCbVoKwQEgF3JFdZAUBAvP8yAwBSAZNC0D8xBrRA0TY9EYSNBcaO8IrzDEBcuPRNoO6q6QF1sIIuMMLQKtw1g0ReMAwK0LQa3cLwWAsIYwDiBbeBvrUdLrtjZI1KCWx1WEPzZXDtB4NEDyax4WDY/ceCzY7pA%2B8Q1JKJyvyuxHRiNSsVAGGJkp4JgiO49cBV1cDwiiOIEPV9DajYwj%2Biuyg1jWPokdrZAKyoDxmQOwl0zoKcnKmOVlhmEtqcA77vcdF0mQuAw7ieK0eghHMZQVHoBQZAIEx%2BPkaQHwwAw78MgTVB5PQzEfeg390vRNBfQzxNf9/r7kn99G/CwfxWAoKqmwJAYw4HlUgi1eDLVJg9J6L03ofQ6rTCAuBCAkBOLVNm9U84rAQJgJgWB4gQBav4HYoYEg7ExJILqZhJCDXmjlQaSQw7TVILNHYXBQyDS4INUaCRRp8PalwHKVDBpQOxstVa61cFbS5vtbmh0CanUFsLJmN02CcEaCwOkmIEpMCJAYQCXAEihm4UVX6GCAZA1kKDOu0gG5KCbnDXQBlkZMFRo7cBkDoE4w4PjY6oIjjEwhMQXR%2BjDEHFdtTMxFi6YMz5kzLBOwzA4I5ttJR6i4hnSFqgRmwwdF6IStEowpiuA6UltLWW8s4bq2Vvrepmtta6wcPrQ2n4TZm2xpba2tt7b62dtnLYRV8Be0cD7B2ljVABx%2BPrEOnRsYRyjsrWOIz2baiTnVVO6dMCZxdkYHOoB5F8ELgoYupdy6MH1tXex4NHGyEbrDIqbjW65wnlYSwXdog91IcVAe1pODDwIKPMCHzrDTxgbPPAWBflAM6DuZeEBXAP0CFvUo7896n26KilI2LMj/13tfBFt8X7NG/sfReiKBBksJVfUYfRcV4lftvTFrNVjrFAeysOvipGcDCREgxRiYmmPMZ1Om6D/opNZuzPBpACFEOGH8thM0QA7DMV1TEYjMQ9UkPQ56gQ/HSNsLIjJCj4BKKOoTXJ2TiCaK2DoimLAFB0kJHSUVIppg/T%2BiQGFtiQa13uZDeQzjnk6DVaQDxXj0aTQgVjOGy1AmExCSTR1L1nWuvpB6wM0wEn5KSXEFJOx0l5x2jzfN/MbUVqZoeZAyRkg3HdQkG4nqCD2XCc9PgdBqmUFqUVJp5s6oDpaXrZOHTjam3NqMzAVsbZiAGcnIZhz1mkDGYiyZfsZnIEDvMwQizw6R2jhcNZ8dNn6x2WkPZWdDlSVLQXBs5yS5lwrjcuxgaJAPKhqG5uEbjHGA7l85ZcL/ndAdphEe7dJ4WEhcVaFsL4DwqXs4ZFq9cXovmESvFhRMi4v3t0OlH8qWkq/jkSlT86gzAI4/EjG9f4soxQAsBHLqpMZ5fGpa/K01HAzW67NPxc1oJ9czbBsr5H4MIcQyg4D2GzTMGYnYOwcr9QCPNBTmJ%2BGSITZwGRG05WtUkDlShOVRpDQSJIBIPVqFcB2LGnY7GYHabkZzcB31NMcZWk5pqKc4jpGcJIIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/varybivore/contains.hpp)
- [unit test](../../../../tests/unit/varybivore/contains.test.hpp)
