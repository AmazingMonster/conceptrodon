<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AllConfess`

<p style='text-align: right;'><a href="../../../index.md#conceptualizations-3">To Index</a></p>

## Description

`Varybivore::AllConfess` accepts a callable predicate and a list of elements.
It returns true if the predicate evaluates to `true` for the value result of every element and returns false if otherwise.

<pre><code>   Predicate, Elements...
-> (...&&Predicate(Elements::value))</code></pre>

## Structure

```C++
template<auto, typename...>
concept AllConfess = REQUIREMENT;
```

## Examples

`AllConfess` turns a fold expression of a callable predicate over `&&` into a concept so that it can be used for subsumption.

The following code will fail since `(...&&Pred_0(*))` and `(...&&Pred_0(*)) && (...&&Pred_1(*))` are both atomic:

```C++
constexpr auto Pred_0 = [](auto...){return true;};

constexpr auto Pred_1 = [](auto...){return true;};

template<auto I>
struct Vay
{
    static constexpr auto value {I};
};

template<typename...Args>
requires (...&&Pred_0(Args::value))
constexpr bool fun(){return false;}

template<typename...Args>
requires(...&&Pred_0(Args::value)) && (...&&Pred_1(Args::value))
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMwArKSuADJ4DJgAcj4ARpjEEgCcpAAOqAqETgwe3r4BwemZjgLhkTEs8YlcKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BxoDHOYqqnEANRMXkSnysSY6AD6Gqcm/gAiz4FWga8QF0QAdIDViYAOwWW4ELYMU4EYheTAvKwg16IkwaACCaPR%2B0OxzOf1Q11uDy4zzeHy%2BPwJgP%2BwLBEKhMLhCP8SJRrKxWIImBYqQM3JebgJpwAki9sFi5nCHKcALICVBEBgAT05YKxp01pzmTEcyFOOO5ePOl0JADcxPDnmCxcjURjQeyrA6MdzefyWW4CMrUoxWJgaejiMAFOKsbcAI5ePC3BSnCA08wANmTNzujwgQZDIBAFu8mFWwIxhqOJ1OsVQnlOVC8DAgdPBmEhxGhVDESlRdpd6LdfN1nu9vuYbEDwdD/glGMj0djCcBydTxIzWYUObz8MLzzMKe38cT28X6a4mbHa8tBaL2IEuLLFarNbrDYZLaZ8M7KO7Or19yYCiUrWoWtBXlBhFQEVV/DcLgwwnetgVZDh1loThAl4PwOC0UhUE4NxrGsbVNm2TAt38HhSAITREPWABrEBAiTf4AA4kykQIQSTSQkn8dizH8fROEkXgWAkDQNFIdDMOwjheFXMSKIwxDSDgWAYEQEBNgIVJLnISg0F5OgEiif1OFUZiAFoONOYBkH1KR/jMXg7kIEg8HQPR%2BEEEQxHYKQZEERQVHUBTSF0LhSAAd2IJhUk4HgkJQtDKKwzgAHlLi0ghTlQKhTlMpMLMkKybNOOyzHjDx9PoM5zFI1ZeHkrR1ggJA9NSAyyAoCBWvakBgCkMw%2BDobliFXCBYiS2IIhaZVYt4SbmGIZUUtibR6nksi9LYQQUoYWgZuCrBYi8YAhVoWhV24XgsBYQxgHEA6YzWvAzUwC7MKOepLl2MiIm5ZDgtoPBYiixaPCwJLYTwYTLtIF7iArJRXh5W7AaMSj1ioAwQwANTwTBwpSodZr84RRHEXyPPkJQ1CS0L9FulA8MsfQgdXSB1lQVI%2Bgusy5nQF5XlMSxrDMSS4eIVzXvgdY6gaZwIFcaY/DCsJFgqKo9CKLIBCVzWMm1hhhnVlZul6Rp5l1sLZb6AZWiN0ZqgmQZLadu21YdiQZcInZPf4jhUPEpKpNy8zLOs2zJHs%2BNcGc6reK4OryPR9YEEwJgsESetSFoyR/H%2BLiQUkDRJDMSQk1E%2BiUn%2BwTSGE0j/hYpNGKSRiuCTQJJC4QIuKTQPgqkmSQDk9GlNU5r1PS7TOu6qqjLYTgWhYM0QTMpgDQMIwSqSf4uH%2Bd78CICW3LCymvPJ6RKYCmngt0AbIui2b4v9xL%2B9SyfMuy85iCXle1%2BQDfgBbx3nvcqqBKoJBImYRODVFLjxngkHSXUwFtSqiARey8zL/1ujULgYkaC0GGqNcawV5rTWJqQxay1VoOGJptRgBAdp7SSodY6p1zrE2uijXYmF8C3AaC9N6jlVCfW5MTX6PQkqA2BtNMG3D6oS2hmROGCNMBIxukYVGoAFIYyxgoXG%2BNCaMGJqfMmPkL6yCvkFTCt96ZoyFlYZmUi2ZZ05tzTgvMCD8zePYkWYsEhHyluzU2T15aK08B0PQqtygezClrPoLs4nZHtssR21tzbO3CfkK2PQQn9HmMkjWVsLaZOVq7BY0SUm%2BwUN7HyT8A4SV4MHdBv9163SAbvJ4EAY6HxIgneqydSCp3TmMLO1chIBG3sXEE3cQQgn8CXMunc%2B6SU4IPYe2jR7wHHhpDKiD4HEDnrsRelkWAKDNPqM0NR/gejmI5A%2BLlj4kzPmYkmljaYBAilFGKl06kvxWRwNKmlLhZRyscwqpzzmnEudvG5mUIAVRQRAmq/hoEjzgcg9qeyMWoPOakVI9xoX3FhT%2Bb%2BHFBoEISEQiaU1FrkJpUtFaa1aFgK2gw3a%2B0eGYCOidMQ7CYacI0XI0gvCnoCKSh9ZAX0xGCAkQDIGINlSyIhgo4myiMiqORhoiIWjGp8F0fogmRMYYmO8hIcx/lqZWJ0B8gBjNhaONZtLLCXNsgXQAPR8ztQ4iwotGni0ls4mWOS5Z%2BAVgwdwJTInhoKSbRJOtI2xP1n0GNqTg022KXkUpaSBC23KUsQpZSXY6jdhUwpXstg%2BwTn7epQdOBfxYCcs5FyrmwujvcuOtV%2BnaJTmnDOlAn412EmYbe/ggiBGLrgjQo72KMWWY01Ztgh5J27dnEAucd7%2BEYh3Xi46ky8XYn7fwfz53SWXY1J%2BDk53JVPTAwssNKXZDXUAA)

By turning `(...&&Pred_0(*))` and `(...&&Pred_1(*))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<typename...Args>
requires AllConfess<Pred_0, Args...>
constexpr bool fun(){return false;}

template<typename...Args>
requires AllConfess<Pred_0, Args...> && AllConfess<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<Vay<1>>());
```

## Implementation

```C++
template<auto Predicate, typename...Elements>
concept AllConfess = (...&&Predicate(Elements::value));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAbKSuADJ4DJgAcj4ARpjEIGakAA6oCoRODB7evgHBaRmOAuGRMSzxicl2mA5ZQgRMxAQ5Pn5Btpj2xQwNTQSl0XEJSbaNza15HQrjAxFDFSNmAJS2qF7EyOwcBJgsKQa7JgDMbkxeRADUysSY%2BKK7pJcEAJ4pjKyYAHQ/2PRsggUJ2wJg0AEE0AwtikCJcwbRaB4GFRMAoFJcTgARS4QH5fcyBAk3O54B6YCB/PaMAgKEAgABuYi8mGWyxOVnBoLBAHoAFT8gWCoXcrl8gWXAAqqJpl0FIvBYqFSv58rBXMhM0wqhSxEu5yuxPQAH0NBjjtiTP4rP5MRB9ag8WyAOwWW4EDYMZ7EZnskxOzG%2BzngjW7bW6%2B3XW7Grhmi1Wy22%2B2Ov2uzDu4iegjezC%2B/2BtXg3b7Q4504RgCSwK5M29DkuAFkBKgiAwXlyU1zLl3LjMmI5kJcQ1qdXqLqhLozvJgMS7K3njhy1fPF1yiwc%2B6W3K93sw2HiwcRgEDjiDwbcAI5ePC3dHwxECFFok5uQ0mp4Ho94qvBgSasOXWJUE8S4qC8BgIGdVN009KgxCUXMAyDME1xLZ9tw%2BPcfg/Y9TwPTBL2vVE4QRJFH2PF8ozfOFDwUL8TwxMxCUY4j72RVFyNfLh3xoujcKHf9AOA0DwMgt0PS9H0Fz9RCCzBXt%2ByNJg0QSAhqDA59GwYZsBDbU4uCrE8ILZBcOFWWhOH8Xg/A4LRSFQTg3Gsawe3WTZp3MY4eFIAhNFM1YAGsAkkL4NEkLgnWODR/A0RjAjMAAOeL9E4SReBYCQNA0UhrNs%2ByOF4Wksp8mzTNIOBYBgRAQHWAgUguchKDQfY6ASKJPk4VR4sCABaQJJEuYBkAHKQvjMXgSSIYg8HQPR%2BEEEQxHYKQZEERQVHUErSF0LiAHdiCYFJOB4MyLKs3y7M4AB5C46thVAqEuTqer6gahsuEazBxDxmvoXUPK4ZZeGKrRVggJAmpSFqyAoCAIahkBgCkZIaFoXZiFpCBYnO2IIiaF4jt4HHmGIF5LtibRamKrymoBAhLoYWh8c2rBYi8YAzgRWluF4LAWEMYBxGZwi6npVFzq1WoLm2LyIl2czNtoPBYn2kmPCwc6szwdLudIUXiEApRMT2fnFaMXzVioAwjwANTwTAdsuncCZW4RRHEZa5vkJQ1HO7b9H5lAnMsfQldpSBVlQGEsi57qZnQLFTEsawzFyvWpqwMOIM6boshcBh3E8No9DCeZykqPRCkyARJj8LjK56QYy5GLiajqAQ%2BgmQu8hbrpKfqWZG%2BGRIW9mGu9F7ZpB8WYfVgUVytgkE6OEs7Lzryx6ut6/rBuG4LPopfBJoYzzAe883VgQTAmCwRIs8CyRji%2BABOY4nUkUKzEkQJMqCJ/ko4VKpB0qeS%2BIELggR4pP3iuA/wYV/Av2CDlXgeUCogCKubMqlUwbVRuvVGGcNfptTYJwJoLB6ROm6kwQcBgjDvSfl8LgIVxqHxINNWasgFru2kJ7NaPtNq6GSHtA6BMl4ryQRdDg11aoXEuPdPUxAyEUKocgGhwA6EMJCl9VAP0EjHxWEDDB2CCEJAarDbRkNfogFIeQ7qKj%2BZcCflwLKKM0YYyxptImeNnaeJJmTCmDhnY02pPTRm50WZsw5rQLmXleYm22LZfAtwRZi02hLZAUtnayy6OdRWys8Zq3iUDKa2svJ6wNpgI2fMjCm1ACVC2VsFC23to7RgztPacKWtw2QvCNq2QEf7M2icrDB1yZnCOUdfycFjgQeO5ohnJ1TgkdOYtw7Zz7s4CArgx5cRLmUIeFd0hV2yF3WuqRDkN1LvsnuOd26jxOePXubdegD0udPcedzcinInnMPZbyAZrA2Avf58sxFr04PIxRlDqH83UYw00B9CAkGPgDAxdSL5XxvpQJegDgH0NCk6eBToIqSE/n1Li4iUG2DQWfOpmD4DYJqrdUxxjiBEO2KQl6LAFD0gHPSBxXwSwzGYYi9O7D5pu06S7HpvsQDHFIEIw63NRFnU2nlKRt1ZEPQ5f1LlPKJz8sFbCCA30LG6I8scU%2BwNSpGPMVDZltrLE8pSCkI0fKn5GkNYpBRfU%2BB0FcZQdxtkfFMy8sGvxlNAnaNpiEpmCTMCs3ZmIKJztYnVMKaQRJfdRZc1smkjJOssny1srklWLwCka2Kc7Mp6QKnG2qREWpIM%2BANKaQ7J2Ot2kSokF01a3tek6FlQM4wQcbCjPgOMnoXNuRx0DknSwKdkFp2misrOrceh5wLp84u%2Bcp7lzrucrI2yzlFCyLu5uaynkdxaPc656znn9DPcPMY/Qj3fMfYvAFbkP0gpVblcF2rLi6t5QajcMwcS4BFciy159SCX2viMLO8scVJHoccY4/hophUymhp0EDV6qs4Kg9BaLSD338M/fw8VGJP0kE/CKr8uByvlscX9yDCM0pBkvMa%2BG/35Q435XWCQMjOEkEAA)

## Links

- [source code](../../../../conceptrodon/varybivore/concepts/all_confess.hpp)
- [unit test](../../../../tests/unit/concepts/varybivore/all_confess.test.hpp)
