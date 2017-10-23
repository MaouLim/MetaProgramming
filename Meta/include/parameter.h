#ifndef _META_PARAMETER_H_
#define _META_PARAMETER_H_

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <type_traits>

namespace mpl = boost::mpl;

namespace meta {
	
	template <typename _T>
	struct param_type : 
		mpl::eval_if<
			mpl::or_<
				std::is_scalar<_T>, 
				std::is_reference<_T>
			>,
			std::identity<_T>, 
			std::add_lvalue_reference<const _T>
		> { };
}

#endif