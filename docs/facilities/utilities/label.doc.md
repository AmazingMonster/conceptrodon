<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Label`

<p style='text-align: right;'><a href="../utilities.md#label">To Index</a></p>

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
/**** Element ****/
template<auto>
struct Element {};

/**** Key ****/
template<auto>
struct Key {};

/**** Lexicon ****/
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

/**** YellowPages ****/
using YellowPages = Lexicon<Element<0>, Element<-1>, Element<-2>, Element<-3>>;

/**** Tests ****/
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

## Links

- [Example](../../code/facilities/utilities/label/implementation.hpp)
- [Source code](../../../conceptrodon/label.hpp)
