<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Among`

## Description

`Typelivore::Among` picks out the element at a given index from a list.
<pre><code>...Element<sub><i>i</i></sub>... -> I -> Element<sub><i>i</i></sub></code></pre>

## Type Signature

```Haskell
Among :: typename... -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Among
{
    template<auto...>
    alias Page = RESULT;
};
```

## Example

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
using SupposedResult = int***;

using Result = Among<int, int*, int**, int***>::Page<3>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Typelivore::Among` first reduces the requested index by removing elements from the front of the list via recursion.
When the index reaches one of the base cases, the function returns the element at the index directly.

A simplified version will be as follows:

```C++
template<typename...Elements>
struct Among {};

template<typename First>
struct Among<First>
{
    template<size_t I>
    struct Detail {};

    template<size_t I>
    requires (I==0)
    struct Detail<I>
    { using type = First; };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};

template<typename First, typename Second, typename...Others>
struct Among<First, Second, Others...>
{
    template<size_t I>
    struct Detail 
    { using type = Among<Others...>::template Detail<I - 2>::type; };

    template<size_t I>
    requires (I==0)
    struct Detail<I>
    { using type = First; };

    template<size_t I>
    requires (I==1)
    struct Detail<I>
    { using type = Second; };

    template<auto...Agreements>
    using Page = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCCSGqQADqgKhE4MHt6%2BeqnpjgKh4VEssfGBdpgOmUIETMQE2T5%2BlZj2hQx1DQTFkTFxCUkK9Y3NuVy2o71h/WWD/gCUtqhexMjsHOb%2BYcjeWADUJv5uyCPoWFTH2CYaAIK3dwSYLMkGz8duBACeyYysmAAdMDsPQ2IIFNdHiNiF4HAc7iwBMAjgB2KyogAixys90ez1e70wnx%2Bf2YbAOADE8MQRlD7jC4QQEUijJ9qbSCPSHujHgd%2BQcCW8mB8TukAF6YAD6zIAktyBQdGfDMZh6nQ0Rjsf5cQ97oqhUTPhLpXKFQLiJgAI5eGmYBQHCDy/zazEaRZ8gXK5mq9W0T7Om76gUmdEHLzpIyC36YI4uqk0uk6tHa3We/mGkXEk5MLxEYGAu7AS0vRgESH%2BIN3RURsIo5RMYCx46Yg6%2Bph0T5Fkvg8sF64gECk7NprE4x74l7C0VfGPk2MckakaNkgEHITVAToZfD%2BcFgDyBAQcQrVe9LOR7MTBGXG7QDG3B0Px9p/crE95wYzU6NYrwkplA5A3TJUCFhFU1Q7Wgji/TVw0jFFhzjVtEUvE5nxPN9sEHTNnjbSDOxOWUDgAWgOMwByHGMcRTcc8Vg3DszcE1AOA2DLRtO0HSdFsW3dEDz3bQi3DY6sQzDWsoyQlsE05GjQ1TCcGJ/LNjX/U0gPNfkONtS1uOdV0uA9WDBII/0iK0uDJMQmNkPXTcH3kscdSUsTv0JVSczzVAC27TBSwhSzrIOBsmzsoTzLcPyAr7YFKOHOieUU%2Bi7gAegAKkyrLstSx4MsygAVbAhAKrLcvufLspy1ztl2fZmxOe8NmSctuUeYKhC8ZJ8kwdAACV7S8WhmRksICCyxL2oQg4BoUIaRvjVC2ROMblzG9K1sETLNvGzLKNCpj/ChFyUpGEU8GQKUmAUJRGggc5BwUAErorNxZvm28up6/rBuG64PROu4OGWWhOAAVl4PxuF4VBODcaxrCVVZ1mbMx/B4UgCE0YHlgAaxAMHJEBDRJC4VF/A0MGNDMAA2GmzAADgZ/ROEkXgWAkDQkihrRSFhjheAUEAkixjgtGWOBYBgRAQFWAhkjzchKDQV46DiCIAU4VQGZpkiackA5gGQZADikQEzF4XrCBIPB0D0fhBBEMR2CkGRBEUFR1DFnQ9AAd2IJhkk4HgQfByHsb5zh9zzBXmVQKgDm13X9cN43TaJsxHQ8VX6GII40aM3hRfF0gICQFXkjVsgKAgCuq5AYApDMPg6GeWlKGiCPojCBpvmD3hu%2BYYhvn3aJtGqUWMZV3t9wYWg%2B%2B90gsGiLxgDcMRaCF6Gl5eQxgHERf8EtGoADd7QjzBVGqPNNgxsb2gj2g8GiAPh48LAI7AvAOe3s/iGiNImBVQsD3k/Iw2NlhUAMMABQAA1PAmBfb7jJP3N2whRDiFdg7eQSg1AR10JMAw4DTCWGsPoZ%2BQtIDLFQC1TIW8SLnBbCQqwlgzC81QH/Ygttz5UNsO0CemQXAPnGH4SYIRZilHKHkNIGQBAiOkQUTIfRJGDEmFUGoAhuhjE8C0PQ6jOhaJmCUAY8Q1HTHkWYnoyiTESGWAoZGGxbEsw4BDUgPMYacETjrPWBsjYmzNpnCAuBrZ522IXTGEDljHiYFgeIEA8YJH8ICAAnP4VEiRJBmEkDTLmYMabJOcWzUgHN0aAhplwGmDNkkMwqYTLgYNUk0zcRHfmgthYRO9hLaWZdZYx0VjXOuucNZsE4A0FgJ9UQkSYAcPYe9TbJMBFwYmlt8BEC4XbSY2CnaYOkNgj2eDF66Gbv7QO/dQ4uPDovfm0d5Z5gOPHA4YyJlTJmUQlEXAFlLI0FnVAOc4j538GYRYRcIGl3Lr8yuucla1whfXJ5kzZlGA%2BVwJINBhong7l3Huw9UGD17qPceDhUHTzLLPeeEdl6r3XrQTeqCsAgKMAfXmR8BFny3rzS%2B19nioPvqDReT8X693fpsXmX8f4Yz/gApQwDQF1lBVAxscCEFIJQdvLZGCXa7NkPsr2vMjn6D3igBGlhyHREofEvmtCBD0MYS6Zh1g2Ew04dw81dj%2BEaL8BAVwFiggPmsfMUxKQZGdB9fkWRDB/VSLUe6gx5idETD4R0Wo0xI2qKmD0H1Z1GiptMXYhxLtzmuPcZHDgjziDjMmdMxF7zPnE0dMEtZALwnFxxqQaJsTKDnKKSUhZJNUQNNROTTJ2TSbNKuZwNpItQWSxlnLWO0LBnq01hwMZKcWAKBPibE%2BHzAREhGCskJtt7ayG2ZqtBOr8EBFICcoO0NC2XPYVHPpccE6roNuuzdBxt0LL3cyCA2dIX/O2EsEFnSwUoFhVCgZkHBibu6lKb9Upf1XXLfrFu6L24QE7ovPFOLt64ZHmPCexLfkzzngvZlmAV5rw3lvDG9LQEit4Cy0%2B59F6cuQDfHlggH78ufq/b4wrP5cPFbwSVgCZWMrlWBhVMD4GIOQYwVB6rnYSC1e7XBuqfaBDeUa0hJqBWustZ0LeqUHr2tYew51WAjP6MEV64R8bRG%2BvQDmhR4bQ3BqURImx0ak2aLjTkZzdmAtWJ8wGvRgXdGWOzeFqNea1iOKMs4otLTPFvoOB%2BrdO7f31tWSQJtwKOniyiZgGJgwLV8u7SAMwCz/D%2BDBlTUmXN6uokqWOx9AtbDtJbYsBJkgwYpLBgzWmyTJDJPJmkrgOnOD%2BAfR4rrvXzkWw6wt0DJXSB/3SM4SQQA)

## Links

- [source code](../../../../conceptrodon/typelivore/among.hpp)
- [unit test](../../../../tests/unit/typelivore/among.test.hpp)
