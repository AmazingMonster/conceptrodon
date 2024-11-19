<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Label`

## Description

`Label` accepts an element and a key.
Then, it returns a map from the key to the element and a map from the element to the key.

<pre><code>   Element, Key
-> idyl: Key -> Element
   lark: Element -> Key</code></pre>

## Structure

```C++
template<typename Element, typename Key>
struct Label
{
    static constexpr auto idyl(Key) -> Element;
    static constexpr auto lark(Element) -> Key;
};
```

## Examples

This utility creates projections between an element and a key.
We will make overload sets for `idyl` and `lark`.
Then, we will retrieve the element corresponding to the key `Key<size_t(1)>` and retrieve the key corresponding to the element `Element<-1>`.

```C++
template<auto>
struct Element {};

template<auto>
struct Key {};

// We will use this helper template to create
// overload sets for `idyl` and `lark`.
template<typename...>
struct LexiconHelper {};

template<auto...I, typename...Es>
struct LexiconHelper<std::index_sequence<I...>, Es...>
: public Label<Es, Key<I>>...
{
    // Pull every `idyl` to the current scope.
    using Label<Es, Key<I>>::idyl...;
    // Pull every `lark` to the current scope.
    using Label<Es, Key<I>>::lark...;
};

template<typename...Es>
struct Lexicon
: public LexiconHelper<std::make_index_sequence<sizeof...(Es)>, Es...> {};

using YellowPages = Lexicon<Element<0>, Element<-1>, Element<-2>, Element<-3>>;

// Retrieve the element corresponding to the key `Key<size_t(1)>`.
using SupposedElement = Element<-1>;
using ResultElement = decltype
(YellowPages::idyl(std::declval<Key<static_cast<size_t>(1)>>()));

static_assert(std::same_as<ResultElement, SupposedElement>);

// Retrieve the key corresponding to the element `Element<-1>`.
using SupposedKey = Key<static_cast<size_t>(1)>;
using ResultKey = decltype
(YellowPages::lark(std::declval<Element<-1>>()));

static_assert(std::same_as<ResultKey, SupposedKey>);
```

## Implementation

```C++
template<typename Element, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Element;
    static constexpr auto lark(Element) -> Key;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAdIADqgKhE4MHt6%2BAcGp6Y4C4ZExLPGJ/tJ2mA6ZQgRMxATZPn5Btpj2RQwNTQQl0XEJSbaNza25HQrjAxFD5SNVAJS2qF7EyOwcBJgsyQa7JoFuBACeyYysmADU2PRsgqQ355fMbDcA0phnx9gmGgAgjNiF4HDdQkx4rQAYCTAB2Cw3WE3VE3GZMRzIG5oBgzTCqZLEG5MLxEG54dBnWgQb5nZY3AC0fzuD0YBGOViBaPRjSxOIE%2BMJxNJ5IMxAA1hB7nt2QzmYFsF8fpzYQiACKqoGwgD0ACoDYajcadbqjTcACrYIQWoQ3I2moH640uw2OuHasyBCLIbxYZEnMl0Qi/RVqr0%2Bv23Y5uZAzdBYKh/NVA3b7Q6YGOi1DJoEgsEEVmywTIxEarUewFpg6YzMnbO54EEUHgumlqzwzWBLmVnU6m4AdVuAHc6LQbl4lC8EHgFDcEF1LsTqxmXqgccRMLXdf3UAA3BK0VBMdDozAEOf8YkmABsGkp1NvGhJDFPT/FEqfADpYSvtydXiuNgvxAxt83BUICTwXEAAlFwSdty27FMqz2GsjnrMlUBAr8AElnkA95MBw7AFDA5sCwhKDYPg4gY3jEAQAiLBVAAfSUABHLxGC2GNcJwv5nlIgSwyBEAbmSLxYloaCIShLoY1I546T45NFQE7Uy25NE%2BxuZQvFocdMAPYgzmRO8HxhO812nW5kA2TcSwUNBLh/bTUUnCJgDk6FFIUZSVROXC1OwRjLJEnseV0/TDJuYyEjM98mk/azyQIBccQc9l0Rc4iUTRTyjB8hSTiU5VQzcYKw0VRiPwitVOwrX80IzGNCOuEiyNEpsW0LSDVGggRYXEyTpNk/rBoYODaCXeiCHQRiWCYCVMFY5iCXYzAuJ4us3HSAAvTBUCoHDpQUZZBLuBQRKVBEOy7HtYUK7yAE0uiPYdlCYYBMDnY51SogbcUUtlBBjDRLplR4ORORkuEh0GYbcRkzAR4skcZQIQqap1%2BwAJXPYg8Hi2y4sRgViE3BRUlfLybPS24VsSu8VJOA7VoICAuAusM7zcwFnpuIQvGSApMHQKHsv%2BotoZjOG1J7QWCYUAyCElktpawX1ANhCA3sM1BPu%2B36wqpGkGJALXaD3MQY1Zva%2BWg1jRBmei8EO1iYewLmef%2BRUIGWQOcabTEnaYBQlGaCALYUa5WPDmNldV9WCGeYXRbScWU7%2BHnHtxm4CebYmD1JpmKapmn8CKtKMq6dHzI0bPYfh3mNH5wX07F9A22l%2B2MSxZ3w6R9nPb%2BH2Fae9IiqT2gCB7wIAatnWgT197Da%2Bn6FFq5Lo/mxirZtmFSsRuWW7973A9zlD%2B7DiOEk5mO44Tk4Z7nn405FrvWewXOOFWWhOD%2BF4H4DgWhSCoE4G4aw1h0TrE2NGL0PBSAEE0H/VYEoAhtzMGYAAnAADg0Dg/weCbyBEkGYeEkgbz6E4JIXgLAJAaA0KQEBYCIEcF4FvZhKDQF/1IHAWAMBEAgHWAQSSqcKAQDQPsOgCQojXE4KoEhjIbySBuMAZA2IpBfjMLwcWhASCUj0PwQQIgxDsCkDIQQigVDqF4aQXQXBSDDmIEwZInAeD/0AcA1B4DOAAHkyTiJuMdG4SibwqLURorRkgdE3AgB4GR9BryIOWLwHhWhVgQCQNI5IsiyCSNyfkkAwApBmD4HQXYxAt4QFiL42IEQmhnA8bwBpzBTL%2BNiNoWoPCkHSOhv4hgtBmn2KwLELwwA3BiFoFvbgvAsBLSMOIUZeBNx1APLMsBBJahkm2EgiIuwAH2JkrEVxpkPBYF8UXBhczSAmViJndUexDDABkkYVBqwqAGGAAoAAasTYc/i3gtKscIUQ4hLEmPkEoNQvjHH6BeSgaBlh9B4FiFvSAqxUDJB6LMxk8Z/qmEsNYMwbCTJEywBigOnRuiZBcK%2BSYfgnFhHmGUCoegCgZAEIyjlaQuUMEGGykYTiah1AEH0CYng2h6FFT0CVcxSjDESCK2YPKVX9EFUqiQqwFBwK2NqmhHAgEsN8ewsJyjVHqM0TcbRZh4m4AMSkwI3N0kfNWAuE8IxqUYMkIEL8ODAiUI0OQqhTD/A3hwYauhpAGHOq/DeLgN48H4MTVULg/gA3UNYbwdhnCQDcI%2BfwoR2SRFBLJOQSgRTknyLYJwJoLA9zwkZEwHEBgipcBwV%2BLgX4tn4CIBS4xsgzEQukFCmxsL7G6HKS4txLSvFGp8fY9hgSxFkhCVQEkxAG1Npbb6F5NrO3dufAk1ASSELmECGYNJyDC0lqrQkCtUjT15OSSAetjbGR7qMB2rgzCaCzwSDUup9i2lNJBaBjpXSekgv6eyQZwzfFjImVMwysykELJecssB%2BA1mOA2b47Z9ldggoOV0XxJyzlnAudsMB1yQX3Mec8pZXlC1fO%2Bn8gFQLGAgqhcOixo7ZDjrsWAqdCL3lEqsCik5VKsU4syHiglC8JMkrJQkClJtMU0p6XSiArg1UhFfJqxYyrSCcp6PpszmQjPspFXXMVvRVVStyLZ2l4rZjWeFWMfo%2BmMTNA88qnVeqLHzuNdmvxHBN3buba2/dHau09vtX2kgyJUmut4YHUgHqsCJGpUc6NsbO3BvhBm%2BE8IyFmCoZIJxYXc22HzTe9LRb4AltEeIx997iA1u2PWy1LAFB7mxHuOLGYZh6KSwOpxvHwX8dBUJuFIBggzvcXMkLi62EBLLYWUJPW1F9YGzcIbnaRuFhPWep1gRr0ZL4Xe59%2BT2u3dfQN0WrFDusWO/HLdqiKkAeqZQYDYCIMjKQYDzp3SHAwdPQMoZIzsOYHGZM6ZaH5lMdeTR%2BZqztP4fsYR3ZJHBBkeOWiyj1GrlExuUghjSgnmLNeSxxrbGfn/MwIC4FtypvmIkAJ6xMLhM6AW2J4wyKbDSfgLJ3FnAdQMWU5YUlObyWUg09S2VOm9NOaZQZ9A/neWFEyBZvlPQtcue0257zauZV2ble51lWr1WSpyOr3zCqFg2cCxsfV3NDWhdNZwSLvX%2BuDeG7WGYiXHUpedZdt1mWtzZcoPO/LIBcFfkCIEfw/hg2/o0Mn%2BESaTVLs4Hmgt6X0EgEkJ20rGgO3p8CDefw8IzBVENYENbOb88NcyfO3Ruf1scLb2gu5gG6WSCAA)

## Links

- [source code](../../../conceptrodon/descend/label.hpp)
