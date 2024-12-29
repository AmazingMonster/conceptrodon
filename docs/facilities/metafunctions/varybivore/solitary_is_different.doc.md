<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SolitaryIsDifferent`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-solitary-is-different">To Index</a></p>

## Description

`Varybivore::SolitaryIsDifferent` accepts two variables.
It returns true if they are different and returns false otherwise.

<pre><code>   Left, Right
-> Left `different from` Right ?
   true : false</code></pre>

## Type Signature

```Haskell
SolitaryIsDifferent
 :: auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct SolitaryIsDifferent
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto>
constexpr bool SolitaryIsDifferent_v
{RESULT};
```

## Examples

```C++
static_assert(SolitaryIsDifferent<1, 1.0>::value);
static_assert(!SolitaryIsDifferent<1, 1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto, auto>
struct SolitaryIsDifferent
{ static constexpr bool value {true}; };

template<auto Variable>
struct SolitaryIsDifferent<Variable, Variable>
{ static constexpr bool value {false}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwapK4AMngMmAByPgBGmMQSABykAA6oCoRODB7evgFBaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHAD0AFSHR8cnp0e7JhoAggdHANQAkiwp9GyCTL13xxfXt2f/Zx%2BV0uVwImGeBjBJgAzG4mF4iKQ7vCiDDsCDZsQvA47kJPIRmgBPB4KAAieCoVHijAIIJMAHYLHdZh88Mg7mgGLNMKoUsQ7jFUJ47gA3MReTB3BkWAhYzAM0kwpkKpV065giEfeWwlGoO4ANWaeCYMXoaIxsuxBFx%2BImxLJFKpxBpMLchuIxtNmCR7s9Zuh6Ou0uZTUc7M53N5/MFwrF3kl0qoYiUKuhyvpirTapuAP%2BQL%2B%2Bzu2FUrBeku%2BIILufO2ZZYYA%2BkwFEoWhA8bQCcR7eTKdTBK6uEiuAA6DRokAgOMSlaq651tmN5vxAgQMBgdud7uOvu02GDu5cceT8WYGdpjhrWicfy8PwcLSkVCcNzWazMjZbBNmaE8UgETQXmsADWASSKOiRmGYACcUFcIEiSJFw9L0tIV4cJIvAsBIGhBHeD5PhwvAKCAQT/veF6kHAsAwIgIAbAQKQIuQlBoM8dDxJErA7KoiQAGwALS8ZIdzAMg7JSMOZi8Jg%2BBEB66B6PwggiGI7BSDIgiKCo6jkaQuiDgA7sQTApJwPCXtet4AY%2BnAAPIIox1qoFQdw8QJQkiWJB5gWYdwQB4bH0Py5g/isvBkVoawQEgrEpOxZAUBAsXxSAwBSGYfB0GCxDERAMTWTE4REmZvCFcwXa2TE2h1GRv6sW8BC2QwtCEtZWAxF4wBwrQtDEdwvBYCwhjAOIun4M69QipgfUPjydQIjsv7hGCaEPh2MTGV2HhYNZsp4Fh/WkFNxCCkopLgsNHZGABaxUAYwAKPqeCYAZtkpIwJUacIojiOpSnyEoajWfp%2BjDSgr6WPoeAxMRkBrKgKS9H1/GzOgMKkqYljWGY%2BHHfJ03wGstT1M4ECuFMfiDqECzlJUeiFJkAgU/T6SMwwQy08sXQ9A0czM4OxO9P0LQcyMVTjAM/MSyLNNixIRMfts8v6JZpB4bwBGuXxgnCaJ4k%2BX5uCECQUrflwYV/jdawIJgTBYAkEDASAkjQsOUHQihGiSGYki8Th/i8VBKvoZhIA/sOvFcLxiRQYhvH%2BJIcHu7xavWQRREkZb5FRTR0V0Q5TGJclQWcWwnDNCwIr0vxTAcgYRgHlBw4jrNskkHgCmDv9Km/dI/1aUDum6BlRkmSVFkcDeqe6QR9kMQidzOVr7nCcg9fAI3zejn5AVxUFpvQmYFsRRRefF/EzFJaggWjGvw1cLBQQ0LQ2W5flullcVh2fxVVU1Z99UaRNRam1TAHUupiF6p9Qal0dgPnGjVPAU0ZrSVUPNMEn1lrdGsutTahJtpwPCh6A6v5jqnUwOdIaRgrqgGznwe6j1nqvXeneX83cfpqT7rIAeOkHzD1BtdTGVhIbrVho7R8iMsjI1RujIR2NcbxHxmIom3REGk3Jp4doehqZlDloOBmvQpYGKyKLJY4tBa80lpovIAtVEkz6HMUxdMBZ82sZTaW8xdFmOVgoRWakJ5T3VjZDgy8dZ12GpvFuhs27BTNsfK2pAbZ21GOItCGFSBYWhE3L29J/BQWQtCb2vtE7T3wpwDOpEbqUVzkgeijlL7n2IKXHYFcPIsAUCKdkIoH7DkhNNAg0kYkd0UrIHunCvo8OBmHUgo9TL9QCVZGedkC5ORcqoNpHSuk9L6bMHe1897xAPtCeJdCz77Pig085QVJzIBSCkes3SoL1h2QQes6y%2B5ZXiG/AqRUuyfR/oSSq1UHAAOvg1YBrUxpgM6t1KBh0YHUMIaQBBk0Ca6TmsgBamDBDYN0rgokBDdrEM%2BmQ9IFCLrUPCLQyK9CmAPSei9N6H1DrsNUhILhmlAa8J0NM9e4MsYiOhsoiRSNOC7FRvy4RFgcYazxh3AmcNuZqL8GTBg7g3HaLVU4rmximYav0azXo2rzF2KFq43I7iLECGFp4xYziPFSxZDLLxziFabCVubYOgS06cFchszpoptlal2RAI2ckD7m3CgkpJ9tKAT3SVhaCw5oTQn8IEROOEU30mjqUjW5TbCZxPisJ2kh/BuyQvSHCiRJCwWqJBFOaFoSLLKYRLOkUJ5SVzcEqN2c1jHQyM4SQQA)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/solitary_is_different/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_different.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/solitary_is_different.test.hpp)
