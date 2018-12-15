
#ifndef TEST_SHARED_PTR_SRC_MY_SHARED_PTR_HPP_
#define TEST_SHARED_PTR_SRC_MY_SHARED_PTR_HPP_

#ifdef USE_BOOST_SHARED_PTR
#pragma message("using boost::shared_ptr")

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
template<typename T> 
using my_shared_ptr = boost::shared_ptr<T>;

#define MY_NAMESPACE boost

#else
#pragma message("using std::shared_ptr")

#include <memory>
template<typename T> 
using my_shared_ptr = std::shared_ptr<T>;

#define MY_NAMESPACE std

#endif 

#endif