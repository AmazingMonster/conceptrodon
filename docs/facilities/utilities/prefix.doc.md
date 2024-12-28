<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Prefix`

<p style='text-align: right;'><a href="../utilities.md#prefix">To Index</a></p>

## Description

`Prefix` accepts an element and an index. It constantly evaluates to `true`.

<pre><code>Element, Index -> true</code></pre>

## Structure

```C++
template<typename, size_t>
concept Prefix = REQUIREMENT;
```

## Examples

This concept works as an enumerator of arguments when expanded alongside an index sequence.
In the following example, We will use `Prefix` to count out the first three arguments and return the fourth one.

```C++
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

/**** TheFourth_v ****/
template<auto...Args>
constexpr auto TheFourth_v
= Midst<std::make_index_sequence<3>>::idyl(Args...);

/**** Tests ****/
static_assert(TheFourth_v<0, 1, 2, 3, 4> == 3);
static_assert(TheFourth_v<0, 1, 2, -3, 4> == -3);
```

## Implementation

```C++
template<typename, size_t>
concept Prefix = true;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwapK4AMngMmAByPgBGmMQgAMwAnKQADqgKhE4MHt6%2BAUEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMiXCyG8WFuJkSbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3AQAJ7PZhsUi3LIAL0wAH0CKiQWgGFs0gRbspiJgaKoYYl7rcCMQvJhYVYrhjad99XdsKpWMTMJScUaDXS9XqwRCoRa2V5HLRCBzxXbrkdbgBZPDoCaW22XRnM8nauGc7msKNoq4TTUOf2B4MmADsVgz9x19LDTOJkbZgpFBAAdJX8V7LkmvCmA0GxXDESAQOEsKphUoAI5aqVRtz4yvl8WJBPArMg24z247Ha3ADqFq8ShhADYNPLFXhVGzq%2BPbkxXagRyZN%2BrULdGD54pHbl4GAB3QyM9BH4jAW%2BCBSjq6z/kWkcZBbklCZMFUNJiCPE9bkDDlaAgbclX3VEYKIEc%2BWPIh1VaYBMAILCTxHZZp1nTMLFuBUCA2BhcM/AidRhHN0RYxJdWBX5fQAFQQTAADF1jaBBhQANxDIFwyLVk4Ww09K0uT8FBrMDGUg6C5NuXiBKEggRNE9FVVTJsSwIdA2xYJgAGsRQ7CDu0wPtXkHRIx2wNt4MQxTgF/StSPY/M8W4j4CE%2BQ1EyAvBkGFJgFCUNoIG0wSNj0sS2SCW4uD5Mw%2BUSPlJDQ2FcyMxJ/I4uZgJiuL4gIRK%2BOS4S0rhDKstuHLbgAWjy24CsPIqis60qdQ4VZaE4fxeD8DgtFIVBODcaxrH5ISthhMEeFIAhNBG1YrICSRyw0AAOMwzGSZIuECI6jq4DMM2kMaOEkXgWAkDQgimma5o4XgFBAIItumkbSDgWAYEQEB1gINJXXISg0CJOh4kiONOFUI71w69dJFuYBkBAqRyzMXhMHwIhiEDPR%2BEEEQxHYKQZEERQVHUIHSF0LKn2IJg0k4HhRvGybttmzgAHlXRh2VUCoW50cx7HcfxzKDrMW4IA8RH6Gg8xEi4ZZeEBrRVggJAEbSJGyAoCAzYtkBgCkHKaFoRliD%2BiAYmFmJwlaDk%2Bd4L3mGIDlRZibRMAcP3SAR0kCFFhhaF9tmsBiLxgDcMRaD%2B7heCwSyjHEJO8AVBw8FEj5hYg8PXW2DbwkZR6ZvdGJuaDjwsGFjU8Fe7PSDL4gYkyTBHjz4B3SMbbVioAwfIANXeJ9Re5SPqeEURxAZlfmbUYWOf0QxjEWyx9DwGI/sgVZUBlHIs46xEitMSxrDML6%2B4prAz4gVY7HDxoXAYdxPCdD0KEcIwwqijCysUbIAhph%2BEgZkaBDAFgjASFlb%2BJcBD9CmIAgoaD6g/z6JMQYoDFgQNsEQ2Beg5htGQeA1BX8Vr0wFhwCapBPq8G%2BrLDGWMcZ4wJirNWuBCAkDWrrfWm0J6rD4kwLACRP6kD2pIRI5ZkiJHuhoSQZhJCbg0P4dcqRHrPVIK9XW5Z1xcHXEdZIN11z%2BEkJdVR642HC2%2Br9f6EigbG3BibSGEtYZWxtlrFGbBOCtBYKJDMHUmCgQMEYTKyRyxcEOiTMmJBKZZRXrTde0hN5KG3mzXQOUuY8z9sw1h7CRYcHFtDV0txpZcPljjSE%2B94mJMOmrDW5staiLMOIw2wMfGBPiHDa2qBNajGaUYLgF0ghOxdm7D2bMA4%2B0jssoOIcw4Rx7tHRgsd46JxmsnVO6daCZ0jrnfeBdDlFwIWXLOM1K7IGrpHOu9RhZNxbhyNu2wZqd27htPuA8lDD0ueEUAni%2BDTwUHPTAC8l490yWvemOTZBb1ZjNQpe9x4PysEfJuH8L5XwEDfO%2BqocVPxfvEN%2B5dz49AIc4CArhKFZRARUFBegoGNGZekBBjRaFLDwb0TBFCcFwLpRgpoRD%2BVkOoe0UVVCpUkPZXrNYGwtgSDKULNmnC5Y8JiS06ZbSNCCNSdrdafTJGkGkbIygzCjEmISRojM/hkh3USJo7R9jnHas4G4gGE8QbeKQFDSWIyhnEGCdsMJCsWAKFEiBUShqWQhRScIt%2BVNZBZORYzeQeT0U6CSKQYpvNs6au9V9MWfipYy1UDGuNCak2RmDOrMZXT4iiNKgbANgzW0WzDb2rWIB41pDSGJaZwpk0TGFLWnJdB5mUEWTNNZicNrLo2T/SOOzBBxwTsLI5acM5Zw2hc/OPyc43JLnciuqgq6MheYIN5bMPk%2B2%2BR3Cm/zeCAsHiC/OYKA1TyYLPeei9GDL0zUiiQKKmZ5p3oW2JB9H54pPgS2aRKGBZx2K2cllhn4cNfoGGl8j0G/0Zf/blrKwECp5SUHI3LOU5Glag8VjQsFyvyGK4jhD5hKroQqgY3LZWMY1aqzYTD9CC3LRwzgss63xtuImhJk7ZQQCEeTUResu2eKkZgGRox5GGJeiAM65ZEiJH8IEex71TMZksZJypfqPFG12iASQ/gVG3QzO9I6kgLpcBOmYJxj1EhaorT9RzO1xMcGJnZ1x4XlirD7lkZwkggA)$Done$

## Links

- [Example](../../code/facilities/utilities/prefix/implementation.hpp)
- [Source code](../../../conceptrodon/prefix.hpp)
