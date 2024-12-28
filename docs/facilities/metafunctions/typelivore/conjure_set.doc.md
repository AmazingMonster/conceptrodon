<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ConjureSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-conjure-set">To Index</a></p>

## Description

`Typelivore::ConjureSet` accepts a list of elements and returns a set that:

- contains every element in the list;
- doesn't contain repetitive elements;
- preserves the relative order of the list.

The result will be stored in a `Capsule`.

<pre><code>   Args...
-> Capsule&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
ConjureSet
 :: template<typename...>
```

## Structure

```C++
template<typename...>
alias ConjureSet = Result;
```

## Examples

We will turn `int, int*, int**, int**` into a set.

```C++
/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = ConjureSet<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`ConjureSet` is implemented as a shortcut to `TypicalConjureSet<*>::type`:

```C++
template<typename...Elements>
using ConjureSet = TypicalConjureSet<Elements...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEElxmpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcybaY9iUMQgRMxAS5Pn5BdQ3Zza0EZdFxCUkpCi1tHfndEwNDFVVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimKmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbi8jlohAAnrDsCDzOCGJCvNDYW5kBN0FgqGiMb8jrdlMRMDRVF9DkCCJgWKkDMz8QRkc9mGxSLcmAjUGSrmhsU8CFSaXSYYF7rcCMQvJhYVYriC/ntbm4mKkFF56AyDkyWWymBy4VyeaxMAA6e0iy4TJUObW6/X0VXk66UjwtBh4ABuJHYIAAKty8KJaMomBNMEaziDeR9UkwttrUP6gyGYQB2NXAq7M1nslWW7mMG3222O51eV0R1JRsSx%2BP5qx5%2B5e9W/Ha3CxxhM6pQgb0ls0WtxWqtsKnpgDWmHcsiYEQSdcVDclTZbMbjU9jyCXK8Ea8ixEdJgLINud9uXkyRgVldl8qPJ48Z/Xl8Chev3Z/t6Oz9gASpgyAbJkgbDkOY69pcE5lhicK3veSHmuW06VimNZorckJxp8X4tD%2BlykGhd4YVOM64Q6gTYARBgKMRq4/jYlEvtabA1tg9BsIITr8pxtHVvafEsowBAWAoFFXPeXGzna9oAPIEAgCQKCh6JXPWjaRtGbZTiR54JMCcISQJBBOnhDH8iZ7H4pZUkybZ2D8mpGnEAobkYje8n3o%2BETAIpb63LuhkHiqAV3vinEKQ5F7mW4zmCT59r8ql0npbWdnxfenmaXhMWytgIAgDOPbAl2VV%2Bd2CHUVhok8eJ/FSVpDEgnpO4GWIX7aBsmBCJgBB%2BYWCmNZyOE2o6CndQ8I1rrQHYAbVJWTXCmQAF6YAA%2BgQNYAJKzfe82PKRtD4kS5URFgqi7UoACOyrivih2%2BZ1JXXuNCnoaayFwtStJ4Kob1ojWABixCyFlsmKSmtyHQwCjPA4wX8s1ym5Tply/adLSOMgBECPGgZiAKQq3Hg6DIrQEDLLcAC0%2BHXSgAj4I0Yj7flsWoSVeN3hAeF5m415uKzeAKA9Nq7YG%2BJQzDbWCHDSMoxBjhGGiqw879Op6gaWFonJuMCwl7oG29yOoxrwAnXjZJAV9NWO0WJtUf9mFTdx5Y43NW6ugAEtTWAMCtzv/utHtTtte0Hfax2fW7tzzUHxKMFdBDoDdDB3Q9mDPa8WHvfR6KJwp3060Fz4zmFfqGDmNLlRFrZRTrcX8wLWCQpVHd4xAOum%2BdS0Z1nIAsEwS67bdmD3U9L1bGDnVl6bAvlY1VM05dFlKwQOVovTA/3ssxVJ%2BXDFr5WVXl%2BH3oKVXIU17C8qpyHI/lePk/T7P%2Bfz1hMeoFQGsEBYbLAdmVCql8XarSgRSAEcDvgakpIdUskkzyNETECTU8CARAhBBtbC3teI7w6jje%2BmYGADRpMNSUT9wq9VoP1Qa1CnLELchfZ4a0fTYIQbAg4txsCqFYGyBMPCuHcONN6TEEIoQJnxGKLYqRd5Xl4VqPWHoRGMjwVHJq00WrYy6v7SUaiLYwLEVqIQXhUhFGXOBD0kpRFkIsVYjINiPgGhoXKN0%2BtPRwgiAQfkfi9gBMEAcB2EczG3Fse4jBIIyFRNoB4%2BUjCqEjXxH44JBAglUxCVkwJewwnAUpGGD49jNG6QJlGXaREEgEAgKzBQMs4z4nif424TjrHoBaVrVUHBVi0E4P4XgfgOBaFIKgTgotLDWGTusTYsiwQ8FIAQTQvTVgLgCJIW0GgAAcZgzAAE59lcH8Ds7ZXA8x5mkP0jgkheAsAkBoDQpBhmjPGRwXgCgQBPOWSM3ppA4CwBgIgEA6wCCpAROQSgaBWR0ASFEG0nBVDbIAGyM2RZIW4wBkBEykLaMwvBlyEBINTPQ/BBAiDEOwKQMhBCKBUOoX5pBdBcFIAAd2ILqTgPA%2BkDKGSssZnAVIInBZKABtwkWovRZi7FtxcVmFuBADwML6DEBhAs5YvAflaFWBAJA0LmwqshRAfVsLEjACkCkGgCTNKUFiPy2IERWjIi5bwB1zBiDIhUrEbQ6sXWkGhVZFSDBaDOsZVgWIXhgA6loLQT53BeBYHHkYcQYa8A0jRjBONoyZ4QQRNsRZfj6j8qRLEDlHqPBYH5YqPA9z42kBgsQWILjHhJuAEiIwKzVhUAMMABQAA1d4rKVI8j9WS4Q0YqXSDHXStQ/LmX6EMMYaw1h9B4FiJ8yAqxUCKOyHGxmRIn6mCmZYMwryG3EGph8eAqw7Dq2yC4HO0w/AsrCOuRYowWVFCyAIJ9egv2NAWCMaoPQ70CH6FMTwnQ9C3rRmByYgw31Aeg/B39LK5htEA5UD9N7ZlbAkDyjggznn8reeKlFaKMVYpxZs%2BVwCOYkDVYELgGqlmdtWBpJgWBEj01IOsyQgRbT7MCJcjQkgzCSGRY8/wyL9n6E4Lc0g9ymO2mRVwZF2z9lnORf4SQxyhPIuI4yt5Hyvmsd%2BTqoFuqQXCohRQY1qBlVwoRRwVoLBAx5kZkwJii7ZX7NtFwLZBL6MXqziysdFLxDUunUoWdjLdApHZZy%2BNBGiMvN4G8oVYKES3DFRKij3nnxcD8wFjQCqlUGoSIxswLGtV/Ksyaw1dmGujEIkYIrXAnlWuZN5W19rHUer9W6p1XqfUOD9QGqSQaQ38vDZG6Nsa/WJsXSm0Z%2BB02OEzfynNkFmR%2BsLdc0ZJay3IgrdsUZ1ba2LIbU2pQLblvBU7XwHt/bB3DsYKO2QEXJ00vkDFhloz4sLo7UeqwlhV3ruvWMndJNOD7szoe5dJ6z0JBC1ezdIHYN%2BAgK4VDIQc6YaWJ%2BjI36ciQfyET4o2QCcfox40cD7QyfPtp30eD1PgPoYZ3kJnHO2f4bWBsPDzG5OEb5UZzgZHJUYtayFIr/mtkKtwES1VmJmOarY6QDjXHKAEYU0pvzom8z%2BH2RcwIYmJO6cM68zgJnvmPYBcC0FIqjXNeIPCtgnBXNSpYAoQMRNAyy7LBMILSuSVhc%2BxOiQU7ZAzv%2BzoEAwREupBdSl0XVuOCZZFTlqg4qvc%2B79wHzCEwysOYq8rsEgQat271SX01zua8qpAL7qxssiu7UDwQXaqh0V8DoN1z5EA7WMqGwNutw/PXet9XWibggpuhtW5gCNUaxALbrUt5NZ2E1prvZtxl22817cEEWxlR2nWnarRey7vBrvNpZPdjt5mntMF7QOzAQ6R11vCxHqL0e/tzvj0DpdY9GwEtDdHjbdRoONHYa6EHawU9dLc9S9UAm9eoUDLHHHRnPQV9coJDCnEnXHf9KnRDLDdnFAzHenXHGDOnVnIgwnWwFDDAtDag7A4gvnBQXDKlFPS3dLcXLvDFb3X3W4f3PzdvBXYLRjVXMzbVdjTATjUYHja5XXEAA5W0QIQIfwE5XTR5VQvMdTLggVd5WwUzWrZYNZEASQfwQTc5PMR5bZSQI5LgXZMwAza5QIVPbggw4wgjfFPQ4zSQ1ZetTSe9SQIAA)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/conjure_set/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/conjure_set.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/conjure_set.test.hpp)
