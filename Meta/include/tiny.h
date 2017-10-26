#ifndef _META_TINY_H_
#define _META_TINY_H_

#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/vector/aux_/size.hpp>
#include <boost/mpl/aux_/clear_impl.hpp>
#include <boost/mpl/aux_/push_front_impl.hpp>
#include <boost/mpl/aux_/push_back_impl.hpp>

namespace mpl = boost::mpl;

namespace meta {

	struct na { };

	struct tiny_tag { };

	template <
		typename _T0 = na, 
		typename _T1 = na, 
		typename _T2 = na
	> 
	struct tiny {
		typedef tiny<_T0, _T1, _T2> type;
		typedef tiny_tag            tag;
		typedef _T0                 t0;
		typedef _T1                 t1;
		typedef _T2                 t2;
	};

	template <typename _Tiny, typename _Pos>
	struct tiny_iterator {
		typedef mpl::random_access_iterator_tag category;
	};

	template <typename _Tiny, size_t _N>
	struct tiny_at { };

	template <typename _Tiny>
	struct tiny_at<_Tiny, 0> {
		typedef typename _Tiny::t0 type;
	};

	template <typename _Tiny>
	struct tiny_at<_Tiny, 1> {
		typedef typename _Tiny::t1 type;
	};

	template <typename _Tiny>
	struct tiny_at<_Tiny, 2> {
		typedef typename _Tiny::t2 type;
	};

	template <typename _T0, typename _T1, typename _T2>
	struct tiny_size : mpl::int_<3> { };

	template <typename _T0, typename _T1>
	struct tiny_size<_T0, _T1, na> : mpl::int_<2> { };

	template <typename _T0>
	struct tiny_size<_T0, na, na> : mpl::int_<1> { };

	template <>
	struct tiny_size<na, na, na> : mpl::int_<0> { };

	template <typename _Tiny>
	struct tiny_empty : 
		mpl::equal<
			mpl::int_<0>, 
			typename tiny_size<
				typename _Tiny::t0, 
				typename _Tiny::t1, 
				typename _Tiny::t2
			>::type
		> { };

	template <typename _Tiny>
	struct tiny_full :
		mpl::equal<
			mpl::int_<3>,
			typename tiny_size<
				typename _Tiny::t0,
				typename _Tiny::t1,
				typename _Tiny::t2
			>::type
		> { };

	template <typename _Tiny, typename _T, size_t _N>
	struct tiny_push_back;

	template <typename _Tiny, typename _T>
	struct tiny_push_back<_Tiny, _T, 0> : tiny<_T, na, na> { };

	template <typename _Tiny, typename _T>
	struct tiny_push_back<_Tiny, _T, 1> : tiny<typename _Tiny::t0, _T, na> { };

	template <typename _Tiny, typename _T>
	struct tiny_push_back<_Tiny, _T, 2> : 
		tiny<typename _Tiny::t0, typename _Tiny::t1, _T> { };
}

namespace boost {
	namespace mpl {
	
		template <typename _Tiny, typename _Pos>
		struct next<meta::tiny_iterator<_Tiny, _Pos>> {
			typedef meta::tiny_iterator<
				_Tiny,
				typename next<_Pos>::type
			> type;
		};

		template <typename _Tiny, typename _Pos>
		struct prior<meta::tiny_iterator<_Tiny, _Pos>> {
			typedef meta::tiny_iterator<
				_Tiny, 
				typename prior<_Pos>::type
			> type;
		};

//		template <
//			typename _T0,
//			typename _T1,
//			typename _T2,
//			typename _Pos
//		>
//		struct at<meta::tiny<_T0, _T1, _T2>, _Pos> : 
//			meta::tiny_at<meta::tiny<_T0, _T1, _T2>, _Pos::value> { };

		template <>
		struct at_impl<meta::tiny_tag> {

			template <typename _Tiny, typename _N>
			struct apply : 
				meta::tiny_at<_Tiny, _N::value> { };
		};

		template <typename _Tiny, typename _Pos, typename _N>
		struct advance<meta::tiny_iterator<_Tiny, _Pos>, _N> {
			typedef meta::tiny_iterator<
				_Tiny, 
				typename plus<_Pos, _N>::type
			> type;
		};

		template <typename _Tiny, typename _First, typename _Last>
		struct distance<
			meta::tiny_iterator<_Tiny, _First>, 
			meta::tiny_iterator<_Tiny, _Last>
		> : minus<_Last, _First> { };

		template <>
		struct begin_impl<meta::tiny_tag> {

			template <typename _Tiny>
			struct apply {
				typedef meta::tiny_iterator<_Tiny, int_<0>> type;
			};
		};

		template <>
		struct end_impl<meta::tiny_tag> {

			template <typename _Tiny>
			struct apply {
				typedef meta::tiny_iterator<
					_Tiny, 
					typename meta::tiny_size<
						typename _Tiny::t0,
						typename _Tiny::t1,
						typename _Tiny::t2
					>::type
				> type;
			};
		};

		template <>
		struct size_impl<meta::tiny_tag> {
			
			template <typename _Tiny>
			struct apply : meta::tiny_size<
				typename _Tiny::t0,
				typename _Tiny::t1,
				typename _Tiny::t2
			> { };
		};

		template <>
		struct clear_impl<meta::tiny_tag> {

			template <typename _Tiny>
			struct apply : meta::tiny<> { };
		};

		template <>
		struct push_front_impl<meta::tiny_tag> {
			
			template <typename _Tiny, typename _T>
			struct apply {
				static_assert(!meta::tiny_full<_Tiny>::type::value);
				typedef meta::tiny<_T, typename _Tiny::t0, typename _Tiny::t1> type;
			};
		};

		template <>
		struct push_back_impl<meta::tiny_tag> {
			template <typename _Tiny, typename _T>
			struct apply : 
				meta::tiny_push_back<_Tiny, _T, size<_Tiny>::value> { };
		};
	}
}


#endif
