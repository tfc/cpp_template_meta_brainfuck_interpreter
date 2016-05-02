#pragma once

#include <cstddef>

namespace tl {
struct null_t {};

template <class T, class U>
struct tl
{
    using head = T;
    using tail = U;
};

template <class T, class ... REST>
struct make { using type = tl<T, typename make<REST...>::type>; };
template <class T>
struct make<T> { using type = tl<T, null_t>; };

template <class ... Ts>
using make_t = typename make<Ts...>::type;


template <class TList>
static const constexpr size_t length_v {0};
template <>
static const constexpr size_t length_v<null_t> {0};
template <class T, class U>
static const constexpr size_t length_v<tl<T, U>> {1 + length_v<U>};


template <class TList, size_t i>
struct type_at;
template <class Head, class Tail>
struct type_at<tl<Head, Tail>, 0> { using type = Head; };
template <class Head, class Tail, size_t i>
struct type_at<tl<Head, Tail>, i> { using type = typename type_at<Tail, i - 1>::type; };

template <class TL, size_t i>
using type_at_t = typename type_at<TL, i>::type;


template <class TList, class T>
static const constexpr ssize_t index_of_v {-1};;
template <class T>
static const constexpr ssize_t index_of_v<null_t, T> {-1};
template <class T, class Tail>
static const constexpr ssize_t index_of_v<tl<T, Tail>, T> {0};
template <class Head, class Tail, class T>
static const constexpr ssize_t index_of_v<tl<Head, Tail>, T> {
    (index_of_v<Tail, T> == -1) ? -1 : (1 + index_of_v<Tail, T>)};


template <class TList, class T>
static const constexpr bool contains_v {index_of_v<TList, T> != -1};


template <class TList, class T>
struct append;
template <>
struct append<null_t, null_t> { using type = null_t; };
template <class T>
struct append<null_t, T> { using type = make_t<T>; };
template <class Head, class T>
struct append<null_t, tl<Head, T>> { using type = tl<Head, T>; };
template <class Head, class Tail, class T>
struct append<tl<Head, Tail>, T>
{ using type = tl<Head, typename append<Tail, T>::type>; };

template <class TList, class T>
using append_t = typename append<TList, T>::type;

template <class Tl1, class Tl2>
struct concat;
template <class Tl1>
struct concat<Tl1, null_t> { using type = Tl1; };
template <class Tl2>
struct concat<null_t, Tl2> { using type = Tl2; };
template <class H1, class T1, class Tl2>
struct concat<tl<H1, T1>, Tl2> { using type = tl<H1, typename concat<T1, Tl2>::type>; };

template <class Tl1, class Tl2>
using concat_t = typename concat<Tl1, Tl2>::type;

template <class Tlist, class T>
struct remove;
template <class T>
struct remove<null_t, T> { using type = null_t; };
template <class Tl, class T>
struct remove<tl<T, Tl>, T> { using type = typename remove<Tl, T>::type; };
template <class Head, class Tl, class T>
struct remove<tl<Head, Tl>, T> { using type = tl<Head, typename remove<Tl, T>::type>; };

template <class Tlist, class T>
using remove_t = typename remove<Tlist, T>::type;

template <class Tlist, template <typename> class F>
struct map;
template <template <typename> class F>
struct map<null_t, F> { using type = null_t; };
template <class Head, class Tail, template <typename> class F>
struct map<tl<Head, Tail>, F> { using type = tl<typename F<Head>::type, typename map<Tail, F>::type>; };

template <class Tlist, template <typename> class F>
using map_t = typename map<Tlist, F>::type;


template <class TList>
struct head;
template <class Head, class Tail>
struct head<tl<Head, Tail>> { using type = Head; };
template <>
struct head<null_t> { using type = null_t; };

template <class TList>
using head_t = typename head<TList>::type;

template <class TList>
struct tail;
template <class Head, class Tail>
struct tail<tl<Head, Tail>> { using type = Tail; };
template <>
struct tail<null_t> { using type = null_t; };

template <class TList>
using tail_t = typename tail<TList>::type;

template <class Tlist, template <typename, typename> class BinF>
struct foldl1;
template <template <typename, typename> class BinF>
struct foldl1<null_t, BinF> { using type = null_t; };
template <class T, template <typename, typename> class BinF>
struct foldl1<tl<T, null_t>, BinF> { using type = T; };
template <class Head1, class Head2, class T, template <typename, typename> class BinF>
struct foldl1<tl<Head1, tl<Head2, T>>, BinF> { using type =
    typename foldl1<tl<typename BinF<Head1, Head2>::type, T>, BinF>::type; };

template <class Tlist, template <typename, typename> class BinF>
using foldl1_t = typename foldl1<Tlist, BinF>::type;

template <class Tlist, template <typename, typename> class BinF>
struct foldr1;
template <template <typename, typename> class BinF>
struct foldr1<null_t, BinF> { using type = null_t; };
template <class Head, template <typename, typename> class BinF>
struct foldr1<tl<Head, null_t>, BinF> { using type = Head; };
template <class Head1, class Head2, template <typename, typename> class BinF>
struct foldr1<tl<Head1, tl<Head2, null_t>>, BinF> { using type = typename BinF<Head1, Head2>::type; };
template <class Head, class Tl, template <typename, typename> class BinF>
struct foldr1<tl<Head, Tl>, BinF> { using type = typename BinF<Head, typename foldr1<Tl, BinF>::type>::type; };

template <class Tlist, template <typename, typename> class BinF>
using foldr1_t = typename foldr1<Tlist, BinF>::type;

} // namespace tl
