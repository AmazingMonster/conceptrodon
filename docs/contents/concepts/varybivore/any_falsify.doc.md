<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `AnyFalsify`

## Description

`Varybivore::AnyFalsify` accepts a callable predicate and a list of variables.
It returns true if there exists a variable for which the predicate evaluates to `false` and returns false if otherwise.

<pre><code>   Predicate, Variables...
-> (...||(not Predicate(Variables)))</code></pre>

## Structure

```C++
template<auto, auto...>
concept AnyFalsify = REQUIREMENT;
```

## Examples

`AnyFalsify` turns a fold expression of a callable predicate over `||` into a concept so that it can be used for subsumption.

The following code will fail since `(...||(not Pred_0(*)))` and `(...||(not Pred_0(*))) && (...||(not Pred_1(*)))` are both atomic:

```C++
constexpr auto Pred_0 = [](auto...){return false;};

constexpr auto Pred_1 = [](auto...){return false;};

template<auto...Args>
requires (...||(not Pred_0(Args)))
constexpr bool fun(){return false;}

template<auto...Args>
requires (...||(not Pred_0(Args))) && (...||(not Pred_1(Args)))
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIMwCspK4AMngMmAByPgBGmMQSAMykAA6oCoRODB7evv5BaRmOAmER0SxxCVzJdpgOWUIETMQEOT5%2BgbaY9sUMjc0EpVGx8Um2TS1teZ0KE4PhwxWj1QCUtqhexMjsHGgMs5iqKcQA1ExeRCfKxJjoAPoaJyaJACJPAVYBLxDnRAB0AJWJgA7BYbgRNgwTlQxEpnlZgS94SYNABBFGovYHI6nX6oK43e5cJ6vd6fb54gF/IGg8GQ6GwzDIxHItEYgiYFgpAwc55uSkA1HEYAKZ7YDE3ACOXjwNwUJwgVJBbmVEAYqAIBNuDwgQpFKwNGKxHJxJxiqE80K8DAgNLBmAhxChMNocMSCKRbLRHK5PKZiX5F1QVL1osS4rRUplcoVSuBKvjao1WvuGl1woUBpWTzMADZzLnYwDlar1ZrrtquOn9Ya0cbDsczRbaFabXa6U6TgRiF5/R6MRjZkxHMg7kwFEoWtRrXyuGLbUD3Rw1rROAFeH4OFpSKhOCrLNYTgoNltMDnEjxSARNMu1gBrEABXN/AAcuakAWBuckAE5El%2BzGSVcOEkXgWAkDQNFITdt13DheAUEAoOvLdl1IOBYBgRAQA2AgUguchKDQLk6HiSJWB2VQ3wAWm/E5gGQZATikP4zF4W5CBIPB0D0fhBBEMR2CkGRBEUFR1FQ0hdC4UgAHdiCYFJOB4Fc1w3G8d04AB5C58M1VAqBOKjc1oyR6MY5jJFYhUPBI%2BhTnMC8Vl4FCtDWCAkGIlJSLICgIC8nyQGAKQzD4OgOWIRCIBiDSYnCZoAE9lN4OLmGIBKtJibQ6hQy9iLYQQtIYWgkskrAYi8YB%2BVoV1ktILAWEMYBxDK2UcrwAA3TBEMkw46guHZL3CDlgO3Wg8BiBT0o8LANO7PBwO4XguuIc0lBeTkmvGowbzWKgDBFAA1PBMFkrSUkYOq%2BOEURxGE66xLUDTpP0JqUGsax9AmxDIDWVAUl6HrqNmdBnheUwD0sMxYJW4huO6%2BA1lqepnAgVwpj8GTQgWcpKj0QpMgEDH8fSQmGCGXHli6HoGjmYmZOR3p%2BhaCmRiqcYBnpjmWZxtmJCRk9tn5/Q1OgjS4KMmi6IYpiWLMBVcE4hzAK4Zyr12tYEEwJgsASW1SAfSREj%2BP9gUkDRJDMSRc0gp8fxFkCwJAC8/nfXMXx/F8uFzAJJC4AI/1zMXJLghCkPV1D3KwjycN0gi/IC%2BzyLYThmhYDrgWopgTmQAwjGYn8/i4P5tw4og4Z4mTroEu7pAepQnsk3RQvkxTktUjh12D2DtLj/TDLTjOs5zvPgALouS5s1A7Pic8zDV1y0JjxP4kI/zp%2B8%2ByQEHzPc6argfy4KCaFoCKopiyTUsSuqr/SzLsocOr8sYAgipKjTysq6raqW%2BrNqMFq258A3HqF1HqpdVD9Q5HVYa3QNLjUmolGaOxtzzUWpeFaa1MAbUagA8IoBI58AOgoY6p1zqXV/tXW6Qk66yEehJbczdXo7QhlYSwX0Yg/X1v9QGnBgYEFBq8Vh1hoa8FQLDeGXCkbdHaqjdGnh2h6GxmUPmMkCa9C5uorIrMljs0ZrTTmCi8gMxkSjPocwdF4wZnTIxmNubzBUbo4Wx5NhC1Vg7LuMExGcDOMQdOmds573zgfCejwICK3LueVWLkNakC1jrUY%2BtgKgVIOBRIhcLbAgDsCYEiRLbWz9t3bx8FbDh0XlHeAMdcJ6TXivYgycdhpzoiwBQHUmIdRCX6WY7F8Dl24rxWQNcaEiXkA3BhOhnZyQUkpJaHdPHi17nhC4JwDK%2BJYM01p7TOnDm6pqCAtlN6z0cokBeu10KeQ3j5Wplyt5tJSCkO4HSfx3C6QQMcfjvxhVPvEc%2BsV4rpRvv8jKWUcpP2ngVV%2BxVSpAMwBVKqYgf6XgaltFBvBgHtTARpPqyABowMEHAySCCpoJWQXNOG6DlrxCwTgra%2BCzn7SYEdE6Z0LqbkvFQwSEhaGiTGc9SZo93qQxsAgqRO4AZZB6gAehBoKthFhRE7gkVgUV%2Bi5EMHcLYpR6rLFUy0UTTVajSa9B1Xo0xTMbG5Dsaq8xAwTV6CHJMA19i7XuJcaeYWwF5khx8U0syLS2knCeX8V5CtekkCiacyOmtta60oB3FJ4EzCF0SIkAIAQLZHw0Cmr8L4imaRKYhZCsTDbG2qC%2BX2gF025kAl%2BB2iR1LepKeUjubE82hwjm5NYK0MjOEkEAA%3D%3D%3D)

By turning `(...||(not Pred_0(*)))` and `(...||(not Pred_1(*)))` into concepts, we allow compilers to perform proper subsumption.

```C++
template<auto...Args>
requires AnyFalsify<Pred_0, Args...>
constexpr bool fun(){return false;}

template<auto...Args>
requires AnyFalsify<Pred_0, Args...> && AnyFalsify<Pred_1, Args...>
constexpr bool fun(){return true;}

static_assert(fun<1>());
```

## Implementation

```C++
template<auto Predicate, auto...Variables>
concept AnyFalsify = (...||(not Predicate(Variables)));
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAbKSuADJ4DJgAcj4ARpjEIGakAA6oCoRODB7evgHBaRmOAuGRMSzxicl2mA5ZQgRMxAQ5Pn5Btpj2xQwNTQSl0XEJSbaNza15HQrjAxFDFSNmAJS2qF7EyOwcBJgsKQa7JgDMbkxeRADUysSY%2BKK7pJfnRAB07wBqTXhMsfQKJ2wJg0AEE0AwtikCJcQQwAJ4AMTEGSocMuJwAIpcIO9XiYAOxuAluCAMVDQm53PAPTAQL7EH5/TAKZask5WUHAkEAegAVPyBYKhdyuXyBZcACrMggKS6CkWgsVC5X8hUgrngmaYVQpYjPC6oa63dAAfQ06OOWJM/is/gxEBeqFxywJFluBA2DEuVGRmHZBIx/s5oM1ux1esdRruJq4FqtNut9sdztd7s93t9/vxgeOHPVoN2%2B0OftOyfeIOIwABxyBoNuAEcvHhbrLYYjkXhUSc3JTTRonhWq7jARqBFrw5dYqhPN6vAwIC78W7MB7iF6fbQlFnA8GQYWDkwjqWDbjB9XaxXMI3m8yYfCkZvO3Du72zQPKwphzX0WZAuZAne7aPl2pyvlw75Du8I4hmOYa6pO060LO86Lsuq5egQxBeCWVjZlyXIzIe1ImkwChKM01Bzt2XCAguLq5hwqy0Jw/i8H4HBaKQqCcESljWJcCjrJsmA/scPCkAQmiMasADWASSK8GiSFw%2BLHBo/gaL%2BgRmAAHDp%2BicJIvAsBIGj9uxnHcRwvAKCA/aSRxjGkHAsAwIgIDrAQKQXOQlBoPsdAJFErDbKoOmBAAtIEkiXMAyDIJcUivGYvBUkQDLoHo/CCCIYjsFIMiCIoKjqI5pC6OBADuxBMCknA8ExLFsVJXGcAA8hc3nQqgVCXGFkXRbF8WJQpZjYh4AX0Hq5hicsvAOVoqwQEg/kpIFZAUBAq3rSAwBSMkNC0LsxC2RAsQtbEERNHC9W8JdzDEHCbWxNotQOeJ/lsIIbUMLQN1lVgsReMAZy0Jut2kFgLCGMA4gAzedQAG7Mi12q1Bc2ziREuzMWVtB4LENWPR4WAtZheAmdwvDI8QU5KBieww/jRhSasVAGFWHx4JglVtSkjAQ9lwiiOIBVC8VagtRV%2Bgwyg1jWPoBO2ZAqyoFCWS2RwEUzOgmKmHxlhmJZNMZSjKudN0WQuAw7ieG0ehhPM5SVHohSZAIkx%2BOBbs9IMzsjOBNR1AIfQTHbeSB10b31LMfvDIkgezJ7eiEc0ceLAnqyCRsWwSI1HCsaQFm8FZfXhVFMVxQlSVjRAuCECQolcHNEms6sCCYEwWCJAupByZIxyvAAnMc%2BKSEpZiSIEZlBEPBkcEZpAmWJryBFwgQ6UPOnr/4yn%2BCPwTF611m2HZreOUtbnLR5nU%2BZt21TcFbCcE0LCI/iEVMJcyAGEYiVD68LgilUr4HSngTK4Eha5VFtIcWShJZlV0MkaqtVbr50LkfKyHUvIXEuD1Z4xA34fy/j/GG/9AGKXGqgSaCRRIrHmqzZyK1qFrSmr5LaLCdqv3fhFUhRguBDy4P2Q6x1TrnTKvda6ENJGPWeq9BwENPqMAID9P6LVAbA1BuDKmkNGZGDhpxfAtwkYozKmjZAGMIbYy6C1fGhNrok22JxcmlNxI0zppgBm0N9ERFABfPgHMFBcx5nzAWOioEi3yrA2QEtSqcSQTLFm%2BsrCWEVrEZWvc1Y9E1trAgutLTJOsEbEuJtwFm17kHHo1tba5C9iEG26cXbe3SO7bI4c6k%2ByyI0gOFto4hyTu0lOUdg69Fjk7eOKcBm1Mmf0bpmc1g53yug5qZVS7cOId/X%2BwByFAPNHXUBjcZrNwYRfdundu6UHzovZeAClL4n3viVSkhJ7RXApgzgNkz4LSci5dynkursIfkFEKL9CGDRYAoRGCVEYCNeMWGYICG4ZSyrIaBUTCryHgXEnQIBjikBQXVKmyyi4tSwbfbqvVX7gshdC2F8LoQQAmqw2hM1jgt2%2BUtZhNCNp%2BU4VNEAUKUgpBNDCoeJp6UkTBbAugojKDiM4jI/64lFVyLeoo6hX0VG/X%2BoYzAQMQZiG0eJKGTMnG8CMdHZGmtOLmMsTo6xuNOJ2KJnCRxZMGSuOpgkDxXima%2BMYezJgnNua835uxcSES8oSGiUVLFUtcWJOMPLVJdiMmq3VmOTg3IdZywNhYYpXFSlYDTb0kZ1Tk7gUdmUCZzSihZArakFpvtxkZyGZbfp/QG2VJjrMltTSxidsGYnXt1bW3NwWcJPO88MGks4AQlg1KoWXFFXCw80psT13Sk3dlbdSAdy7iMXuuNrlJAAccY4/gNLKTMue/EG8SWrI%2Bafeyu7%2B7%2BGHv4HSv4h6SCHqpUeXA8W42OCsyyT6OX5xSg%2BsDJ8IOkBphkZwkggA)

## Links

- [source code](../../../../conceptrodon/varybivore/concepts/any_falsify.hpp)
- [unit test](../../../../tests/unit/concepts/varybivore/any_falsify.test.hpp)
