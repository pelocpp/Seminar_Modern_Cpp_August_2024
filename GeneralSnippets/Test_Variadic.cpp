template<class type_parameter_0_0, class ... type_parameter_0_1>
void printer3(type_parameter_0_0 n, type_parameter_0_1... args)
{
    if constexpr (sizeof...(args) > 0) {
        printer3(args...);
    }

}

// #define INSIGHTS_USE_TEMPLATE 1
 
/* First instantiated from: insights.cpp:10 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void printer3<int, int, int, int, int>(int n, int __args1, int __args2, int __args3, int __args4)
{
    if constexpr (true) {
        printer3(__args1, __args2, __args3, __args4);
    }

}
#endif


/* First instantiated from: insights.cpp:4 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void printer3<int, int, int, int>(int n, int __args1, int __args2, int __args3)
{
    if constexpr (true) {
        printer3(__args1, __args2, __args3);
    }

}
#endif


/* First instantiated from: insights.cpp:4 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void printer3<int, int, int>(int n, int __args1, int __args2)
{
    if constexpr (true) {
        printer3(__args1, __args2);
    }

}
#endif


/* First instantiated from: insights.cpp:4 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void printer3<int, int>(int n, int __args1)
{
    if constexpr (true) {
        printer3(__args1);
    }

}
#endif


/* First instantiated from: insights.cpp:4 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void printer3<int>(int n)
{
    if constexpr (false) {
    }

}
#endif


void test_seminar()
{
    printer3(1, 2, 3, 4, 5);
}