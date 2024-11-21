<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreLessThan`

## Description

`Varybivore::AreLessThan` accepts a variable and returns a predicate.
When invoked, the predicate returns true if all the arguments are less than the variable;
otherwise, the predicate returns false.

<pre><code>   Target
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (V<sub>0</sub> &lt; Target) && (V<sub>1</sub> &lt; Target) && ... && (V<sub>n</sub> &lt; Target)</code></pre>

## Type Signature

```Haskell
AreLessThan ::   auto...
                 -> auto...
                 -> auto
```

## Structure

```C++
template<auto>
struct AreLessThan
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
template<auto...Args>
using Metafunction
= AreLessThan<5>
::Page<Args...>;

static_assert(Metafunction<2, 3, 4>::value);
static_assert(! Metafunction<6, 2, 3>::value);
```

## Implementation

Here's the entire implementation:

```C++
template<auto Target>
struct AreLessThan
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(Variables < Target)) };
    };
    
    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v
    { (...&&(Variables < Target)) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDspK4AMngMmAByPgBGmMQgZgCcpAAOqAqETgwe3r7%2BQemZjgJhEdEscQnJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlUbHxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwEmCypBjsmAMxuTF5EANQAKi3AmATH2CYaAILjxF4OFy/EmCGYCgUVwQhmeLxMASsrwuMIuOz2B0wx1O51QADoMQA1Fp4JgxegKR5g2EXd6fAgXZTEVBEZRMO7E2EQqEvEkk2aOZAXNAMcaYVSpYgXGKoTwXABuYi8SOhbJhzIuEAxaPMADY1RBscRcfiARdkddbvclkt9QEACLHFkkiGWo7WpmymHw/ZMQ4nM5EZUvYC/XaMAiEo5PJ0XLyZIyU%2BmYfVHc2U6m06PIn1%2BtiCBTKon2sGM527V3ulFerE4vEEomhjl4Lk8vkCoUisV0u4AfXFebNFkVWbM6r7mrLuoUsbchuIdwIJrNdpZtqtudeAHoAFRr9cbpdg1drq7YIRXddb5cb08r4/g14uxHIz3ojE/YBBkMvcPhYAXACy9yYVC8DAcbJczjb5fn%2BQFgVBE4AFZKxeEAQBbJETkfTMMWzOdXmrZBWyYQF4gICBv2aP8AIaZEzFIC4jioyRHgQyVvEwJYFyw5pOVw/DWggMAwC/H9SMAgRkVVKjKOo%2BiQEY6UWPtDgVloThoN4PwOC0UhUE4NxrGsUk1g2GNzCOHhSAITR5JWABrEBoLMNEAjMSQAA4nOgjQklsjRVScmjFI4SReBYCQNA0UhVPUzSOF4BQQFCsy1Pk0g4FgGBEBANYCFSc5yEoNA9joeJIlYLZVCc1UAFpVUkC5gGQLkpDRMxeEwfAiG1dA9H4QQRDEdgpBkQRFBUdQEtIXQuFIAB3YgmFSTgeAUpSVPMjTOAAeXOLKKVQKgLlKiqqpquqLgasxFQ8fL6CFIyuCWXh4q0FYICQPLUgKsgKAgV73pAYApEomhaB2YgYogGIVpicIWgAT3m3hIeYYhobWmJtEwBw4dIPL0wINaGFoWHRqwGIvGAU5aFoGLuF4LAWEMYBxCJvBfkA8UARW/l0fOLYTPCHY/PU2g8BiGakY8LAVoIbUgup0g2eIEUlHNXZ6aFoxzJWKgDCfTE8EwSa1tSRhMa64RRHEfrTaGtQVvG/R6ZQHTLH0YWYsgFZUFSBoqfK8Z0GOc1TEsawzAi%2BX2vZ93unRhoXAYdxPA6PRQnCIZKhGCaiiyAQpj8TOMmzhh5mGBIJrsGPegmNpE/yMu6grgQ%2BlaYv09L2wq9zvRZmb1OFgzlYFH0zYJEWjhlLClbIr2srKuq2r6skRrFVwQgSH1MxjLu0yNZWBBMCYLAEggKz/CONEkiOAJJA0SRHNVELoNVFI/IC0gguMtFVS4bykic7/oMkFwaCF9RLhV4JFaKsVt4JSeqlZ66VNrZU%2Bt9K6RU2CcBaCwcUARypMG5AYSMXAkhoi4GidSLVV7tU6rIHqFtpBWyUDbUauhKLTVmnDUe48wGrQ4BtTK5wLg7QuJg7BuD8H0xOsQ0hGhzqoEuvEdeRwzBbweoleBKD4g5S%2BnIt6V0QAiJwcgAhf0khcFCoDYGoNwajQRjDTGtikYozRhjWW2MAx4wJitYmpNyaU0xrTVWWx1L4BZo4NmVNyGqC5jsTGfM6grSFiLGG4sgn3WlpjeWitMDKzpkYNWoAYF8G1goXW%2BtDbG1lqbWhfV6GyGtiNdSLD7bqyDlYZ2iS3bHw0l7bIPs/YB1aSHMO8QI6dIHvXISfgICuE7hNFO5QS56Czg0WZaQC4NBbosOuPRG4dxrnnaOkym4DF7ossuey8gHO7ichZrcR6rHWMPW6%2BgloT1GlPAxYijESKISQshy9WprxuionepA94HxGF0l%2BgUQBHGITfAIwCAgBCOLfSQVUJrcIgbYKBqjYHwHgRlLaWiNHEDQVsTBh0WAKHFFycUvzETjGaoCqhE0qnmxqQNeQjCGk6FhVNGac1qacOWu89aiDtq7UpdValtKJQMrdACCkEALq6IUUZI4ILCnqJ0e9Eluq9G0tSKkdsRDWyMoILhYgLAqp8DoJYyg1j1IOMJiZF1TiY6YzcYIDxhNgmYBJmTMQfjZYBLyak0gISK7hI5lE5A3NYmCHiaNRJotoYpMluk2WmSMjZJVnk98Gsin0hKXrA2RtVImXZb1CQtTBo8ttvy4xjtg7tNdvAD2PSBBUyXH7FtbSLCh3AeHPAWAxmHNjtM%2BOqz5lpy2Ws4o2RVnLOyJsjOE7K79FWeXI5Vc11t2uduvdpy7nPMHo8vqIq3kRU4MI61VKaV0oVTscYALKGKNuvdUF4LD6UFHq/IKyQ0RHCONBNygCQogYCN5a94DOCQLiqC6ygRGqIq4FIJICKL5cCCH5I4oqb1RWgY9UeTVYM8K/TAlY8tMjOEkEAA)

## Links

- [source code](../../../../conceptrodon/varybivore/are_less_than.hpp)

- [unit test](../../../../tests/unit/metafunctions/varybivore/are_less_than.test.hpp)
