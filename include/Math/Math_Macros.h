#pragma once

#define VectorTemplate template <typename T, std::size_t N>
#define MatrixTemplate template<typename T, std::size_t R, std::size_t C>
#define MatrixMacro Matrix<T, R, C, typename std::enable_if<std::is_same<T, signed __int8>::value || \
															std::is_same<T, unsigned __int8>::value || \
															std::is_same<T, signed __int16>::value || \
															std::is_same<T, unsigned __int16>::value || \
															std::is_same<T, signed __int32>::value || \
															std::is_same<T, unsigned __int32>::value || \
															std::is_same<T, signed __int64>::value || \
															std::is_same<T, unsigned __int64>::value || \
															std::is_same<T, float>::value || \
															std::is_same<T, double>::value>::type>