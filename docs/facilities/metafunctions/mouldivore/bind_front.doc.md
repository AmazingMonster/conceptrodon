<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Mouldivore::BindFront`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#mouldivore-bind-front">To Index</a></p>

## Description

`Mouldivore::BindFront` accepts an operation.
Its first layer accepts a list of elements and returns a function.
When invoked, the function adds the elements to the front of the argument list and instantiates the operation with the result.

<pre><code>   Operation
-> Elements...
-> Arguments...
-> Operation&lt;Elements..., Arguments...&gt;</code></pre>

## Type Signature

```Haskell
BindFront
 :: template<typename...> class... 
 -> typename...
 -> template<typename...>
```

## Structure

```C++
template<template<typename...> class>
struct BindFront
{
    template<typename...>
    alias Page
    {
        template<typename...>
        alias Page = RESULT;
    };
};
```

## Examples

We will bind `int, int**` to the front of `Operation`.

```C++
template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**, int***>;

template<typename...Args>
using Metafunction = BindFront<Operation>
::Mold<int, int*>
::Mold<Args...>;

using Result = Metafunction<int**, int***>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

The key is to halt the invocation of `Operation` until the argument list is fully provided.

Here's the entire implementation:

```C++
template<template<typename...> class Operation>
struct BindFront
{
    template<typename...Beginnings>
    struct ProtoMold
    {
        template<typename...Elements>
        using Mold = Operation<Beginnings..., Elements...>;
    };

    template<typename...Beginnings>
    using Mold = ProtoMold<Beginnings...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIHBAA6oCoRODB7evnppGY4C4ZExLPGJZly2mPZFDEIETMQEOT5%2BQTV1WY3NBCXRcQlJwQpNLW151WN9A2UVIFUAlLaoXsTI7BwEmCwpBjsmgW47eweYRycAnimMrJgAdE9H2ADUyAYKCq8A8rfETHqLxMGgAgmNiF4HK8LBF0AAxYiyEGgkwAdisYNe2Nep32gIuxwINzubCeDwsmGAEQYEWACmBWJxEKhBFeyiRRAAsp50Cica90ZjQQKBXjzpdibdmGSnth6GxBAzAth%2BaLsV4MkZXjzaOhBYEACK/f6ArKXSnUhi0owKcmkV7y3aMAh254qo7CgXow2elFq7HigmSkkyx5PS00unK1VMjVa4A63kG40c1Dc3kWqlR23k4GBYU%2Bv1glEAegAVJWq9Wa6Wy9XXgAVTBjb7Vutgis17tVjuoktmQIRD5eLAGtxoBibFKuxn90FBw5E0P3PMesEs6F/BJmgTF%2BeaumvIReFIFTDoABKLa8tDZR2N24BQOOEQIDrf5Y/gkr34IVfzQswUXQlrmlVcnlBYh6TnQ9tS5TAmioLwp3qFMYThRFkWOJ9dwYOcQBAXU%2BVfQQ/3LAiiMzY4oPpNdVQLf0wTgxNrwUW97yNHVEKYZDUPNUj/y/V5P0rQCmPBJpHGQAB9JgvgSAgIDGdBCIUe45OVNw2I4h0TzPdILx0u8XiWT0OBWWhOH8Xg/A4LRSFQTg3GsaxXgUNYNkwQVBx4UgCE0CyVgAawCSQHg0SQuDRQINH8DQzAANkSswAA5Uv0ThJF4FgJA0DRSDshynI4XgFBAAqAvsizSDgWAYEQEA1gIFIvHfCgIDQPY6ASKJ7k4VRUsSgBaRLJFeYBkGQV4pAeMxeAvQgSDwVTqn4QQRDEdgpBkQRFBUdRqtIXRqgAdwBFJOB4SzrNswLHM4H42tatlUCoV5BpGsaJqmmbwrMV4IA8br6GIHzAi4JZeCqrQVggJAupSHqyA6xHkZAYApDMPg6B2YhyogWJ7tiCJmiuK7eBJ5hiCuH5Ym0TAHAp0gusVAgfgYWhyaOrBYi8YA3DEWhyu4XgsBYQxgHEHm8GIRnHAANxbe7MFURm2q2Py31qe7aDwWIARpjwsHughiDwXLRdIJXiFiQzDV2SW9aMQKVioAx6QANTwTBTu3Oy/PW4RRHEHag/2tR7pO/RJZQVzLH0fXysgFZUBnLIReGlSH1MSxrDMYqbfNrBk4gFY7HlrIXAYdxPHaPQwgiQZymGaoCkyARJj8Nv0g7hg5iGRJplqSuBF6CY66mLpR4acZ%2Bib%2BZW9sOeu70GYWgHluh/LzzNgkG6OBswr7pKj6htG8bJum2aAYgXAlrB8wIah/zXZWBBMCYLBEjL0hQskQIDwACcgQ0SSEimYSQiV8r%2BESkAzKHBsqkFyhDB4iUuCJVSkA1KGD/BRX8CAxKx8jolTKhVV%2B1U4YNXhk1Z6bVyCUDRqDPqbBODNBYArNEw0mDvAMNqLgQCHhcAigtfARBi56CDptUO0hw5KEjkdXQ2NzpMEuqLA%2BR8iq8BKk9FqbVXhvVeOwzh3DeGSxmoI4RGhAbAyRqDcGZgX4wxqjQphCQGGdVQCDYYxiuEfElgIrgBUaB3gSATImR0qZk2ZlEmmdMGZMytqzF0HMub3V5vzQWtBhbM3Fk7LYDl8BywcHgJWIsHKq3VjsZm2srJHT1gbMmxsCnQ3NpbPyNs7ZKAdhLIwztQCUL4B7BQ3tfb%2B2ZlIkO21ZGyAjodBySiY4u1zlYBODTS6p3TgITO2cjQrPzoXBIxdlYp2niU5wEBXCr2qI3Uog98i93qNc0g7d6ibwWMPboY8V6T27mc%2Bo49553K3mvH5uQ/nryBc3D5O91h70hggzRJ9OBGOIBwrhPD/H8MsRFQG99xHg0htDN%2BpAP5f2GL/OpSCUGCMimiAhaIYqSEgWNaoWiHqlVsOQ5xVD4A0Oai9DxbjiAsK2Ow76LAFAK2mgrARDxzhjFEQ/FakjZDSOmbteQ8j5k6CSKQFRajrqIruiQx6dDXrvXFeNSV0rXiysEQqtkQMvF2ISODQITjXa1QRi65GQrfWgxANKs8Ml7UyUdXJNFY0cahPxpQCJDlYncz8km%2BJ8tmbJMEKk7mhTMB8wFkLEWfk8l9JaaQIplcykqzVsgDWNTBA63qfrQ2VxmmmzaczTp9tHZ9LpF692TAvY%2Bz9tKCZaqpkSBmXtbVUc9V8OMPHGw6z4CbPqCLUsKk4550sAXbRRcVonN/hXc5fhLk12ebc6FS9XlZGeTe4oC97mfJnoC55x6AVz3eUvSFb7P2PpBQijycLtoaJNcVFFVrXg2plXKx1eKxEkEJZ6yh79P7f0oAfalixBHJH8PFKK%2BVkhokwcQ8DnLyqVRJf/fwwD/CpSSkAyQQCYqgK4MEOpgQwPaM4MSlDCD5qke45ynlKwbYZGcJIIAA%3D)

## Links

- [source code](../../../../conceptrodon/mouldivore/bind_front.hpp)
- [unit test](../../../../tests/unit/metafunctions/mouldivore/bind_front.test.hpp)
