#pragma once

#include "typelist.hpp"

namespace tt {

using ::tl::tl;
using ::tl::null_t;

template <class LList, class Cursor, class RList>
struct tape;

template <class LHead, class LTail, class Cursor, class RHead, class RTail>
struct tape<tl<LHead, LTail>, Cursor, tl<RHead, RTail>> {
    using get = Cursor;
    template <class T>
    using set = tape<tl<LHead, LTail>, T, tl<RHead, RTail>>;

    using move_left  = tape<LTail, LHead, tl<Cursor, tl<RHead, RTail>>>;
    using move_right = tape<tl<Cursor, tl<LHead, LTail>>, RHead, RTail>;
};

template <class Cursor>
struct tape<null_t, Cursor, null_t> {
    using get = Cursor;
    template <class T>
    using set = tape<null_t, T, null_t>;

    using move_left  = tape<null_t, null_t, tl<Cursor, null_t>>;
    using move_right = tape<tl<Cursor, null_t>, null_t, null_t>;
};

template <class Cursor, class RHead, class RTail>
struct tape<null_t, Cursor, tl<RHead, RTail>> {
    using get = Cursor;
    template <class T>
    using set = tape<null_t, T, tl<RHead, RTail>>;

    using move_left  = tape<null_t, null_t, tl<Cursor, tl<RHead, RTail>>>;
    using move_right = tape<tl<Cursor, null_t>, RHead, RTail>;

};

template <class LHead, class LTail, class Cursor>
struct tape<tl<LHead, LTail>, Cursor, null_t> {
    using get = Cursor;
    template <class T>
    using set = tape<tl<LHead, LTail>, T, null_t>;

    using move_left  = tape<LTail, LHead, tl<Cursor, null_t>>;
    using move_right = tape<tl<Cursor, tl<LHead, LTail>>, null_t, null_t>;
};

template <class Tape>
using get_t = typename Tape::get;

template <class Tape, class T>
using set_t = typename Tape::template set<T>;

template <class Tape>
using move_left_t  = typename Tape::move_left;

template <class Tape>
using move_right_t = typename Tape::move_right;

template <class T>
using make_t = tape<null_t, T, null_t>;

}
