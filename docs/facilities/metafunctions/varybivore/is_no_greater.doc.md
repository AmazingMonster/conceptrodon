<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsNoGreater`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-no-greater">To Index</a></p>

## Description

`Varybivore::IsNoGreater` accepts a target and a list of variables.
It returns true if the target is less or equal to all the variables;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target &le; V<sub>0</sub>) && (Target &le; V<sub>1</sub>) && ... && (Target &le; V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsNoGreater
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct IsNoGreater
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsNoGreater_v
{RESULT};
```

## Examples

```C++
static_assert(IsNoGreater<5, 5, 6, 7>::value);
static_assert(! IsNoGreater<4, 2, 3, 4>::value);
```

## Implementation

We will implement `IsNoGreater` using only `<`, meaning <code>Target &le; Variable</code> is expressed as:

```C++
not (Variable < Target)
```

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsNoGreater
{
    static constexpr bool value
    { (...&&(not (Variables < Target))) };
};

template<auto Target, auto...Variables>
constexpr bool IsNoGreater_v
{ (...&&(not (Variables < Target))) };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQCcpK4AMngMmAByPgBGmMQgZlykAA6oCoRODB7evv5BaRmOAmER0SxxCUm2mPbFDEIETMQEOT5%2BgTV1WY3NBKVRsfGJyQpNLW15nWN9A%2BWVIwCUtqhexMjsHAD0AFR7%2BweHR/tbJhoAgrv7ANQAkiwp9GyCTPXXB6cXV8c/x5/nZ3OBEwDwMwJMAGY3EwvERrgAVZrATAEUjXGFEAB02IAas08EwYvQFJDsICxsQvA47gpIqgAOLETCveKAkwAdisF2uPOuM0cyGuaAYY0wqhSxGuMVQnmuADcxF5MIDedcORZrhBsZjzAA2PUQBioAiavHEAlEzAKNVQhFIlGLR1q9kAEUhXIBrvdbIuwNBLMh0NhqDtxGRqPRwe1ZotxNJgOFovFkulstutIZTJZxAA%2BnK2ZzNdq9QajSaIDHCcSbW5Q%2BHHYtnW6IR7Ad9fod/u3rthVKxHph3ic2x2/j7zvy8Mgc0wFEoWhB03TGczgcRAwBWNFb666tHs0kgEAK7yYRbei6T6ez%2BcECBgMA05dZteB6TXMxoiFoySH4%2BKs93Q4ZZaE4DdeD8DgtFIVBODcaxrD5VZ1kHcwIR4UgCE0YDlgAaxADdJExDQAA4zDMAIAi4DdSJIrh2XZaRQI4SReBYCQNA0UhIOg2COF4BQQC4rCoOA0g4FgGBEBAVYCBSWFyEoNAHjoeJIlYTZVBI3UAFpdUka5gGQQUpExMxeEwfAiHNdA9H4QQRDEdgpBkQRFBUdRRNIXRkgAd2IJgUk4HgQLAiDsJgzgAHlYXkk1UCoa4tN0/TDOM65TLMTUPBU%2BhJTQrhFl4EStGWCAkGUlJVLICgIEq6qQGAKRPxoWg10EiAYgimJwmaABPYLeB65hiD6qKYm0TAHEG0hlOeAgooYWgBq8rAYi8YBoVoWhBO4XgsBYQxgHEVa8CZBw8DlK0IrFKbYU2DDwmBZjoNoPAYgC0aPCwCKCHNdi9tIK7iGlJQXRBI63qMbDlioAxgAUHE8EwXyopSRgZvs4RRHEFysfctQIp8/QjpQBDLH0d7BMgZZUBSepdp0sZ0EhF1TEsawzF44GbOummuim%2BoXAYdxPHaPRQnCQYKmGZJCkyARJj8OX0gVhg5iGBJRlqQWenGVoxbybXugEXoWg1mWtdsfWlb0GZzal%2BZZeWBRkI2CRQo4cDuIiviku0vSDKMkyiKyiBcEIEg1TMdCiswmHlgQZksASCA8P8CFMQCCFGI0SQzEkXVOI3XUgmY1jSHY9DMV1LhdRIgI6N1QjqOzvceN4PiBKE%2BPRLKqTypk2KFNq%2Bq8vUthOGaFg5XZHSmCFAwjAygJMS4YiLKskg8Fs5Iscc3HpHxpRCa83RP38wLBs972O8ijgYrk2FrgS/2UoM5Al%2BAFe1%2BI7LUFyvEaOEIzBxxKmJQeY94iKTqgAqqeUUBfy4FRLirV2qUC6l5Ya/UZrYNGuNSa01AZzUYAtJaK1oJrQ2ltHaM0DqQ02JQs6usrq7WgrdZA90ZpPVqBFN6H1%2BrfUYcVf6M1gag0wODQ6RgoagD7nweGiNkao3RpBDC%2B8cbOSPrIAmnloLnxJtDdmVgKb8OpmnGC9MsiM2ZqzYxnNubxF5uYl2OsLrOAgK4W2yRJZlE1noeW9RvGpFVvUC2Cxja61NjbQ2ysBbuIaPrcJstrZ9GCfbfojt/GFRWGsd2OTmK319pwN%2BgdF5HR/uvDQmoI7WWAYVYqCdSBJyYCnSgnsK5V1XnndkG4AgMQhPnQukhkh3y7rYHu4D%2B7wEHrJOKMCoHEAnpsaeqUWAKDlIKOUyDMRgitAQTekcbJ2VkAfLRrl5Anz0ToEA35L5BT2jfcKXk%2BKPzii/RKqg1kbK2TsvZYx/6APyjHCEYCYbiQqnA6qCyoUIM2SkFIeZkE5n%2BQQHMXyj50HQZ1bqvVRq4LxWNCagsZokMEItZaEUqGbTELQwG9CZHCNIPgc6jhWE3VUHdYE3DBC8K8vwz6fUhG/VEYDcR6RJEQxkeEORpUFFMARkjFGaMMaAw0U5CQ2i3JXKJrcwxxhyY2DMfAWmViBC7S2MzMmHNLBc07jzHefMLF2CiX4TxItgm%2BOlhEkJRQsjBMCVkZJVsXUJLNgbXIcTQ31HDcGu2MTI3xtmFky2HtckoTTYU55vESkYuuOszZ8o/ksgBeHLewLY6NL7onZOwwLHlzYokVeEIIQbhoiMziLb2T1x9i8zg3dhJNPwpIDcWd6Lsk4iRQIXAuBkTMHuZiEJs2d37b3UqntzK9pzfxNdOEgbxAyM4SQQA)$Done$

## Links

- [source code](../../../../conceptrodon/varybivore/is_no_greater.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/is_no_greater.test.hpp)
