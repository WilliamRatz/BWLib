#pragma once

#define VectorTemplate template <typename T, std::size_t N>
template<typename T, std::size_t R, std::size_t C, typename Enable = void> class Matrix;
#define MatrixTemplate template<typename T, std::size_t R, std::size_t C>
#define MatrixMacro typename std::enable_if<std::is_same<T, signed __int8>::value || \
															std::is_same<T, unsigned __int8>::value || \
															std::is_same<T, signed __int16>::value || \
															std::is_same<T, unsigned __int16>::value || \
															std::is_same<T, signed __int32>::value || \
															std::is_same<T, unsigned __int32>::value || \
															std::is_same<T, signed __int64>::value || \
															std::is_same<T, unsigned __int64>::value || \
															std::is_same<T, float>::value || \
															std::is_same<T, double>::value>::type>
template<typename T, std::size_t N, typename Enable = void> class VectorX;
#define VectorXMacro VectorX<T, N, typename std::enable_if<std::is_same<T, signed __int8>::value || \
														   std::is_same<T, unsigned __int8>::value || \
														   std::is_same<T, signed __int16>::value || \
														   std::is_same<T, unsigned __int16>::value || \
														   std::is_same<T, signed __int32>::value || \
														   std::is_same<T, unsigned __int32>::value || \
														   std::is_same<T, signed __int64>::value || \
														   std::is_same<T, unsigned __int64>::value || \
														   std::is_same<T, float>::value || \
														   std::is_same<T, double>::value>::type>

#define VectorXMacro3 VectorX<T, 3, typename std::enable_if<std::is_same<T, signed __int8>::value || \
															std::is_same<T, unsigned __int8>::value || \
															std::is_same<T, signed __int16>::value || \
															std::is_same<T, unsigned __int16>::value || \
															std::is_same<T, signed __int32>::value || \
															std::is_same<T, unsigned __int32>::value || \
															std::is_same<T, signed __int64>::value || \
															std::is_same<T, unsigned __int64>::value || \
															std::is_same<T, float>::value || \
															std::is_same<T, double>::value>::type>


